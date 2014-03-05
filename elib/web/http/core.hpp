#ifndef ELIB_WEB_HTTP_CORE_HPP
#define ELIB_WEB_HTTP_CORE_HPP

# include <elib/web/http/fwd.hpp>
# include <elib/aux.hpp>
# include <elib/enumeration.hpp>
# include <elib/lexical_cast.hpp>
# include <algorithm>
# include <string>
# include <vector>
# include <utility>

namespace elib { namespace web { namespace http
{
   
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class version
    {
        ONE_ZERO, 
        ONE_ONE
    };
    
/* I don't care If clang thinks the default case is covered.
 * All it takes is one bad cast, or uninitialized enum, and
 * these assumptions go to shit.*/
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wcovered-switch-default"
#   pragma clang diagnostic ignored "-Wunreachable-code"
# endif
    ////////////////////////////////////////////////////////////////////////////
    //
    inline std::string version_to_string(version v)
    {
        switch (v)
        {
            case version::ONE_ZERO:
                return "HTTP/1.0";
            case version::ONE_ONE:
                return "HTTP/1.1";
            default:
                throw "In default case!";
        }
    }
    
    inline std::string to_string(version v)
    {
        return version_to_string(v);
    }
    
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline version string_to_version(std::string const & s)
    {
        if (s == "HTTP/1.0")
            return version::ONE_ZERO;
        else if (s == "HTTP/1.1")
            return version::ONE_ONE;
        else
            throw "In default case!";
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class method
    {
        none = 0, 
        OPTIONS, 
        GET, 
        HEAD,
        POST, 
        PUT, 
        DELETE,
        TRACE, 
        CONNECT
    };
}}}                                                // namespace elib::web:http

namespace elib { namespace enumeration
{
    ////////////////////////////////////////////////////////////////////////////
    //
    template <>
    struct basic_enum_traits<::elib::web::http::method>
    {
        using EnumType = ::elib::web::http::method;
        
        static const std::map<EnumType, std::string> name_map;
        
        static constexpr const EnumType ELIB_ENUM_FIRST_VALUE = EnumType::OPTIONS;
        static constexpr const EnumType ELIB_ENUM_LAST_VALUE = EnumType::CONNECT;
        
        static constexpr const bool ELIB_ENUM_IS_CONTIGIOUS = true;
    };
}}                                               // namespace elib::enumeration
    
namespace elib { namespace web { namespace http
{
    
    inline std::string to_string(method m)
    {
        return elib::enumeration::enum_cast<std::string>(m);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class status
    {
        none = 0, 

        CONTINUE = 100, 
        SWITCH_PROTOCOL = 101,
        
        OK = 200, 
        CREATED = 201,
        ACCEPTED = 202, 
        NON_AUTH_INFORMATION = 203, 
        NO_CONTENT = 204, 
        RESET_CONTENT = 205,
        PARTIAL_CONTENT = 206, 
        
        REDIRECT_CHOICE = 300, 
        REDIRECT_MOVED_PERM = 301, 
        REDIRECT_FOUND = 302, 
        REDIRECT_SEE_OTHER = 303,
        REDIRECT_NOT_MODIFIED = 304, 
        REDIRECT_USE_PROXY = 305, 
        //REDIRECT_UNUSED = 306, 
        REDIRECT_TEMP = 307, 
        
        BAD_REQUEST = 400, 
        UNAUTHORIZED = 401, 
        PAYMENT_REQUIRED = 402, 
        FORBIDDEN = 403, 
        NOT_FOUND = 404, 
        METHOD_NOT_ALLOWED = 405, 
        NOT_ACCEPTABLE = 406, 
        PROXY_AUTH_REQUIRED = 407, 
        REQUEST_TIMEOUT = 408, 
        CONFLICT = 409, 
        GONE = 410, 
        LENGTH_REQUIRED = 411, 
        PRECONDITION_FAILED = 412, 
        REQUEST_ENTITY_TOO_LARGE = 413, 
        REQUEST_URI_TOO_LARGE = 414, 
        UNSUPPORTED_MEDIA_TYPE = 415,
        REQUEST_RANGE_NOT_SATISFIABLE = 416, 
        EXPECTATION_FAILED = 417, 
        
        INTERNAL_SERVER_ERROR = 500, 
        NOT_IMPLEMENTED = 501, 
        BAD_GATEWAY = 502, 
        SERVICE_UNAVAILABLE = 503, 
        GATEWAY_TIMEOUT = 504, 
        HTTP_VERSION_UNSUPPORTED = 505
    };
}}}                                                // namespace elib::web::http

namespace elib { namespace enumeration
{
    ////////////////////////////////////////////////////////////////////////////
    //
    template <>
    struct basic_enum_traits<::elib::web::http::status>
    {
        static const std::map<::elib::web::http::status, std::string> name_map;
    };
}}                                               // namespace elib::enumeration
    
namespace elib { namespace web { namespace http
{
    inline std::string to_string(status s)
    {
        return elib::enumeration::enum_cast<std::string>(s);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_information(status s) noexcept
    {
        using UnderT = aux::underlying_type_t<status>;
        return (static_cast<UnderT>(s) >= 100 
            && static_cast<UnderT>(s) <= 199);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_success(status s) noexcept
    {
        using UnderT = aux::underlying_type_t<status>;
        return (static_cast<UnderT>(s) >= 200
             && static_cast<UnderT>(s) <= 299);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_redirect(status s) noexcept
    {
        using UnderT = aux::underlying_type_t<status>;
        return (static_cast<UnderT>(s) >= 300
             && static_cast<UnderT>(s) <= 399);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_client_error(status s) noexcept
    {
        using UnderT = aux::underlying_type_t<status>;
        return (static_cast<UnderT>(s) >= 400
             && static_cast<UnderT>(s) <= 499);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_server_error(status s) noexcept
    {
        using UnderT = aux::underlying_type_t<status>;
        return (static_cast<UnderT>(s) >= 500
             && static_cast<UnderT>(s) <= 599);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_error(status s) noexcept
    {
        return (status_is_client_error(s) || status_is_server_error(s));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class EnumType>
    struct message_header
    {
        version http_version;
        EnumType code;
        std::string value;
    };
    
    template <class HeaderType>
    struct message
    {
        using header_type = HeaderType;
        
        header_type header;
        std::vector<field_type> fields;
        data_type data;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <status Status>
    response generate_status_response()
    {
        response r;
        r.header.http_version = version::ONE_ZERO;
        r.header.code = Status;
        r.header.value = to_string(Status);
        return r;
    }


    template <
        class Header
      , class T
      , ELIB_ENABLE_IF(
          elib::is_valid_lexical_cast<
              std::string, aux::uncvref<T>
          >::value
       )
    >
    void insert_field(
        message<Header> & dest
      , std::string const & key
      , T && v
    )
    {
        dest.fields.push_back(std::make_pair(
            key
          , elib::lexical_cast<std::string>(elib::forward<T>(v))
        ));
    }
    
    template <
        class T
      , ELIB_ENABLE_IF(
          elib::is_valid_lexical_cast<
              std::string, aux::uncvref<T>
          >::value
        )
    >
    void insert_field(
        std::vector<field_type> & dest
      , std::string const & key
      , T && v
    )
    {
        dest.push_back(std::make_pair(
            key
          , elib::lexical_cast<std::string>(elib::forward<T>(v))
        ));
    }
    
    template <class Header>
    void insert_field(
        message<Header> & dest
      , field_type const & f
    )
    {
        dest.fields.push_back( f );
    }
    
    inline void 
    insert_field(
        std::vector<field_type> & dest
      , field_type && f
    )
    {
        dest.push_back(
            static_cast<field_type &&>(f)
        );
    }
    
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline std::vector<field_type>::const_iterator
    find_field(std::vector<field_type> const & v, std::string const & key)
    {
        return std::find_if(v.begin(), v.end()
                    , [&](field_type const & f) { return f.first == key; });
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline std::vector<field_type>::iterator
    find_field(std::vector<field_type> & v, std::string const & key)
    {
        return std::find_if(v.begin(), v.end()
                          , [&](field_type const & f) { return f.first == key; }); 
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline bool
    remove_field(std::vector<field_type> & v, std::string const & key)
    {
        auto it = std::remove_if(v.begin(), v.end()
                        , [&](field_type const & f) { return f.first == key; });
        return it != v.end();
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline bool
    replace_field(std::vector<field_type> & v, std::string const & key
                     , std::string const & replacement)
    {
        field_type new_val{key, replacement};
        bool found = false;
        std::replace_if(v.begin(), v.end()
                     , [&](field_type const & f) 
                       {
                            if (f.first == key)
                                found = true;
                            return (f.first == key); 
                       }
                     , new_val); 
        return found;
    }
    
}}}                                                         // namespace elib
#endif /* ELIB_WEB_HTTP_CORE_HPP */