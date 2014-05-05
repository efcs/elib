#ifndef ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP
#define ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP

# include <elib/filesystem/config.hpp>
# include <elib/filesystem/path.hpp>

# include <system_error>
# include <memory>
# include <string>
# include <cerrno>

namespace elib { namespace fs
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

    ////////////////////////////////////////////////////////////////////////////
    //                      MISC ERROR HELPERS                                                      
    ////////////////////////////////////////////////////////////////////////////
    namespace detail 
    {
        ////////////////////////////////////////////////////////////////////////
        constexpr int errc_cast(std::errc e) noexcept
        {
            return static_cast<int>(e);
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline std::error_code capture_errno()
        {
            return std::error_code{errno, std::system_category()};
        }

        ////////////////////////////////////////////////////////////////////////
        inline void capture_errno(std::error_code & ec)
        {
            ec = capture_errno();
        }

        ////////////////////////////////////////////////////////////////////////
        inline std::error_code handle_error(int xerrno)
        {
            return std::error_code{xerrno, std::system_category()};
        }

        ////////////////////////////////////////////////////////////////////////
        inline std::error_code handle_error(std::errc err_code)
        {
            return std::make_error_code(err_code);
        }

        ////////////////////////////////////////////////////////////////////////
        inline void handle_error(int xerrno, std::error_code& ec)
        {
            ec = handle_error(xerrno);
        }
        
        inline void
        handle_error(std::errc err_code, std::error_code& ec)
        {
            ec = handle_error(err_code);
        }

        inline void clear_error(std::error_code *ec)
        {
            if (ec) ec->clear();
        }

        inline int clear_errno()
        {
            int xerrno = errno;
            errno = 0;
            return xerrno;
        }
        
        inline bool handle_and_throw_error(int xerrno, 
                                        const std::string& msg, std::error_code *ec)
        {
            auto m_ec = handle_error(xerrno);
            if (!m_ec) return false;
            ec != nullptr ? *ec = m_ec : throw filesystem_error(msg, m_ec);
            return true;
        }

        
        inline bool handle_and_throw_error(int xerrno, 
                        const std::string& msg, const path& p1, std::error_code *ec)
        {
            auto m_ec = handle_error(xerrno);
            if (!m_ec) return false;
            ec != nullptr ? *ec = m_ec : throw filesystem_error(msg, p1, m_ec);
            return true;
        }

        inline bool handle_and_throw_error(int xerrno, 
                                            const std::string& msg, const path& p1,
                                            const path& p2, std::error_code *ec)
        {
            auto m_ec = handle_error(xerrno);
            if (!m_ec) return false;
            ec != nullptr ? *ec = m_ec : throw filesystem_error(msg, p1, p2, m_ec);
            return true;
        }
        
        inline bool handle_and_throw_errno(const std::string& msg, 
                        std::error_code *ec)
        {
            return handle_and_throw_error(clear_errno(), msg, ec);
        }

        inline bool handle_and_throw_errno(const std::string& msg, const path& p1,
                        std::error_code *ec)
        { 
            return handle_and_throw_error(clear_errno(), msg, p1, ec);
        }

        inline bool handle_and_throw_errno(const std::string& msg, const path& p1,
                                            const path& p2, std::error_code *ec)
        {
            return handle_and_throw_error(clear_errno(), msg, p1, p2, ec);
        }

        inline bool handle_and_throw_error(std::errc err_code, 
                        const std::string& msg, std::error_code *ec)
        {
            return handle_and_throw_error(static_cast<int>(err_code), msg, ec);
        }

        inline bool handle_and_throw_error(std::errc err_code, 
                        const std::string& msg, const path& p1, std::error_code *ec)
        {
            return handle_and_throw_error(static_cast<int>(err_code), msg, p1, ec);
        }

        inline bool handle_and_throw_error(std::errc err_code, 
                        const std::string& msg, const path& p1,
                        const path& p2, std::error_code *ec)
        {
            return handle_and_throw_error(static_cast<int>(err_code),
                    msg, p1, p2, ec);
        }
    }                                                       // namespace detail
}}                                                        // namespace elib::fs
#endif /* ELIB_FILESYSTEM_FILESYSTEM_ERROR_HPP */