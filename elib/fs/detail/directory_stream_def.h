#ifndef ELIB_FS_DIRECTORY_STREAM_DEF_H
#define ELIB_FS_DIRECTORY_STREAM_DEF_H

#include <elib/fs/detail/filesystem_error_helper.h>

#include <system_error>
#include <utility>


namespace elib {
namespace fs {
namespace detail {
    
    
    
directory_stream::directory_stream(directory_stream&& other) noexcept
{
    *this = std::move(other);
}

directory_stream::~directory_stream()
{
    reset();
}

directory_stream&
directory_stream::operator=(directory_stream&& other) noexcept
{
    reset();
    
    m_dir_stream = other.m_dir_stream;
    m_dirent = other.m_dirent;
    if (other.m_dirent_ptr == nullptr)
        m_dirent_ptr = nullptr;
    else
        m_dirent_ptr = &m_dirent;
    
    return *this;
}
    
   
bool
directory_stream::open(const path& p, std::error_code& ec) noexcept
{
    reset();
    ec.clear();
    
    m_dir_stream = opendir(p.c_str());
    if (! m_dir_stream) {
        detail::handle_errno(ec);
        return false;
    }
    return true;
}

bool
directory_stream::close(std::error_code& ec) noexcept
{
    auto dir_stream = _get_stream(ec);
    if (ec)
        return false;
    
    int ret = closedir(dir_stream);
    m_dir_stream = nullptr;
    
    if (ret == -1) {
        detail::handle_errno(ec);
        return false;
    }
    
    return true;
}

const directory_stream::dirent_t*
directory_stream::entry() const noexcept
{
    return m_dirent_ptr;
}

const directory_stream::dirent_t*
directory_stream::advance(std::error_code& ec) noexcept
{
    ec.clear();
    ((void)_get_stream(ec));
    if (ec)
        return nullptr;
    
    auto ret = readdir_r(m_dir_stream, &m_dirent, &m_dirent_ptr);
    if (ret != 0) {
        detail::handle_error(ret, ec);
        return nullptr;
    }
    
    return m_dirent_ptr;
}

void
directory_stream::rewind(std::error_code& ec) noexcept
{

    auto dir_stream = _get_stream(ec);
    if (ec)
        return;
   
    rewinddir(dir_stream);
}

void
directory_stream::seek(long pos, std::error_code& ec) noexcept
{
    ec.clear();
    auto dir_stream = _get_stream(ec);
    if (ec)
        return;
    seekdir(dir_stream, pos);
}

long
directory_stream::tell(std::error_code& ec) noexcept
{
    ec.clear();
    auto dir_stream = _get_stream(ec);
    if (ec)
        return static_cast<long>(-1);
    return telldir(dir_stream);
}


void
directory_stream::reset() noexcept
{
    _close();
    m_dirent_ptr = nullptr;
    m_dir_stream  = nullptr;
}

bool
directory_stream::is_open() const noexcept
{
    return (m_dir_stream != nullptr);
}

bool
directory_stream::good() const noexcept
{
    return (is_open() && m_dirent_ptr);
}
    

directory_stream::operator bool() const noexcept
{ 
    return good();
}

directory_stream::dir_t*
directory_stream::_get_stream(std::error_code& ec) noexcept
{
    if (m_dir_stream == nullptr)
        detail::handle_error(std::errc::bad_file_descriptor, ec);
    
    return m_dir_stream;
}

void
directory_stream::_close() noexcept
{
    if (m_dir_stream) {
        if (closedir(m_dir_stream) == -1)
            errno = 0;
    }
}


    
} /* namespace detail */
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_DIRECTORY_STREAM_DEF_H */