#ifndef ELIB_WEB_PROXY_ERROR_HPP
#define ELIB_WEB_PROXY_ERROR_HPP

# include <elib/web/fwd.hpp>
# include <elib/web/basic_web_error.hpp>
# include <elib/aux.hpp>

# include <string>

namespace elib { namespace web
{
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    ////////////////////////////////////////////////////////////////////////////
    //
    class proxy_error
      : public basic_web_error
    {
    public:
        using basic_web_error::basic_web_error;
        
        ELIB_DEFAULT_COPY_MOVE(proxy_error);
        
        virtual ~proxy_error() = default;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class proxy_protocol_error
      : public proxy_error
    {
    public:
        proxy_protocol_error(std::string s, http_status st)
          : proxy_error(static_cast<std::string &&>(s)), m_st{st}
        {}
        
        proxy_protocol_error(const char *s, http_status st)
          : proxy_error(s), m_st{st}
        {}
        
        using proxy_error::proxy_error;
        
        ELIB_DEFAULT_COPY_MOVE(proxy_protocol_error);
        
        http_status status() const noexcept
        { return m_st; }
        
        virtual ~proxy_protocol_error() = default;

    private:
        http_status m_st{};
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class proxy_internal_error
      : public proxy_error
    {
    public:
        using proxy_error::proxy_error;
        
        ELIB_DEFAULT_COPY_MOVE(proxy_internal_error);
        
        virtual ~proxy_internal_error() = default;
    };
    
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
}}                                                       // namespace elib::web
#endif /* ELIB_WEB_PROXY_ERROR_HPP */