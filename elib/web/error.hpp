#ifndef ELIB_WEB_ERROR_HPP
#define ELIB_WEB_ERROR_HPP

# include <elib/except.hpp>

namespace elib { namespace web
{
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class web_error : public elib::exception
    {
    public:
        using elib::exception::exception;
        
        web_error(web_error const &) = default;
        web_error(web_error &&) = default;
        web_error & operator=(web_error const &) = default;
        web_error & operator=(web_error &&) = default;
        
        virtual ~web_error() = default;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
}}                                                       // namespace elib::web
namespace elib { using elib::web::web_error; }
#endif /* ELIB_WEB_BASIC_WEB_ERROR_HPP */