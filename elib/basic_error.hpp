#ifndef ELIB_BASIC_ERROR_HPP
#define ELIB_BASIC_ERROR_HPP

# include <exception>
# include <memory>
# include <string>

namespace elib
{
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class basic_error : public std::exception
    {
    public:
        explicit basic_error(std::string s)
          : m_impl{std::make_shared<std::string>(s)}
        {}
        
        explicit basic_error(const char* s)
          : m_impl{std::make_shared<std::string>(s)}
        {}
        
        basic_error(basic_error const &) = default;
        basic_error(basic_error &&) = default;
        basic_error & operator=(basic_error const &) = default;
        basic_error & operator=(basic_error &&) = default;
        
        virtual const char* what() const noexcept
        {
            return m_impl->c_str();
        }
        
        virtual ~basic_error() = default;

    private:
        std::shared_ptr<std::string> m_impl;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
}                                                           // namespace elib
#endif /* ELIB_BASIC_ERROR_HPP */