#include <elib/fs/detail/directory_stream.h>


namespace elib {
namespace fs {
namespace detail {


void
directory_stream::open(const fs::path& p) noexcept
{
    reset();
    
    m_root_path = p;
    
    errno = 0;
    m_dir_stream = opendir(m_root_path.c_str());
    
    /* upon failure, clear errno, set fail */
    if (! m_dir_stream) {
        detail::handle_errno(m_ec);
        _set_fail();
    }
}

void
directory_stream::close() noexcept
{
    /* if not open, set fail and return */
   if (!_require_open())
       return;
    
    errno = 0;
    int ret = closedir(m_dir_stream);
    _reset(); // reset all variables
    if (ret == -1) {
        detail::handle_errno(m_ec);
        _set_fail();
    }
}


const fs::path&
directory_stream::entry() noexcept
{
    if (!_require_open() || !good()) {
        _set_fail();
        _make_sentinal();
        return m_curr_path;
    }
    
    /* clear errno, just in case */
    errno = 0;
    dirent_t *de = readdir(m_dir_stream);
    
    /* if ret == NULL then either an error has occured
     * (and errno is set). otherwise we have reached end of stream */
    if (! de) {
        _make_sentinal();
        
        if (errno != 0) {
            detail::handle_errno(m_ec);
            _set_bad();
        } else {
            _set_eof();
        }
    } 
    else { // readdir passed
        m_curr_path = m_root_path / de->d_name;
    }
    
    return m_curr_path;
}

const fs::path&
directory_stream::advance() noexcept
{
    if (!is_open() || !good()) {
        _set_fail();
        _make_sentinal();
        return m_curr_path;
    }
    
    // prepare & call readdir_r
    dirent_t de;
    dirent_t *de_ptr{nullptr};
    
    int ret = readdir_r(m_dir_stream, &de, &de_ptr);
    
    if (ret != 0) {
        detail::handle_error(ret, m_ec);
        _set_bad();
        _make_sentinal();
        return m_curr_path;
    }
    
    // if de_ptr == NULL, then we are at eof
    if (de_ptr == nullptr) {
        _set_eof();
        _make_sentinal();
        return m_curr_path;
    }
    
    m_curr_path = m_root_path / de.d_name;
    return m_curr_path;
}

void
directory_stream::rewind() noexcept
{
    if (!_require_open() || bad())
        return;
    
    rewinddir(m_dir_stream);
    _set_eof(false);
    _set_fail(false);
}

long
directory_stream::tell() const noexcept
{
    if (!_require_open() || bad())
        return -1;
    
    errno = 0;
    long ret = telldir(m_dir_stream);
    
    if (ret == -1) {
        detail::handle_errno(m_ec);
        _set_bad();
    }
    
    return ret;
}

void
directory_stream::seek(long pos) noexcept
{
    if (!_require_open() || bad()) 
        return;
    
    seekdir(m_dir_stream, pos);
}


void
directory_stream::copy(const directory_stream& other) noexcept
{
    reset(); // close our resources
    
    // if other is currently open,
    // attempt to match it's current position
    if (other.is_open()) {
        // if failure occurs on matching abort
        if (! _match_stream(other))
            return;
    } else { 
        m_curr_path = other.m_curr_path;
    }
    //TODO
    // copy other information
    m_state = other.m_state;
    m_ec = other.m_ec;
    m_curr_path = other.m_curr_path;
}

void
directory_stream::move(directory_stream&& other) noexcept
{
    reset(); // close our resources
    
    // copy other
    m_root_path = std::move(other.m_root_path);
    m_curr_path = std::move(other.m_curr_path);
    m_dir_stream = other.m_dir_stream;
    m_state = other.m_state;
    m_ec = std::move(other.m_ec);
    // destroy other, without closing its resources
    other._reset();
}

////////////////////////////////////////////////////////////////////////////////
//                            private members                                           
////////////////////////////////////////////////////////////////////////////////

/* precondition: m_dir_stream has been closed */
bool
directory_stream::_match_stream(const directory_stream& other) noexcept
{
    if (!other.is_open() || other.bad())
        return false;
    
    open(other.m_root_path);
    if (! is_open())
        return false;
    
    std::error_code ec;
    long pos = other.tell(ec);
    if (pos == -1) {
        m_ec = ec;
        //TODO
        return false;
    }
    
    seek(pos);
    if (ec)
        return false;
    return true;
}

  
  
} /* namespace detail */
} /* namespace fs */
} /* namespace elib */