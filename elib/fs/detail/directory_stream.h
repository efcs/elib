#ifndef ELIB_FS_DIRECTORY_STREAM_H
#define ELIB_FS_DIRECTORY_STREAM_H

#include <elib/fs/path.h>

#include <string>
#include <system_error>

#include <dirent.h>


namespace elib {
namespace fs {
namespace detail {
    
    
class directory_stream {
public:
    typedef struct dirent dirent_t;
    
    directory_stream() = default;
    directory_stream(directory_stream&&) noexcept;
    
    ~directory_stream();
    
    directory_stream&
    operator=(directory_stream&&) noexcept;
    
    bool open(const path& p, std::error_code& ec) noexcept;
    
    bool close(std::error_code& ec) noexcept;
    
    const dirent_t*
    entry() const noexcept;
    
    const dirent_t*
    advance(std::error_code& ec) noexcept;
    
    void rewind(std::error_code& ec) noexcept;
    
    void seek(long pos, std::error_code& ec) noexcept;
    long tell(std::error_code& ec) noexcept;
    
    void clear() noexcept;
    
    void reset() noexcept;
    
    const std::error_code&
    error() noexcept;
    
    bool
    is_open() const noexcept;
    
    bool
    good() const noexcept;
    
    operator bool() const noexcept;
    
private:
    typedef DIR dir_t;
    
    void
    _close() noexcept;
    
    dir_t*
    _get_stream(std::error_code& ec) noexcept;
    
    directory_stream(const directory_stream&);
    
    directory_stream&
    operator=(const directory_stream&);
    
    dir_t *m_dir_stream{nullptr};
    dirent_t m_dirent, *m_dirent_ptr{nullptr};
};
    
    
} /* namespace detail */
} /* namespace fs */
} /* namespace elib */

#endif /* ELIB_FS_DIRECTORY_STREAM_H */