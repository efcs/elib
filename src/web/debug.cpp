#include <elib/web/fwd.hpp>
#include <elib/web/proxy.hpp>
#include <elib/web/http.hpp>
#include <elib/web/socket.hpp>

#include <elib/enumeration.hpp>
#include <elib/lexical_cast.hpp>

#include <string>
#include <iostream>
#include <vector>

namespace elib { namespace web
{
    namespace enums = elib::enumeration;
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunreachable-code"
# endif

    void prox_debug_print(std::string const & v)
    {
        if (!prox_debug_print_on) return;
        std::cout << "PROX DEBUG: " << v << std::endl; 
    }
    
    void prox_debug_print(http_data const & v)
    {
        std::string s{v.begin(), v.end()};
        if (!prox_debug_print_on) return;
        std::cout << "PROX DEBUG: http_data ->\n" << s << std::endl;
    }
    
    void prox_debug_print(http_request_header const & v)
    {
        if (!prox_debug_print_on) return;
        auto dt = generate_http_request_header(v);
        std::string s(dt.begin(), dt.end());
        
        std::cout << "PROX DEBUG: http_request_header ->\n"
                  << s << std::endl; 
    }
    
    void prox_debug_print(http_response_header const & v)
    {
        if (!prox_debug_print_on) return;
        auto dt = generate_http_response_header(v);
        std::string s(dt.begin(), dt.end());
        
        std::cout << "PROX DEBUG: http_response_header ->\n"
                  << s << std::endl; 
    }
    
    void prox_debug_print(http_request const & v)
    {
        if (!prox_debug_print_on) return;
        std::cout << "PROX DEBUG: http_request ->\n";
        prox_debug_print(v.header);
        prox_debug_print(v.fields);
    }
    
    void prox_debug_print(http_response const & v)
    {
        if (!prox_debug_print_on) return;
        std::cout << "PROX DEBUG: http_response ->\n";
        prox_debug_print(v.header);
        prox_debug_print(v.fields);
    }
    
    void prox_debug_print(http_field const & v)
    {
        if (!prox_debug_print_on) return;
        std::cout << "PROX DEBUG: http_field ->\n"
                  << v.key << ": " << v.value
                  << std::endl;
    }
    
    void prox_debug_print(std::vector<http_field> const & v)
    {
        if (!prox_debug_print_on) return;
        auto dt = generate_http_fields(v);
        std::string s{dt.begin(), dt.end()};
        std::cout << "PROX DEBUG: http_field(s) ->\n"
                  << s << std::endl; 
    }
    
# if defined(__clang__)
#   pragma clang diagnostic pop
#endif
}}                                                      // namespace elib::web