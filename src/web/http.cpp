#include <elib/web/http.hpp>
#include <elib/lexical_cast.hpp>
#include <algorithm>
#include <iterator>
#include <regex>

#define PROXY_HTTP_METHOD_MAP_ITEM(Name) \
    {::elib::web::http_method::Name, #Name}
    
#define PROXY_HTTP_STATUS_MAP_ITEM(Name) \
    {::elib::web::http_status::Name, #Name}

namespace elib { namespace enumeration
{
    constexpr const ::elib::web::http_method 
    basic_enum_traits<::elib::web::http_method>::ELIB_ENUM_FIRST_VALUE;
    
    constexpr const ::elib::web::http_method 
    basic_enum_traits<::elib::web::http_method>::ELIB_ENUM_LAST_VALUE;
    
    constexpr const bool 
    basic_enum_traits<::elib::web::http_method>::ELIB_ENUM_IS_CONTIGIOUS;
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#   pragma clang diagnostic ignored "-Wglobal-constructors"
# endif

    const std::map<::elib::web::http_method, std::string> 
    basic_enum_traits<::elib::web::http_method>::name_map =
    {
        PROXY_HTTP_METHOD_MAP_ITEM(OPTIONS)
      , PROXY_HTTP_METHOD_MAP_ITEM(GET)
      , PROXY_HTTP_METHOD_MAP_ITEM(HEAD)
      , PROXY_HTTP_METHOD_MAP_ITEM(POST)
      , PROXY_HTTP_METHOD_MAP_ITEM(PUT)
      , PROXY_HTTP_METHOD_MAP_ITEM(DELETE)
      , PROXY_HTTP_METHOD_MAP_ITEM(TRACE)
      , PROXY_HTTP_METHOD_MAP_ITEM(CONNECT)
    };
    
    const std::map<::elib::web::http_status, std::string>
    basic_enum_traits<::elib::web::http_status>::name_map =
    {
        PROXY_HTTP_STATUS_MAP_ITEM(CONTINUE)
      , PROXY_HTTP_STATUS_MAP_ITEM(SWITCH_PROTOCOL)
      
      , PROXY_HTTP_STATUS_MAP_ITEM(OK)
      , PROXY_HTTP_STATUS_MAP_ITEM(CREATED)
      , PROXY_HTTP_STATUS_MAP_ITEM(ACCEPTED)
      , PROXY_HTTP_STATUS_MAP_ITEM(NON_AUTH_INFORMATION)
      , PROXY_HTTP_STATUS_MAP_ITEM(NO_CONTENT)
      , PROXY_HTTP_STATUS_MAP_ITEM(RESET_CONTENT)
      , PROXY_HTTP_STATUS_MAP_ITEM(PARTIAL_CONTENT)
      
      , PROXY_HTTP_STATUS_MAP_ITEM(REDIRECT_CHOICE)
      , PROXY_HTTP_STATUS_MAP_ITEM(REDIRECT_MOVED_PERM)
      , PROXY_HTTP_STATUS_MAP_ITEM(REDIRECT_FOUND)
      , PROXY_HTTP_STATUS_MAP_ITEM(REDIRECT_SEE_OTHER)
      , PROXY_HTTP_STATUS_MAP_ITEM(REDIRECT_NOT_MODIFIED)
      , PROXY_HTTP_STATUS_MAP_ITEM(REDIRECT_USE_PROXY)
      , PROXY_HTTP_STATUS_MAP_ITEM(REDIRECT_TEMP)
      
      , PROXY_HTTP_STATUS_MAP_ITEM(BAD_REQUEST)
      , PROXY_HTTP_STATUS_MAP_ITEM(UNAUTHORIZED)
      , PROXY_HTTP_STATUS_MAP_ITEM(PAYMENT_REQUIRED)
      , PROXY_HTTP_STATUS_MAP_ITEM(FORBIDDEN)
      , PROXY_HTTP_STATUS_MAP_ITEM(NOT_FOUND)
      , PROXY_HTTP_STATUS_MAP_ITEM(METHOD_NOT_ALLOWED)
      , PROXY_HTTP_STATUS_MAP_ITEM(NOT_ACCEPTABLE)
      , PROXY_HTTP_STATUS_MAP_ITEM(PROXY_AUTH_REQUIRED)
      , PROXY_HTTP_STATUS_MAP_ITEM(REQUEST_TIMEOUT)
      , PROXY_HTTP_STATUS_MAP_ITEM(CONFLICT)
      , PROXY_HTTP_STATUS_MAP_ITEM(GONE)
      , PROXY_HTTP_STATUS_MAP_ITEM(LENGTH_REQUIRED)
      , PROXY_HTTP_STATUS_MAP_ITEM(PRECONDITION_FAILED)
      , PROXY_HTTP_STATUS_MAP_ITEM(REQUEST_ENTITY_TOO_LARGE)
      , PROXY_HTTP_STATUS_MAP_ITEM(REQUEST_URI_TOO_LARGE)
      , PROXY_HTTP_STATUS_MAP_ITEM(UNSUPPORTED_MEDIA_TYPE)
      , PROXY_HTTP_STATUS_MAP_ITEM(REQUEST_RANGE_NOT_SATISFIABLE)
      , PROXY_HTTP_STATUS_MAP_ITEM(EXPECTATION_FAILED)
      
      , PROXY_HTTP_STATUS_MAP_ITEM(INTERNAL_SERVER_ERROR)
      , PROXY_HTTP_STATUS_MAP_ITEM(NOT_IMPLEMENTED)
      , PROXY_HTTP_STATUS_MAP_ITEM(BAD_GATEWAY)
      , PROXY_HTTP_STATUS_MAP_ITEM(SERVICE_UNAVAILABLE)
      , PROXY_HTTP_STATUS_MAP_ITEM(GATEWAY_TIMEOUT)
      , PROXY_HTTP_STATUS_MAP_ITEM(HTTP_VERSION_UNSUPPORTED)
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
}}                                              // namespace elib::enumeration

namespace elib { namespace web
{
    using match_type = std::match_results<http_data::const_iterator>;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data::const_iterator
    parse_http_newl(http_data::const_iterator begin
                  , http_data::const_iterator const & end)
    {
        std::regex re{"^\\r\\n"};
        if (std::regex_search(begin, end, re))
            std::advance(begin, 2);
        return begin;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data::const_iterator 
    parse_http_field(http_data::const_iterator begin
                   , http_data::const_iterator const & end
                   , http_field & dest)
    {
        std::regex re{"^([a-zA-Z][a-zA-Z0-9-]*):\\s([^\\r]*)\\r\\n"};
        match_type m;
        if (!std::regex_search(begin, end, m, re))
            return begin;
        
        dest.key = m[1].str();
        dest.value = m[2].str();
        
        auto n_begin = begin;
        std::advance(n_begin, m[0].length());
        return n_begin;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data::const_iterator 
    parse_http_fields(http_data::const_iterator begin
                    , http_data::const_iterator const & end
                    , std::vector<http_field> & dest)
    {
        bool success = false;
        do
        {
            http_field tmp;
            auto n_begin = parse_http_field(begin, end, tmp);
            success = (begin != n_begin);
            
            if (success) 
            {
                dest.push_back(elib::move(tmp));
                begin = n_begin;
            }
        } while (success);
        
        return begin;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data::const_iterator
    parse_http_fields_and_newl(http_data::const_iterator begin
                             , http_data::const_iterator const & end
                             , std::vector<http_field> & dest)
    {
        auto field_end = parse_http_fields(begin, end, dest);
        auto newl_end = parse_http_newl(field_end, end);
        if (newl_end == field_end) 
            return begin;
        return newl_end;
    }
       
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data::const_iterator 
    parse_http_request_header(http_data::const_iterator begin
                            , http_data::const_iterator const & end
                            , http_request_header & dest)
    {
        std::regex re{"^([A-Z]+)\\s+([^ ]*)\\s+(HTTP/1\\.[01])\\r\\n"};
        match_type m;
        if (!std::regex_search(begin, end, m, re))
            return begin;
            
        dest.method = elib::enumeration::enum_cast<http_method>(m[1].str());
        dest.request = m[2].str();
        dest.version = string_to_version(m[3]);
        
        auto n_begin = begin;
        std::advance(n_begin, m[0].length());
        return n_begin;
    }
         
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data::const_iterator
    parse_http_response_header(http_data::const_iterator begin
                             , http_data::const_iterator const & end
                             , http_response_header & dest)
    {
        std::regex re{"^(HTTP/1\\.[01])\\s+([[:digit:]]+)\\s+([^\\r]*)\\r\\n"};
        match_type m;
        
        if (!std::regex_search(begin, end, m, re))
            return begin;
            
        dest.version = string_to_version(m[1].str());
        dest.status = static_cast<http_status>(
                            elib::lexical_cast<int>(m[2].str())
                        );
        dest.description = m[3].str();
        
        auto n_begin = begin;
        std::advance(n_begin, m[0].length());
        return n_begin;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    bool parse_http_request(http_data const& dt, http_request & dest)
    {
        http_data::const_iterator begin = dt.begin();
        const http_data::const_iterator end = dt.end();
        
        auto n_begin = parse_http_request_header(begin, end, dest.header);
        if (n_begin == begin)
            return false;
        else
            begin = n_begin;
            
        begin = parse_http_fields(begin, end, dest.fields);
        n_begin = parse_http_newl(begin, end);
        if (n_begin == begin)
            return false;
        else
            begin = n_begin;
        
        dest.data.insert(dest.data.begin(), begin, end);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    bool parse_http_response(http_data const & dt, http_response & dest)
    {
        http_data::const_iterator begin = dt.begin();
        const http_data::const_iterator end = dt.end();
        
        auto n_begin = parse_http_response_header(begin, end, dest.header);
        if (n_begin == begin)
            return false;
        else
            begin = n_begin;
            
        begin = parse_http_fields(begin, end, dest.fields);
        n_begin = parse_http_newl(begin, end);
        if (n_begin == begin)
            return false;
        else
            begin = n_begin;
        
        dest.data.insert(dest.data.begin(), begin, end);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data generate_http_field(http_field const & f)
    {
        http_data dt;
        dt.reserve(f.key.size() + f.value.size() + 4);
        dt.insert(dt.end(), f.key.begin(), f.key.end());
        dt.push_back(':'); dt.push_back(' ');
        dt.insert(dt.end(), f.value.begin(), f.value.end());
        dt.insert(dt.end(), std::begin(http_newl), std::end(http_newl));
        return dt;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data generate_http_fields(std::vector<http_field> const & f)
    {
        http_data dt;
        for (auto const & field : f)
        {
            const http_data field_dt = generate_http_field(field);
            dt.insert(dt.end(), field_dt.begin(), field_dt.end());
        }
        return dt;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data generate_http_request_header(http_request_header const & h)
    {
        http_data dt;
        const std::string method_str = elib::enumeration::enum_cast<std::string>(h.method);
        const std::string ver_str = version_to_string(h.version);
        
        dt.insert(dt.end(), method_str.begin(), method_str.end());
        dt.push_back(' ');
        dt.insert(dt.end(), h.request.begin(), h.request.end());
        dt.push_back(' ');
        dt.insert(dt.end(), ver_str.begin(), ver_str.end());
        dt.insert(dt.end(), std::begin(http_newl), std::end(http_newl));
        return dt;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data generate_http_response_header(http_response_header const & h)
    {
        http_data dt;
        const std::string ver_str = version_to_string(h.version);
        const std::string status_str = std::to_string(static_cast<int>(h.status));
        dt.insert(dt.end(), ver_str.begin(), ver_str.end());
        dt.push_back(' ');
        dt.insert(dt.end(), status_str.begin(), status_str.end());
        dt.push_back(' ');
        dt.insert(dt.end(), h.description.begin(), h.description.end());
        dt.insert(dt.end(), std::begin(http_newl), std::end(http_newl));
        return dt;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data generate_http_request(http_request const & r)
    {
        const http_data header_dt = generate_http_request_header(r.header);
        const http_data field_dt = generate_http_fields(r.fields);
        http_data dt;
        
        dt.reserve(header_dt.size() + field_dt.size() + r.data.size() + 2);
        
        dt.insert(dt.end(), header_dt.begin(), header_dt.end());
        dt.insert(dt.end(), field_dt.begin(), field_dt.end());
        dt.insert(dt.end(), std::begin(http_newl), std::end(http_newl));
        dt.insert(dt.end(), r.data.begin(), r.data.end());
        return dt;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_data generate_http_response(http_response const & r)
    {
        http_data header_dt = generate_http_response_header(r.header);
        http_data field_dt = generate_http_fields(r.fields);
        http_data dt;
        
        dt.reserve(header_dt.size() + field_dt.size() + r.data.size() + 4);
        
        dt.insert(dt.end(), header_dt.begin(), header_dt.end());
        dt.insert(dt.end(), field_dt.begin(), field_dt.end());
        dt.insert(dt.end(), std::begin(http_newl), std::end(http_newl));
        dt.insert(dt.end(), r.data.begin(), r.data.end());
        return dt;
    }
    
    
}}                                                       // namespace elib::web