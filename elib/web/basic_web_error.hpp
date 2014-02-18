#ifndef ELIB_WEB_BASIC_WEB_ERROR_HPP
#define ELIB_WEB_BASIC_WEB_ERROR_HPP

# include <elib/basic_error.hpp>

namespace elib { namespace web
{
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class basic_web_error
      : public basic_error
    {
    public:
        using basic_error::basic_error;
        
        basic_web_error(basic_web_error const &) = default;
        basic_web_error(basic_web_error &&) = default;
        basic_web_error & operator=(basic_web_error const &) = default;
        basic_web_error & operator=(basic_web_error &&) = default;
        
        virtual ~basic_web_error() = default;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
}}                                                       // namespace elib::web
#endif /* ELIB_WEB_BASIC_WEB_ERROR_HPP */