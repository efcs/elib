#ifndef ELIB_WEB_BASIC_WEB_ERROR_HPP
#define ELIB_WEB_BASIC_WEB_ERROR_HPP

# include <exception>
# include <memory>
# include <string>

namespace elib { namespace web
{
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class basic_web_error
      : public std::exception
    {
    public:
        explicit basic_web_error(std::string s)
          : m_impl{std::make_shared<std::string>(s)}
        {}
        
        explicit basic_web_error(const char* s)
          : m_impl{std::make_shared<std::string>(s)}
        {}
        
        basic_web_error(basic_web_error const &) = default;
        basic_web_error(basic_web_error &&) = default;
        basic_web_error & operator=(basic_web_error const &) = default;
        basic_web_error & operator=(basic_web_error &&) = default;
        
        virtual const char *what() const noexcept
        {
            return m_impl->c_str();
        }
        
        virtual ~basic_web_error() = default;

    private:
        std::shared_ptr<std::string> m_impl;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
}}                                                       // namespace elib::web
#endif /* ELIB_WEB_BASIC_WEB_ERROR_HPP */