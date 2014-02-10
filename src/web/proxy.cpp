#include <elib/web/proxy.hpp>
#include <elib/enumeration.hpp>
#include <elib/lexical_cast.hpp>

#include <chrono>
#include <string>
#include <iterator>
#include <iostream>
#include <cstddef>

namespace elib { namespace web
{
    namespace enums = elib::enumeration;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_response proxy_to_destination(http_request const & orig_req)
    {
        const std::size_t redir_max = 10;
        std::size_t redir_count = 0;
        http_request req = orig_req;
        http_response response;
        while (true)
        {
            prox_debug_print("Sending Request to server");
            
            response = resolve_request_and_receive(req);
                
            if (response.header.status == http_status::REDIRECT_MOVED_PERM
                || response.header.status == http_status::REDIRECT_FOUND)
            {
                prox_debug_print("Attempting to resolve redirect");
                ++redir_count;
                if (redir_count >= redir_max)
                    throw proxy_internal_error{"Exceded max redirect count"};
                req = resolve_redirect(orig_req, response);
                prox_debug_print(req);
            }
            else break;
        }
        return response;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_request
    request_assignment_bridge::operator()(http_request const & r) const
    {
        return r;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_response 
    response_assignment_bridge::operator()(http_response const & r) const
    {
        if (r.header.status != http_status::OK) return r;
        
        auto len_pos = find_http_field(r.fields, "Content-Length");
        if (len_pos == r.fields.end()
            || elib::lexical_cast<std::size_t>(len_pos->value) % 2 == 0)
        {
            return r;
        }
        
        return generate_odd_content_response();
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_response resolve_request_and_receive(http_request const & req)
    {
        if (req.header.method != http_method::GET)
        {
            prox_debug_print("POST Request");
            prox_debug_print(req);
            
            throw proxy_protocol_error{
                "Unsupported http request method: " 
                    + enums::enum_cast<std::string>(req.header.method)
                , http_status::NOT_IMPLEMENTED
            };
        }
            
        auto host_pos = find_http_field(req.fields, "Host");
        if (host_pos == req.fields.end())
            throw proxy_protocol_error{
                "No Host field in HTTP request"
              , http_status::METHOD_NOT_ALLOWED
            };
            
        hostent *he = ::gethostbyname(host_pos->value.c_str());
        if (!he) return generate_status_response<http_status::NOT_FOUND>();
        
        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(80);
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        bcopy(he->h_addr, &server.sin_addr, static_cast<std::size_t>(he->h_length));
        
        socket server_sock{sock_domain::inet, sock_type::stream, 0};
        if (!server_sock)
            throw socket_error{
                "Failed to open socket for server"
                , server_sock.error_code()
            };
            
        server_sock.connect(server);
        if (!server_sock)
            throw socket_error{
                "Failed to connect to remote server: " + host_pos->value
                , server_sock.error_code()
            };
                            
        send(server_sock, generate_http_request(req));
        
        return receive_http_response(server_sock);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_request resolve_redirect(http_request const & orig, http_response const & redir)
    {
        http_request req = orig;
        
        auto loc_pos = find_http_field(redir.fields, "Location");
        ELIB_ASSERT(loc_pos != redir.fields.end());
        
        req.header.request = loc_pos->value;
        return req;
    }
    
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_request receive_http_request(socket const & s)
    {
        std::size_t msg_size = 0;
        
        // really big because I type slow
        
        const auto timeout_at = std::chrono::seconds(60) 
                              + std::chrono::system_clock::now();
        
        while (true)
        {
            if (timeout_at < std::chrono::system_clock::now())
                throw proxy_protocol_error{
                    "Waited too long for request"
                  , http_status::GATEWAY_TIMEOUT
                };
                
            http_data dt(5012);
            http_request req;
            receive(s, dt, msg_flags::peek);
            
            http_data::const_iterator b = dt.begin();
            http_data::const_iterator e = dt.end();
            
            if (b == e) continue;
            
            auto f_begin = parse_http_request_header(b, e, req.header);
            if (f_begin == b) continue;
            
            auto newl_e = parse_http_fields_and_newl(f_begin, e, req.fields);
            if (newl_e == f_begin) continue;
            
            // we have header and all fields
            msg_size = static_cast<std::size_t>(std::distance(b, newl_e));
            
            auto field_pos = find_http_field(req.fields, "Content-Length");
            if (field_pos != req.fields.end())
                msg_size += elib::lexical_cast<std::size_t>(field_pos->value);
                
            break;
        }
        
        http_data final_dt(msg_size);
        while (true)
        {
            ssize_t try_ret = receive(s, final_dt, msg_flags::peek);
            if (try_ret == static_cast<ssize_t>(msg_size))
                break;
        }
        
        ssize_t ret = receive(s, final_dt);
        ELIB_ASSERT(ret == static_cast<ssize_t>(msg_size)); ELIB_UNUSED(ret);
        
        http_request final_req;
        if (! parse_http_request(final_dt, final_req)) 
            throw proxy_protocol_error{
                "Failed to parse http request"
              , http_status::BAD_GATEWAY
            };
            
        return final_req;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_response receive_http_response(socket const & s)
    {
        std::size_t msg_len = 0;
        
        const std::size_t max_loop_count = 10;
        std::size_t loop_count = 0;
        std::size_t receive_length = default_receive_length;
        
        while (true)
        {
            ++loop_count;
            if (loop_count >= max_loop_count)
                throw proxy_protocol_error{
                    "receive_http_response timed out"
                  , http_status::GATEWAY_TIMEOUT
                };
                
            if (loop_count > 1)
                receive_length += default_receive_length;
            
            http_response res;
            http_data dt(receive_length);
            receive(s, dt, msg_flags::peek);
            
            http_data::const_iterator b = dt.begin();
            http_data::const_iterator e = dt.end();
            
            auto f_begin = parse_http_response_header(b, e, res.header);
            if (f_begin == b) continue;
                
            auto newl_end = parse_http_fields_and_newl(f_begin, e, res.fields);
            if (newl_end == f_begin) continue;
                
            msg_len = static_cast<std::size_t>(std::distance(b, newl_end));
            
            auto field_pos = find_http_field(res.fields, "Content-Length");
            if (field_pos != res.fields.end())
                msg_len += elib::lexical_cast<std::size_t>(field_pos->value);
                
            break;
        }
        
        http_data final_dt(msg_len);
        while (true)
        {
            ssize_t try_ret = receive(s, final_dt, msg_flags::peek);
            if (try_ret == static_cast<ssize_t>(msg_len))
                break;
        }
        
        // eat the buffer
        if (static_cast<std::size_t>(receive(s, final_dt)) != msg_len)
            throw proxy_protocol_error{
                "Failed in final receive of receive_http_response: "
                "returned length != expected length"
              , http_status::BAD_GATEWAY
            };
        
        http_response final_res;
        if (!parse_http_response(final_dt, final_res)) 
            throw proxy_protocol_error{
                "Failed in final parse of receive_http_response"
              , http_status::BAD_GATEWAY
            };
            
        return final_res;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    http_response generate_odd_content_response()
    {
        http_response r = generate_status_response<http_status::PRECONDITION_FAILED>();
        r.header.description = "The Page had an odd numbered content size";
        return r;
    }
}}                                                       // namespace elib::web