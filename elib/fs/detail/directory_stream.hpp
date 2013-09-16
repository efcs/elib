#ifndef ELIB_FS_DIRECTORY_STREAM_HPP
#define ELIB_FS_DIRECTORY_STREAM_HPP

#include <elib/fs/path.hpp>
#include <elib/fs/filesystem_error.hpp>

#include <string>
#include <system_error>
#include <utility>

#include <dirent.h>


namespace elib {
namespace fs {
namespace detail {
    

    
class directory_stream {
public:
//
// ctor & dtor 
//
    directory_stream() = default;
    
    directory_stream(directory_stream&& other)
    { move(std::move(other)); }
    
    
    directory_stream& 
    operator=(directory_stream&& other)
    { 
        move(std::move(other)); 
        return *this;
    }
    
    ~directory_stream()
    { 
        close(); 
    }
//
// dirstream operations
//
    bool is_open() const noexcept
    { return (m_dir_stream != nullptr); }
    
    /* on success, state is cleared,
     * otherwise fail is set */
    void open(const fs::path& p) noexcept;
    
    void open(const fs::path& p, std::error_code& ec) noexcept
    {
        open(p);
        ec = m_ec;
    }
    
    /* on success, state is cleared,
     * otherwise, fail is set */
    void close() noexcept;
    
    void close(std::error_code& ec) noexcept
    {
        close();
        ec = m_ec;
    }
    
    
//
// current position & advance
//
    /* return the current contents of the direntry struct,
     * only use if you have not modified the object since
     * the last call to entry or advance */
    const fs::path&
    get() const noexcept
    { return m_curr_path; }
    
    /* reread and return the current direntry from
     * the stream */
    const fs::path&
    entry() noexcept;
    
    const fs::path&
    entry(std::error_code& ec) noexcept
    {
        auto&& ret = entry();
        ec = m_ec;
        return ret;
    }
    
    /* move to the next directory entry,
     * if EOF, then dirent_t is set as specified
     * in entry() and the eof bit is set */
    const fs::path&
    advance() noexcept;
    
    const fs::path&
    advance(std::error_code& ec) noexcept
    {
        auto&& ret = advance();
        ec = m_ec;
        return ret;
    }
    
    /* move to the beginning of the directory,
     * on success, the EOF bit is cleared and the first entry
     * is reread into entry() */
    void rewind() noexcept;
    
    void rewind(std::error_code& ec) noexcept
    {
        rewind();
        ec = m_ec;
    }

    
//
//  positioning
//   
    // npos is returned when tell() fails
    long tell() const noexcept;
    
    long tell(std::error_code& ec) const noexcept
    {
        auto&& ret = tell();
        ec = m_ec;
        return ret;
    }
    
    // move to the position as specified by pos
    void seek(long pos) noexcept;
    
    void seek(long pos, std::error_code& ec) noexcept
    {
        seek(pos);
        ec = m_ec;
    }
    
//
// state functions
//
    // no error has occured
    bool good() const noexcept
    { return (m_state == goodbit); }
    
    // at end of stream
    bool eof() const noexcept
    { return (m_state & eofbit); }
    
    // recoverable error
    bool fail() const noexcept
    { return ((m_state & failbit) || bad()); }
    
    // non-recoverable error, denoted using ec instead of a bit-field
    bool bad() const noexcept
    { return (m_state & badbit); }
        
    
    // as if by fail();
    bool operator!() const noexcept
    { return !good(); }
    
    // as if by good();
    operator bool() const noexcept
    { return good(); }
    
    // return the error_code currently
    // held by the object
    const std::error_code& 
    error() const noexcept
    { return m_ec; }
    
    // clear state bitmask
    void clear() noexcept
    { 
        m_state = goodbit;
        m_ec.clear();
    }
    
//
// copy & move
//
    /* since the underlying implementation is
     * hostile to copying, this function should
     * only be used as a last resort. if directory
     * modifications have happened between the last
     * call to open, or rewind, then the information
     * used to copy may not be valid */
    void copy(const directory_stream& other) noexcept;
    
    void copy(const directory_stream& other, std::error_code& ec) noexcept
    {
        copy(other);
        ec = m_ec;
    }
    
    /* close currently held resources,
     * then take the stream from other */
    void move(directory_stream&&) noexcept;
    
//
// data member access
//
    
    const fs::path& 
    root_path() const noexcept
    { return m_root_path; }
    

    void reset() noexcept
    {
        close();
        _reset();
    }
    
private:
    // dir stream type
    typedef DIR dir_t;
    // because I don't like C syntax,
    // but love its naming conventions
    typedef struct dirent dirent_t;
    
    // bit-field representing stream state
    // similar to std::ios_base::iostate
    typedef char state_t;
    static constexpr state_t goodbit = 0;
    static constexpr state_t eofbit = 1;
    static constexpr state_t failbit = 2;
    static constexpr state_t badbit = 4;
    
    bool _require_open() const noexcept
    {
        if (! is_open()) {
            detail::handle_error(std::errc::bad_file_descriptor, m_ec);
            _set_fail();
            return false;
        }
        return true;
    }
    
    // used by copy to move to correct position
    bool _match_stream(const directory_stream&) noexcept;
    
    void _make_sentinal()
    { 
        m_curr_path = path();
    }
    
    // modify state, state is mutable,
    // so operations like tell() can be marked as const
    // and still set the fail bit 
    void _set_state(state_t mask, bool value=true) const noexcept
    { 
        if (value)
            m_state |= mask;
        else
            m_state &= ~mask;
    }
    
    void _set_eof(bool val=true) const noexcept
    { _set_state(eofbit, val); }
    
    void _set_fail(bool val=true) const noexcept
    { _set_state(failbit, val); }
    
    void _set_bad(bool val=true) const noexcept
    { _set_state(badbit, val); }
    
    // free resources and clear all state
    void _reset() noexcept
    {
        m_root_path = path();
        m_curr_path = path();
        m_dir_stream = nullptr;
        m_state = goodbit;
        m_ec.clear();
    }
private:    
    // constructing path,
    // required for copy
    fs::path m_root_path;
    // the object storing the current path in the stream
    fs::path m_curr_path;
    
    // readdir stream pointer
    dir_t *m_dir_stream{nullptr};
    
    // stores stream state information
    // see note above for mutable rational
    mutable state_t m_state;
    // for reporting errors to concerned parties
    mutable std::error_code m_ec;
};
 
    
} /* namespace detail */
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_DIRECTORY_STREAM_HPP */