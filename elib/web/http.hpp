#ifndef ELIB_WEB_HTTP_HPP
#define ELIB_WEB_HTTP_HPP

# include <elib/config.hpp>
# if !defined(ELIB_CONFIG_HAS_REGEX)
#   error "elib::web::http requires std::regex " \
          "please use the CMake option CONFIG_LIB_WEB to disable this library"
# endif

# include <elib/aux.hpp>
/* elib::enumeration is a side-project of mine. It provides checked casting
 * from strings to enums, and vis versa */
# include <elib/enumeration.hpp>

# include <algorithm>
# include <map>
# include <memory>
# include <string>
# include <vector>

////////////////////////////////////////////////////////////////////////////////
//                                HTTP
////////////////////////////////////////////////////////////////////////////////
namespace elib { namespace web
{
    
     /* because \n just won't do the trick
     * initialization format is needed to prevent extra null (i think?) */
    constexpr const char http_newl[] = {'\r', '\n'};
    
    /* ONE_ZERO, ONE_ONE */
    enum class http_version;
    /* OPTIONS, GET, HEAD, ect. */
    enum class http_method;
    /* OK, BAD_REQUEST, FORBIDDEN, ect. */
    enum class http_status;
    
    // Expects/returns format "HTTP/1.x"
    const char* version_to_string(http_version);
    http_version string_to_version(std::string const &);
    
    constexpr bool status_is_information(http_status) noexcept;
    constexpr bool status_is_success(http_status) noexcept;
    constexpr bool status_is_redirect(http_status) noexcept;
    constexpr bool status_is_client_error(http_status) noexcept;
    constexpr bool statis_is_server_error(http_status) noexcept;
    constexpr bool status_is_error(http_status) noexcept;
    
    /* The idiomatic C++ void* */
    using http_data = std::vector<char>;
    
    /* a single field. key and value*/
    struct http_field;
    
    // the first line of the HTTP request/response
    struct http_request_header;
    struct http_response_header;
    
    // http_request and http_response
    // have a header, a set of fields, and data
    struct http_request;
    struct http_response;
   
    ////////////////////////////////////////////////////////////////////////////
    //                       HTTP Parsing
    ////////////////////////////////////////////////////////////////////////////
    /* at the top level, parse_http_request/parse_http_response parse the entire
     * structure, converting it to its respective data types. 
     * 
     * Lower level functions, mostly for internal use, take the current range
     * in consideration and attempt to parse their respective sections starting
     * at that point. if parsing is succesful, the return value is an iterator
     * pointing one past the end of the matched expression. otherwise begin is
     * returned.
     * 
     * NOTE: The iterator must be a bidirectional iterator
     * 
     * The ad-hoc grammar used for parsing looks something like:
     * 
     * http_request_header:
     *   ^METHOD \s+ ([^\s]+) \s+ HTTP/1.x\r\n
     * 
     * http_response_header:
     *  ^HTTP/1.x \s+ (\d+) \s+ ([^\r]+)\r\n
     * 
     * field:
     *   ^([a-Z][a-Z-]*):\s([^\r]*)\r\n
     * 
     * fields:
     *      fields, field
     *      field,
     *      none
     * 
     * http_request:
     *  http_request_header fields \r\n data
     * 
     * http_response:
     *  http_response_header fields \r\n data
     */
    //========================================================================//
    
    bool parse_http_request(http_data const & dt, http_request & dest);

    bool parse_http_response(http_data const & dt, http_response & dest);
   
    http_data::const_iterator
    parse_http_newl(http_data::const_iterator begin
                  , http_data::const_iterator const & end);
                  
    http_data::const_iterator 
    parse_http_field(http_data::const_iterator begin
                   , http_data::const_iterator const & end
                   , http_field & dest);
                   

    http_data::const_iterator 
    parse_http_fields(http_data::const_iterator begin
                    , http_data::const_iterator const & end
                    , std::vector<http_field> & dest);
                    
    http_data::const_iterator
    parse_http_fields_and_newl(http_data::const_iterator begin
                             , http_data::const_iterator const & end
                             , std::vector<http_field> & dest);
       
       
    http_data::const_iterator 
    parse_http_request_header(http_data::const_iterator begin
                            , http_data::const_iterator const & end
                            , http_request_header & dest);
         
         
    http_data::const_iterator
    parse_http_response_header(http_data::const_iterator begin
                             , http_data::const_iterator const & end
                             , http_response_header & dest);
    
    
    ////////////////////////////////////////////////////////////////////////////
    //                         Generation
    ////////////////////////////////////////////////////////////////////////////
    /* Generate a HTTP request/response from the internal representation
     * most generate functions have a proxy parse function.*/
    //========================================================================//
    
    http_data generate_http_field(http_field const &);
    
    http_data generate_http_fields(std::vector<http_field> const &);
    
    http_data generate_http_request_header(http_request_header const &);
    
    http_data generate_http_response_header(http_response_header const &);
    
    http_data generate_http_request(http_request const &);
    
    http_data generate_http_response(http_response const &);
    
    ////////////////////////////////////////////////////////////////////////////
    //
    std::vector<http_field>::const_iterator
    find_http_field(std::vector<http_field> const &, std::string const &);
    
    std::vector<http_field>::iterator
    find_http_field(std::vector<http_field> &, std::string const &);
    
    bool
    remove_http_field(std::vector<http_field> &, std::string const &);
    
    bool
    replace_http_field(std::vector<http_field> &
                     , std::string const &, std::string const &);
    
    template <http_status Status>
    http_response generate_status_response();
    
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class http_version
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
    inline const char* version_to_string(http_version v)
    {
        switch (v)
        {
            case http_version::ONE_ZERO:
                return "HTTP/1.0";
            case http_version::ONE_ONE:
                return "HTTP/1.1";
            default:
                throw "In default case!";
        }
    }
    
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline http_version string_to_version(std::string const & s)
    {
        if (s == "HTTP/1.0")
            return http_version::ONE_ZERO;
        else if (s == "HTTP/1.1")
            return http_version::ONE_ONE;
        else
            throw "In default case!";
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class http_method
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
}}                                                       // namespace elib::web

namespace elib { namespace enumeration
{
    ////////////////////////////////////////////////////////////////////////////
    //
    template <>
    struct basic_enum_traits<::elib::web::http_method>
    {
        using EnumType = ::elib::web::http_method;
        
        static const std::map<EnumType, std::string> name_map;
        
        static constexpr const EnumType ELIB_ENUM_FIRST_VALUE = EnumType::OPTIONS;
        static constexpr const EnumType ELIB_ENUM_LAST_VALUE = EnumType::CONNECT;
        
        static constexpr const bool ELIB_ENUM_IS_CONTIGIOUS = true;
    };
}}                                               // namespace elib::enumeration
    
namespace elib { namespace web
{
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class http_status
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
}}                                                       // namespace elib::web

namespace elib { namespace enumeration
{
    ////////////////////////////////////////////////////////////////////////////
    //
    template <>
    struct basic_enum_traits<::elib::web::http_status>
    {
        static const std::map<::elib::web::http_status, std::string> name_map;
    };
}}                                               // namespace elib::enumeration
    
namespace elib { namespace web
{
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_information(http_status s) noexcept
    {
        using UnderT = aux::underlying_type_t<http_status>;
        return (static_cast<UnderT>(s) >= 100 
            && static_cast<UnderT>(s) <= 199);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_success(http_status s) noexcept
    {
        using UnderT = aux::underlying_type_t<http_status>;
        return (static_cast<UnderT>(s) >= 200
             && static_cast<UnderT>(s) <= 299);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_redirect(http_status s) noexcept
    {
        using UnderT = aux::underlying_type_t<http_status>;
        return (static_cast<UnderT>(s) >= 300
             && static_cast<UnderT>(s) <= 399);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_client_error(http_status s) noexcept
    {
        using UnderT = aux::underlying_type_t<http_status>;
        return (static_cast<UnderT>(s) >= 400
             && static_cast<UnderT>(s) <= 499);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_server_error(http_status s) noexcept
    {
        using UnderT = aux::underlying_type_t<http_status>;
        return (static_cast<UnderT>(s) >= 500
             && static_cast<UnderT>(s) <= 599);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr bool status_is_error(http_status s) noexcept
    {
        return (status_is_client_error(s) || status_is_server_error(s));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    struct http_field
    {
        std::string key;
        std::string value;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    struct http_request_header
    {
        http_version version;
        http_method method;
        std::string request;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    struct http_response_header
    {
        http_version version;
        http_status status;
        std::string description;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    struct http_request
    {
        http_request_header header;
        std::vector<http_field> fields;
        http_data data;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    struct http_response
    {
        http_response_header header;
        std::vector<http_field> fields;
        http_data data;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <http_status Status>
    http_response generate_status_response()
    {
        http_response r;
        r.header.version = http_version::ONE_ZERO;
        r.header.status = Status;
        r.header.description = elib::enumeration::enum_cast<std::string>(Status);
        return r;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline std::vector<http_field>::const_iterator
    find_http_field(std::vector<http_field> const & v, std::string const & key)
    {
        return std::find_if(v.begin(), v.end()
                    , [&](http_field const & f) { return f.key == key; });
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline std::vector<http_field>::iterator
    find_http_field(std::vector<http_field> & v, std::string const & key)
    {
        return std::find_if(v.begin(), v.end()
                          , [&](http_field const & f) { return f.key == key; }); 
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline bool
    remove_http_field(std::vector<http_field> & v, std::string const & key)
    {
        auto it = std::remove_if(v.begin(), v.end()
                        , [&](http_field const & f) { return f.key == key; });
        return it != v.end();
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline bool
    replace_http_field(std::vector<http_field> & v, std::string const & key
                     , std::string const & replacement)
    {
        http_field new_val{key, replacement};
        bool found = false;
        std::replace_if(v.begin(), v.end()
                            , [&](http_field const & f) 
                                {
                                    if (f.key == key)
                                        found = true;
                                    return (f.key == key); 
                                }
                            , new_val); 
        return found;
    }
    
}}                                                       // namespace elib::web
#endif /* ELIB_WEB_HTTP_HPP */