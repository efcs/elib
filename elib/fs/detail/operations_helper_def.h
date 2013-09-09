#ifndef ELIB_FS_OPERATIONS_HELPER_DEF_H
#define ELIB_FS_OPERATIONS_HELPER_DEF_H


namespace elib {
namespace  fs {
namespace detail {

    
    inline std::string
_realpath(const char* p_str, std::error_code& ec) noexcept
{
    ec.clear();
    char buff[PATH_MAX];
    char *ret = realpath(p_str, buff);
    if (! ret) {
        detail::handle_errno(ec);
        return std::string();
    }
    return std::string(buff);
}

inline void
_statvfs(const char *p_str, struct statvfs svfs, std::error_code& ec)
{
    ec.clear();
    
    if (statvfs(p_str, &svfs) == -1)
        detail::handle_errno(ec);
}

inline perms
_get_perms(const struct stat& st) noexcept
{
    perms pmask = perms::none;
    const mode_t& mode = st.st_mode;
    
    if (S_IRUSR & mode)
        pmask |= perms::owner_read;
    if (S_IWUSR & mode)
        pmask |= perms::owner_write;
    if (S_IXUSR & mode)
        pmask |= perms::owner_exec;
    if (S_IRGRP & mode)
        pmask |= perms::group_read;
    if (S_IWGRP & mode)
        pmask |= perms::group_write;
    if (S_IXGRP & mode)
        pmask |= perms::group_exec;
    if (S_IROTH & mode)
        pmask |= perms::others_read;
    if (S_IWOTH & mode)
        pmask |= perms::others_write;
    if (S_IXOTH & mode)
        pmask |= perms::others_exec;
    if (S_ISUID & mode)
        pmask |= perms::set_uid;
    if (S_ISGID & mode)
        pmask |= perms::set_gid;
    if (S_ISVTX & mode)
        pmask |= perms::sticky_bit;
    
    return pmask;
}
 
    
inline file_status
_status(const path& p, struct stat& path_stat, std::error_code& ec) noexcept
{
    ec.clear();
    
    if (stat(p.c_str(), &path_stat) == -1) {
        detail::handle_errno(ec);
        if (ec.value() == ENOENT || ec.value() == ENOTDIR)
            return file_status(file_type::not_found);
        
        return file_status(file_type::none);
    }
    
    file_status fst;
    
    const mode_t& mode = path_stat.st_mode;
    
    if (S_ISREG(mode))
        fst.type(file_type::regular);
    else if (S_ISDIR(mode))
        fst.type(file_type::directory);
    else if (S_ISBLK(mode))
        fst.type(file_type::block);
    else if (S_ISCHR(mode))
        fst.type(file_type::character);
    else if (S_ISFIFO(mode))
        fst.type(file_type::fifo);
    else if (S_ISSOCK(mode))
        fst.type(file_type::socket);
    else
        fst.type(file_type::unknown);
    
    fst.permissions(detail::_get_perms(path_stat));
    return fst;
}


inline uintmax_t
_file_size(const struct stat & st) noexcept
{
    return static_cast<uintmax_t>(st.st_size);
}
    

inline file_status
_symlink_status(const path& p, struct stat& path_stat, std::error_code & ec) noexcept
{
    ec.clear();
    
    if (lstat(p.c_str(), &path_stat) == -1) {
        detail::handle_errno(ec);
        if (ec.value() == ENOENT || ec.value() == ENOTDIR)
            return file_status(file_type::not_found);
        
        return file_status(file_type::none);
    }
    
    file_status fst;
    const mode_t& mode = path_stat.st_mode;
    
    if (S_ISLNK(mode))
        fst.type(file_type::symlink);
    else if (S_ISREG(mode))
        fst.type(file_type::regular);
    else if (S_ISDIR(mode))
        fst.type(file_type::directory);
    else if (S_ISBLK(mode))
        fst.type(file_type::block);
    else if (S_ISCHR(mode))
        fst.type(file_type::character);
    else if (S_ISFIFO(mode))
        fst.type(file_type::fifo);
    else if (S_ISSOCK(mode))
        fst.type(file_type::socket);
    else
        fst.type(file_type::unknown);
    
    // TODO symbolic link
    fst.permissions(detail::_get_perms(path_stat));
    return fst;
}

inline bool
_file_status_bad(const file_status & st) noexcept
{
    return (st.type() == file_type::none);
}
    
    
inline path
_path_from_env(const char* name)
{
    const char *ret = std::getenv(name);
    if (! ret)
        return path();
    
    return path(ret);
}


inline std::string
_readlink(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    
    struct stat st;
    detail::_status(p, st, ec);
    if (ec)
        return std::string();
    
    std::string tmp;
    char *buff = new char[st.st_size];
    ssize_t ret = readlink(p.c_str(), buff, st.st_size);
    
    if (ret == -1) {
        detail::handle_errno(ec);
    } else {
        tmp = std::string(buff);
    }
    
    delete [] buff;
    return tmp;
}


} /* namespace detail */
} /* namespace  fs */
} /* namespace elib */
#endif /* ELIB_FS_OPERATIONS_HELPER_DEF_H */