#ifndef ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP
#define ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP

# include <elib/filesystem/config.hpp>
# include <elib/filesystem/path.hpp>
# include <elib/assert.hpp>
# include <system_error>
# include <memory>
# include <string>
# include <cerrno>

namespace elib { namespace fs { inline namespace v1
{

# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class filesystem_error 
      : public std::system_error 
    {
    public:

        filesystem_error(const std::string& what_arg, std::error_code ec)
            : std::system_error{ec}, m_impl{std::make_shared<impl_t>()}
        {
            m_impl->what_arg = what_arg;
        }
            
        filesystem_error(const std::string& what_arg, const path& p,
                        std::error_code ec)
            : filesystem_error{what_arg, ec}
        {
            m_impl->p1 = p;
        }
            
        filesystem_error(const std::string& what_arg, const path& p1,
                        const path& p2, std::error_code ec)
            : filesystem_error{what_arg, p1, ec}
        {
            m_impl->p2 = p2;
        }
            
        const path&
        path1() const noexcept
        { return m_impl->p1; }
            
        const path&
        path2() const noexcept
        { return m_impl->p2; }
            
        //TODO add meaningful message
        const char* 
        what() const noexcept
        { return m_impl->what_arg.c_str(); } 
            
    private:
        
        struct impl_t 
        {
            std::string what_arg {};
            path p1 {};
            path p2 {};
        };
            
        std::shared_ptr<impl_t> m_impl;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

    namespace detail 
    {
        ////////////////////////////////////////////////////////////////////////
        inline std::error_code capture_errno()
        {
            ELIB_ASSERT(errno);
            return std::error_code{errno, std::system_category()};
        }
    }                                                       // namespace detail
}}}                                                       // namespace elib::fs
#endif /* ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP */