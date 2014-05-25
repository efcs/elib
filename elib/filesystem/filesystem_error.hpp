#ifndef ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP
#define ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP

# include <elib/filesystem/config.hpp>
# include <elib/filesystem/path.hpp>
# include <elib/assert.hpp>
# include <elib/fmt.hpp>
# include <system_error>
# include <memory>
# include <string>
# include <utility>
# include <cerrno>

namespace elib { namespace fs { inline namespace v1
{

# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class filesystem_error : public std::system_error 
    {
    public:
        filesystem_error(const std::string& what_arg, std::error_code ec)
            : std::system_error(ec, what_arg)
            , m_impl(std::make_shared<storage_t>())
        {
        }
            
        /// NOTE: two parameters have to be given to make_shared (ie pair<path, path>)
        /// to prevent ambigious overload resolution
        filesystem_error(
            const std::string& what_arg
          , const path& p, std::error_code ec
          )
            : std::system_error(ec, what_arg)
            , m_impl(std::make_shared<storage_t>(p, path()))
        {}
            
        filesystem_error(
            const std::string& what_arg
          , const path& p1, const path& p2
          , std::error_code ec
          )
            : std::system_error(ec, what_arg)
            , m_impl(std::make_shared<storage_t>(p1, p2))
        {}
            
        path const & path1() const noexcept { return m_impl->first; }
        path const & path2() const noexcept { return m_impl->second; }
            
    private:
        using storage_t = std::pair<path, path>;
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