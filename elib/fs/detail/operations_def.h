#ifndef ELIB_FS_OPERATIONS_DEF_H
#define ELIB_FS_OPERATIONS_DEF_H

#include <elib/fs/detail/operations_helper.h>
#include <elib/fs/detail/filesystem_error_helper.h>

#include <memory>

#include <cstdint>
#include <cstdlib>
#include <climits>

#include <unistd.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/statvfs.h>


namespace elib {
namespace fs {
    
    
// absolute
inline path 
absolute(const path& p, const path& base)
{
    bool has_root_dir = p.has_root_directory();
    
    if (p.has_root_name()) {
        if (has_root_dir) {
            return p;
        } 
        else {
            return (p.root_name() / absolute(base).root_directory()
                    /
                    absolute(base).relative_path() / p.relative_path());
        }
    } 
    else {
        if (has_root_dir) {
            return (absolute(base).root_name() / p);
        } else {
            return (absolute(base) / p);
        }
    }
    
    throw;
}


// canonical
inline path 
canonical(const path& p, const path& base)
{
    std::error_code ec;
    auto canon_p = canonical(p, base, ec);
    if (ec) 
        throw filesystem_error(ec.message(), p, base, ec);
}

inline path 
canonical(const path& p, std::error_code& ec)
{
    return canonical(p, current_path(), ec);
}

inline path 
canonical(const path& p, const path& base, std::error_code& ec)
{
    ec.clear();
    auto ap = absolute(p, base);
    auto str = detail::_realpath(ap.c_str(), ec);
    if (ec)
        return path();
    
    return path(str);
}


// copy
inline void 
copy(const path& from, const path& to)
{
    copy(from, to, copy_options::none);
}

inline void 
copy(const path& from, const path& to, std::error_code& ec) noexcept
{
    copy(from, to, copy_options::none, ec);
}


inline void
copy(const path& from, const path& to, copy_options options)
{
    std::error_code ec;
    copy(from, to, options, ec);
    if (ec)
        throw filesystem_error(ec.message(),  from, to, ec);
}

inline void
copy(const path& from, const path& to, 
     copy_options options, std::error_code& ec) noexcept
{
    ec.clear();
    
    bool sym_status = (options & copy_options::create_symlinks) ||
                      (options & copy_options::skip_symlinks);
    
    file_status f_stat, t_stat;
    if (sym_status) {
        
        f_stat = symlink_status(from, ec);
        if (! detail::_file_status_bad(f_stat))
            return;
        
        t_stat = symlink_status(to, ec);
        if (! detail::_file_status_bad(t_stat))
            return;
        
        ec.clear();
    } 
    else {
        
        f_stat = status(from, ec);
        if (! detail::_file_status_bad(f_stat))
            return;
        
        t_stat = status(to, ec);
        if (! detail::_file_status_bad(t_stat))
            return;
        
        ec.clear();
    }
    
    if (! exists(f_stat)) {
        detail::handle_error(std::errc::no_such_file_or_directory, ec);
        return;
    }
    
    //TODO
    if (equivalent(from, to, ec) ||
        (is_directory(f_stat) && is_regular_file(t_stat))) {
        detail::handle_error(std::errc::file_exists, ec);
        return;
    }
    
    if (is_symlink(f_stat)) {
        
        if (options & copy_options::skip_symlinks)
            return;
        
        if (! exists(t_stat)) {
            copy_symlink(from, to, ec);
            return;
        }
        // else t exists
        detail::handle_error(std::errc::file_exists, ec);
        return;
    }
    
    if (is_regular_file(f_stat)) {
        
        if (options & copy_options::directories_only) {
            return;
        }
        else if (options & copy_options::create_symlinks) {
            create_symlink(from, to, ec);
            return;
        }
        else if (options & copy_options::create_hard_links) {
            create_hard_link(from, to, ec);
            return;
        }
        else if (is_directory(t_stat)) {
            copy_file(from, to / from.filename(), options, ec);
            return;
        } else {
            copy_file(from, to, options, ec);
            return;
        }
        //shouldn't be here
        throw;
    }
    
    if (is_directory(f_stat) && ((options & copy_options::recursive) ||
                                 !(options & copy_options::none))) {
        
        if (! exists(t_stat)) {
            create_directory(to, from, ec);
            if (ec)
                return;
        }
        
        //TODO
        throw;
        return;
    } 
    
    //TODO
    return;
}

//copy_file
inline void 
copy_file(const path& from, const path& to)
{
    copy_file(from, to, copy_options::none);
}

inline void 
copy_file(const path& from, const path& to, std::error_code& ec) noexcept
{
    copy_file(from, to, copy_options::none, ec);
}

inline void 
copy_file(const path& from, const path& to, copy_options option)
{
    std::error_code ec;
    copy_file(from, to, option, ec);
    if (ec)
        throw filesystem_error(ec.message(), from, to, ec);
}

inline void 
copy_file(const path& from, const path& to, copy_options option,
          std::error_code& ec) noexcept
{   
    ec.clear();
    
    file_status t_stat = status(to, ec);
    if (! detail::_file_status_bad(t_stat))
        return;
    
    ec.clear();
    
    auto existing_options = (copy_options::skip_existing |
                            copy_options::overwrite_existing |
                            copy_options::update_existing);
    
    if (exists(t_stat) && !(option & existing_options)) {
        detail::handle_error(std::errc::file_exists, ec);
        return;
    }
    
    //TODO
    ((void)from);
    throw;
}
          
//copy_symlink
inline void 
copy_symlink(const path& existing_symlink, const path& new_symlink)
{
    std::error_code ec;
    copy_symlink(existing_symlink, new_symlink, ec);
    if (ec)
        throw filesystem_error(ec.message(), existing_symlink, new_symlink, ec);
}

inline void 
copy_symlink(const path& existing_symlink, const path& new_symlink,
             std::error_code& ec) noexcept
{
    ((void)existing_symlink); ((void)new_symlink);
    ec.clear();
    
    //TODO
    throw;
}
                 

             
//create_directories
inline bool 
create_directories(const path& p);

inline bool 
create_directories(const path& p, std::error_code& ec) noexcept;


// create_directory
inline bool 
create_directory(const path& p)
{
    std::error_code ec;
    auto ret = create_directory(p, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, ec);
    return ret;
}

inline bool 
create_directory(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    //TODO
    ((void)p);
    throw;
}

inline void 
create_directory(const path& p, const path& attributes)
{
    std::error_code ec;
    create_directory(p, attributes, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, attributes, ec);
}

inline void 
create_directory(const path& p, const path& attributes, 
                 std::error_code& ec) noexcept
{
    ec.clear();
    //TODO
    ((void)p); ((void)attributes);
    throw;
    
}


//create_directory_symlink
inline void 
create_directory_symlink(const path& to, const path& new_symlink)
{
    std::error_code ec;
    create_directory_symlink(to, new_symlink, ec);
    if (ec)
        throw filesystem_error(ec.message(), to, new_symlink, ec);
}

inline void 
create_directory_symlink(const path& to, const path& new_symlink,
                         std::error_code& ec) noexcept
{
    ec.clear();
    ((void)to); ((void)new_symlink);
    throw;
}


//create_hard_link
inline void 
create_hard_link(const path& to, const path& new_hard_link)
{
    std::error_code ec;
    create_hard_link(to, new_hard_link, ec);
    if (ec)
        throw filesystem_error(ec.message(), to, new_hard_link, ec);
}

inline void 
create_hard_link(const path& to, const path& new_hard_link,
                 std::error_code& ec) noexcept
{
    ec.clear();
    ((void)to); ((void)new_hard_link);
    throw;
}

                
// create_symlink
inline void 
create_symlink(const path& to, const path& new_symlink)
{
    std::error_code ec;
    create_symlink(to, new_symlink, ec);
    if (ec)
        throw filesystem_error(ec.message(), to, new_symlink, ec);
}

inline void 
create_symlink(const path& to, const path& new_symlink,
               std::error_code& ec) noexcept
{
    ec.clear();
    ((void)to); ((void)new_symlink);
    throw;
}

               
// current_path
inline path 
current_path()
{
    std::error_code ec;
    auto p = current_path(ec);
    if (ec)
        throw filesystem_error(ec.message(), ec);
    return p;
}

inline path 
current_path(std::error_code& ec)
{
    ec.clear();
    
    long size = pathconf(".", _PC_PATH_MAX);
    std::unique_ptr<char[]> buff(new char[size]); 

    auto ptr = getcwd(buff.get(), static_cast<size_t>(size));
    if (! ptr) {
        detail::handle_errno(ec);
        return path();
    }
    
    return path(buff.get());
}

inline void 
current_path(const path& p)
{
    std::error_code ec;
    current_path(p, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, ec);
}

inline void 
current_path(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    if (chdir(p.c_str()) == -1)
        detail::handle_errno(ec);
}


//exists
inline bool 
exists(file_status s) noexcept
{
    return (status_known(s) && s.type() != file_type::not_found);
}

inline bool 
exists(const path& p)
{
    return exists(status(p));
}

inline bool 
exists(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    return exists(status(p, ec));
}

//equivalent
inline bool 
equivalent(const path& p1, const path& p2)
{
    std::error_code ec;
    bool ret = equivalent(p1, p2, ec);
    if (ec)
        throw filesystem_error(ec.message(), p1, p2, ec);
    return ret;
}

inline bool 
equivalent(const path& p1, const path& p2, std::error_code& ec) noexcept
{
    ec.clear();
    
    struct stat stat1, stat2;
    file_status fs1, fs2;
    
    fs1 = detail::_status(p1, stat1, ec);
    if (! detail::_file_status_bad(fs1))
        return false;
    
    fs2 = detail::_status(p2, stat2, ec);
    if (! detail::_file_status_bad(fs2))
        return false;
    
    ec.clear();
    
    if (! exists(fs1) && ! exists(fs2)) {
        detail::handle_error(std::errc::no_such_file_or_directory, ec);
        return false;
    }
    
    if (is_other(fs1) && is_other(fs2)) {
        detail::handle_error(std::errc::bad_file_descriptor, ec);
        return false;
    }
    
    return (stat1.st_dev == stat2.st_dev && 
            stat1.st_ino == stat2.st_ino);
}


//file_size
inline uintmax_t 
file_size(const path& p)
{
    std::error_code ec;
    uintmax_t ret = file_size(p, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, ec);
    return ret;
}

inline uintmax_t 
file_size(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    struct stat pstat;
    
    file_status fst = detail::_status(p, pstat, ec);
    
    // ec is set when ! exists(fst)
    if (ec)
        return static_cast<uintmax_t>(-1);
    
   if (! is_regular_file(fst)) {
        detail::handle_error(std::errc::operation_not_permitted, ec);
        return static_cast<uintmax_t>(-1);
   }
    
    return detail::_file_size(pstat);
}

//hard_link_count
inline uintmax_t 
hard_link_count(const path& p)
{
    std::error_code ec;
    auto ret = hard_link_count(p, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, ec);
    return ret;
}

inline uintmax_t 
hard_link_count(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    struct stat st;
    file_status fst = detail::_status(p, st, ec);
    if (! detail::_file_status_bad(fst))
        return static_cast<uintmax_t>(-1);
    
    if (! exists(fst))
        return 0;
    
    return static_cast<uintmax_t>(st.st_nlink);
}


//is_block_file
inline bool 
is_block_file(file_status s) noexcept
{
    return (s.type() == file_type::block);
}

inline bool 
is_block_file(const path& p)
{
    return is_block_file(status(p));
}

inline bool 
is_block_file(const path& p, std::error_code& ec) noexcept
{
    return is_block_file(status(p, ec));
}


//is_character_file
inline bool 
is_character_file(file_status s) noexcept
{
    return (s.type() == file_type::character);
}

inline bool 
is_character_file(const path& p)
{
    return is_character_file(status(p));
}

inline bool 
is_character_file(const path& p, std::error_code& ec) noexcept
{
    return is_character_file(status(p, ec));
}


//is_directory
inline bool 
is_directory(file_status s) noexcept
{
    return s.type() == file_type::directory;
}

inline bool 
is_directory(const path& p)
{
    return is_directory(status(p));
}

inline bool 
is_directory(const path& p, std::error_code& ec) noexcept
{
    return is_directory(status(p, ec));
}


//is_empty
inline bool 
is_empty(const path& p)
{
    std::error_code ec;
    
    struct stat st;
    file_status fst = detail::_status(p, st, ec);
    if (! detail::_file_status_bad(fst))
        return false;
    
    //TODO
    if (is_directory(fst))
        throw;

    return (detail::_file_size(st) == 0);
}

inline bool 
is_empty(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    struct stat st;
    file_status fst = detail::_status(p, st, ec);
    if (! detail::_file_status_bad(fst))
        return false;
    
    //TODO
    if (is_directory(fst))
        throw;

    return (detail::_file_size(st) == 0);
}


//is_fifo
inline bool 
is_fifo(file_status s) noexcept
{
    return (s.type() == file_type::fifo);
}

inline bool 
is_fifo(const path& p)
{
    std::error_code ec;
    
    file_status fst = status(p, ec);
    
    if (! detail::_file_status_bad(fst))
        throw filesystem_error(ec.message(), p, ec);
    
    return is_fifo(fst);
}

inline bool 
is_fifo(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    file_status fst = status(p, ec);
    if (detail::_file_status_bad(fst))
        return false;
    
    return is_fifo(fst);
}


//is_other
inline bool
is_other(file_status s) noexcept
{
    return ( exists(s) && 
             ! is_regular_file(s) && 
             ! is_directory(s) && 
             ! is_symlink(s));
}

inline bool
is_other(const path& p)
{
    std::error_code ec;
    
    file_status fst = status(p, ec);
    
    if (! detail::_file_status_bad(fst))
        throw filesystem_error(ec.message(), p, ec);
    
    return is_other(fst);
}

inline bool
is_other(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    file_status fst = status(p, ec);
    if ( ! detail::_file_status_bad(fst))
        return false;
    
    return is_other(fst);
}


//is_regular_file
inline bool
is_regular_file(file_status s) noexcept
{
    return (s.type() == file_type::regular);
}

inline bool
is_regular_file(const path& p)
{
    std::error_code ec;
    
    file_status fst = status(p, ec);
    
    if (! detail::_file_status_bad(fst))
        throw filesystem_error(ec.message(), p, ec);
    
    return is_regular_file(fst);
}

inline bool
is_regular_file(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    file_status fst = status(p, ec);
    if ( ! detail::_file_status_bad(fst))
        return false;
    
    return is_regular_file(fst);
}

//is_socket
inline bool
is_socket(file_status s) noexcept
{
    return (s.type() == file_type::socket);
}

inline bool
is_socket(const path& p)
{
    std::error_code ec;
    
    file_status fst = status(p, ec);
    
    if (! detail::_file_status_bad(fst))
        throw filesystem_error(ec.message(), p, ec);
    
    return is_socket(fst);
}

inline bool
is_socket(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    file_status fst = status(p, ec);
    if ( ! detail::_file_status_bad(fst))
        return false;
    
    return is_socket(fst);
}


//is_symlink
inline bool
is_symlink(file_status s) noexcept
{
    return (s.type() == file_type::symlink);
}

inline bool
is_symlink(const path& p)
{
    std::error_code ec;
    
    file_status fst = status(p, ec);
    
    if (! detail::_file_status_bad(fst))
        throw filesystem_error(ec.message(), p, ec);
    
    return is_symlink(fst);
}

inline bool
is_symlink(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    file_status fst = symlink_status(p, ec);
    if ( ! detail::_file_status_bad(fst))
        return false;
    
    return is_symlink(fst);
}


//last_write_time
inline file_time_type  
last_write_time(const path& p)
{
    std::error_code ec;
    auto ret = last_write_time(p, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, ec);
    return ret;
}

inline file_time_type  
last_write_time(const path& p, std::error_code& ec) noexcept
{    
    ec.clear();
    
    struct stat st;
    file_status fst = detail::_status(p, st, ec);
    if (! detail::_file_status_bad(fst) || ! exists(fst))
        return detail::clock::from_time_t(static_cast<std::time_t>(-1));
    
    return detail::clock::from_time_t(st.st_mtime);
}

inline void
last_write_time(const path& p, file_time_type new_time)
{
    std::error_code ec;
    last_write_time(p, new_time, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, ec);
}

inline void
last_write_time(const path& p, file_time_type new_time,
                std::error_code& ec) noexcept
{
    ec.clear();
    
    struct stat st;
    detail::_status(p, st, ec);
    if (ec)
        return;
    
    struct utimbuf ut;
    ut.actime = st.st_atime;
    ut.modtime = detail::clock::to_time_t(new_time);
    
    if (utime(p.c_str(), &ut) == -1)
        detail::handle_errno(ec);
    
}

inline void 
permissions(const path& p, perms prms)
{
    std::error_code ec;
    permissions(p, prms, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, ec);
}

inline void 
permissions(const path& p, perms prms, std::error_code& ec) noexcept
{
    ec.clear();
    
    //TODO
    ((void)p); ((void)prms);
    throw;
}
                
// read_symlink
inline path 
read_symlink(const path& p)
{
    std::error_code ec;
    auto tmp_p = read_symlink(p, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, ec);
    return tmp_p;
}

inline path 
read_symlink(const path& p, std::error_code& ec)
{
    ec.clear();
    
    std::string tmp = detail::_readlink(p, ec);
    if (ec)
        return path();
    
    return path(tmp);
}


//remove
inline bool
remove(const path& p);

inline bool
remove(const path& p, std::error_code& ec) noexcept;


//remove_all
inline uintmax_t 
remove_all(const path& p);

inline uintmax_t 
remove_all(const path& p, std::error_code& ec) noexcept;

//rename
inline void
rename(const path& from, const path& to);

inline void
rename(const path& from, const path& to, std::error_code& ec) noexcept;


//resize_file
inline void
resize_file(const path& p, uintmax_t size);

inline void
resize_file(const path& p, uintmax_t size, std::error_code& ec) noexcept;


//space
inline space_info   
space(const path& p)
{
    std::error_code ec;
    auto ret = space(p, ec);
    if (ec)
        throw filesystem_error(ec.message(), p, ec);
    return ret;
}

inline space_info   
space(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    space_info sinfo;
    
    struct statvfs vst;
    if (statvfs(p.c_str(), &vst) == -1) {
        detail::handle_errno(ec);
        sinfo.capacity = static_cast<uintmax_t>(-1);
        sinfo.free = static_cast<uintmax_t>(-1);
        sinfo.available = static_cast<uintmax_t>(-1);
        return sinfo;
    }
    
    sinfo.capacity = vst.f_blocks * vst.f_frsize;
    sinfo.free = vst.f_bfree * vst.f_frsize;
    sinfo.available = vst.f_bavail * vst.f_frsize;
    return sinfo;
}


//file_status
inline file_status  
status(const path& p)
{
    std::error_code ec;
    file_status result = status(p, ec);
    if (result.type() == file_type::none)
        throw filesystem_error("TODO", p, ec);
    return result;
}

inline file_status  
status(const path& p, std::error_code& ec) noexcept
{
    struct stat path_stat;
    return detail::_status(p, path_stat, ec);
}


//status_known
inline bool
status_known(file_status s) noexcept
{
    return (s.type() != file_type::unknown);
}

inline file_status  
symlink_status(const path& p)
{
    std::error_code ec;
    auto fstat = symlink_status(p, ec);
    if (fstat.type() == file_type::none)
        throw filesystem_error("TODO", p, ec);
    return fstat;
}

inline file_status  
symlink_status(const path& p, std::error_code& ec) noexcept
{
    struct stat path_stat;
    return detail::_symlink_status(p, path_stat, ec);
}

inline path 
system_complete(const path& p)
{
    return absolute(p, current_path());
}

inline path 
system_complete(const path& p, std::error_code& ec)
{
    ec.clear();
    return absolute(p, current_path());
}


namespace detail {
    
    inline bool
    _check_dir(const path & p) noexcept
    {
        if (p.empty())
            return false;
        
        std::error_code ec;
        file_status st = status(p, ec);
        
        if (! detail::_file_status_bad(st))
            return false;
        
        return (exists(p) && is_directory(p));
    }

} /* namespace detail */


inline path 
temp_directory_path()
{
    std::error_code ec;
    auto p = temp_directory_path(ec);
    if (ec)
        throw filesystem_error(ec.message(), ec);
    
    return p;
}

inline path 
temp_directory_path(std::error_code& ec)
{
    ec.clear();
    
    path p;
    
    const char* env_paths[] = {"TMPDIR", "TMP", "TEMP", "TEMPDIR"};
    for (auto & ep : env_paths) {
        p = detail::_path_from_env(ep);
        if (detail::_check_dir(p))
            return p;
    }
    
    p = path("/tmp");
    if (detail::_check_dir(p))
        return p;
    
    detail::handle_error(std::errc::no_such_file_or_directory, ec);
    return path();
}


inline path 
unique_path(const path& model);

inline path 
unique_path(const path& model, std::error_code& ec);
    
} /* namespace fs */
} /* namespace elib */



#endif /* ELIB_FS_OPERATIONS_DEF_H */