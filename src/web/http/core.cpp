#include <elib/web/http/core.hpp>


namespace elib { namespace enumeration
{
    
    constexpr const ::elib::web::http::method 
    basic_enum_traits<::elib::web::http::method>::ELIB_ENUM_FIRST_VALUE;
    
    constexpr const ::elib::web::http::method 
    basic_enum_traits<::elib::web::http::method>::ELIB_ENUM_LAST_VALUE;
    
    constexpr const bool 
    basic_enum_traits<::elib::web::http::method>::ELIB_ENUM_IS_CONTIGIOUS;
  
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#   pragma clang diagnostic ignored "-Wglobal-constructors"
# endif

#define _(Name) \
    {::elib::web::http::method::Name, #Name}
    
    const std::map<::elib::web::http::method, std::string> 
    basic_enum_traits<::elib::web::http::method>::name_map =
    {
        _(OPTIONS)
      , _(GET)
      , _(HEAD)
      , _(POST)
      , _(PUT)
      , _(DELETE)
      , _(TRACE)
      , _(CONNECT)
    };
    
#undef _
#define _(Name) \
    {::elib::web::http::status::Name, #Name}

    const std::map<::elib::web::http::status, std::string>
    basic_enum_traits<::elib::web::http::status>::name_map =
    {
        _(CONTINUE)
      , _(SWITCH_PROTOCOL)
      
      , _(OK)
      , _(CREATED)
      , _(ACCEPTED)
      , _(NON_AUTH_INFORMATION)
      , _(NO_CONTENT)
      , _(RESET_CONTENT)
      , _(PARTIAL_CONTENT)
      
      , _(REDIRECT_CHOICE)
      , _(REDIRECT_MOVED_PERM)
      , _(REDIRECT_FOUND)
      , _(REDIRECT_SEE_OTHER)
      , _(REDIRECT_NOT_MODIFIED)
      , _(REDIRECT_USE_PROXY)
      , _(REDIRECT_TEMP)
      
      , _(BAD_REQUEST)
      , _(UNAUTHORIZED)
      , _(PAYMENT_REQUIRED)
      , _(FORBIDDEN)
      , _(NOT_FOUND)
      , _(METHOD_NOT_ALLOWED)
      , _(NOT_ACCEPTABLE)
      , _(PROXY_AUTH_REQUIRED)
      , _(REQUEST_TIMEOUT)
      , _(CONFLICT)
      , _(GONE)
      , _(LENGTH_REQUIRED)
      , _(PRECONDITION_FAILED)
      , _(REQUEST_ENTITY_TOO_LARGE)
      , _(REQUEST_URI_TOO_LARGE)
      , _(UNSUPPORTED_MEDIA_TYPE)
      , _(REQUEST_RANGE_NOT_SATISFIABLE)
      , _(EXPECTATION_FAILED)
      
      , _(INTERNAL_SERVER_ERROR)
      , _(NOT_IMPLEMENTED)
      , _(BAD_GATEWAY)
      , _(SERVICE_UNAVAILABLE)
      , _(GATEWAY_TIMEOUT)
      , _(HTTP_VERSION_UNSUPPORTED)
    };

#undef _

# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
}}                                              // namespace elib::enumeration