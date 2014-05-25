#ifndef ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP
#define ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP

# include <elib/filesystem/config.hpp>
# include <elib/filesystem/path.hpp>
# include <elib/assert.hpp>
# include <elib/fmt.hpp>
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
            : std::system_error{ec}, m_impl(std::make_shared<storage_t>())
        {
            m_impl->what_arg = elib::fmt("%s: %s ", ec.message(), what_arg);
        }
            
        filesystem_error(const std::string& what_arg, const path& p,
                        std::error_code ec)
            : std::system_error{ec}, m_impl{std::make_shared<storage_t>(p)}
        {
            m_impl->what_arg = elib::fmt("%s: %s (path=%s)", ec.message(), what_arg, p.native());
        }
            
        filesystem_error(const std::string& what_arg, const path& p1,
                        const path& p2, std::error_code ec)
            : std::system_error{ec}, m_impl(std::make_shared<storage_t>(p1, p2))
        {
            m_impl->what_arg = elib::fmt("%s: %s (path=%s) (path=%s)"
              , ec.message(), what_arg, p1.native(), p2.native()
              );
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
        
        struct storage_t
        {
            storage_t() {}
            
            storage_t(path xp1) 
              : p1(elib::move(xp1))
            {}
              
            storage_t(path xp1, path xp2) 
              : p1(elib::move(xp1)), p2(elib::move(xp2))
            {}
            
            path p1, p2;
            std::string what_arg;
        };
            
        std::shared_ptr<storage_t> m_impl;
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