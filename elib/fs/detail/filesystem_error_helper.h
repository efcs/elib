#ifndef ELIB_FS_FILESYSTEM_ERROR_HELPER_H
#define ELIB_FS_FILESYSTEM_ERROR_HELPER_H


#include <elib/fs/path.h>
#include <elib/fs/filesystem_error.h>


#include <system_error>
#include <string>


namespace elib {
namespace fs {
namespace detail {
    

inline void
handle_errno(std::error_code & ec)
{    
    ec.assign(errno, std::system_category());
    errno = 0;
}

inline std::error_code
handle_errno()
{
    std::error_code ec{errno, std::system_category()};
    errno = 0;
    return ec;
}

inline std::error_code
handle_error(int xerrno)
{
    return std::error_code(xerrno, std::system_category());
}

inline void
handle_error(int xerrno, std::error_code & ec)
{
    ec.assign(xerrno, std::system_category());
}

inline void
handle_error(std::errc err_code, std::error_code & ec)
{
    ec = std::make_error_code(err_code);
}

inline std::error_code
handle_error(std::errc err_code)
{
    return std::make_error_code(err_code);
}


inline void
handle_and_throw_errno()
{
    std::error_code ec{errno, std::system_category()};
    errno = 0;
    throw filesystem_error(ec.message(), ec);
}

inline void
handle_and_throw_errno(const path& p1)
{
    auto ec = handle_errno();
    throw filesystem_error(ec.message(), p1, ec);
}

inline void
handle_and_throw_errno(const path& p1, const path& p2)
{
    auto ec = handle_errno();
    throw filesystem_error(ec.message(), p1, p2, ec);
}
  
inline void
handle_and_throw_errno(const std::string & s)
{
    std::error_code ec{errno, std::system_category()};
    errno = 0;
    throw filesystem_error(s, ec);
}

inline void
handle_and_throw_errno(const std::string & s, const path& p1)
{
    auto ec = handle_errno();
    throw filesystem_error(s, p1, ec);
}

inline void
handle_and_throw_errno(const std::string & s, const path& p1, const path& p2)
{
    auto ec = handle_errno();
    throw filesystem_error(s, p1, p2, ec);
}
    
} /* namespace detail */
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_FILESYSTEM_ERROR_HELPER_H */