#ifndef ELIB_WEB_BASIC_PROX_ERROR_HPP
#define ELIB_WEB_BASIC_PROX_ERROR_HPP

# include <exception>
# include <memory>
# include <string>

namespace elib { namespace web
{
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class basic_prox_error
      : public std::exception
    {
    public:
        explicit basic_prox_error(std::string s)
          : m_impl{std::make_shared<std::string>(elib::move(s))}
        {}
        
        explicit basic_prox_error(const char* s)
          : m_impl{std::make_shared<std::string>(s)}
        {}
        
        basic_prox_error(basic_prox_error const &) = default;
        basic_prox_error(basic_prox_error &&) = default;
        basic_prox_error & operator=(basic_prox_error const &) = default;
        basic_prox_error & operator=(basic_prox_error &&) = default;
        
        virtual const char *what() const noexcept
        {
            return m_impl->c_str();
        }
        
        virtual ~basic_prox_error() = default;

    private:
        std::shared_ptr<std::string> m_impl;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
}}                                                       // namespace elib::web
#endif /* ELIB_WEB_BASIC_PROX_ERROR_HPP */