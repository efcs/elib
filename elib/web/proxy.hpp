#ifndef ELIB_WEB_PROXY_HPP
#define ELIB_WEB_PROXY_HPP

# include <elib/web/fwd.hpp>
# include <elib/web/proxy_error.hpp>
# include <elib/web/socket.hpp>
# include <elib/web/http.hpp>

# include <elib/aux.hpp>

# include <algorithm>
# include <memory>
# include <string>
# include <system_error>
# include <thread>
# include <vector>

# include <cstring>

# include <netdb.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

namespace elib { namespace web
{
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class RequestBridge, class ResponseBridge>
    class proxy_server
    {
    private:
        using request_thread_type = proxy_request<RequestBridge, ResponseBridge>;
        
        /* non-copyable */
        ELIB_DELETE_COPY(proxy_server);
        
    public:
        proxy_server() noexcept
          : m_sock{}
        {}
        
        ELIB_DEFAULT_MOVE(proxy_server);
        
        ~proxy_server() noexcept = default;
       
        ////////////////////////////////////////////////////////////////////////
        // Run method
        /* assumes bind() and listen() have already been run, 
         * NOTE: since sockets can't be copyied, it has to me moved in. 
         *          this pattern is common within proxy.hpp */
        [[noreturn]] void run(socket && mine)
        { m_sock.swap(mine); m_run(); }
        
    private:
        [[noreturn]] void m_run()
        {
            if (m_sock.fail())
                throw socket_error{
                    "bad socket passed to run()"
                    , m_sock.error_code()
                };
                
            if (!m_sock.is_open())
                throw socket_error{
                    "closed socket passed to run()"
                    , std::error_code{EBADF, std::system_category()}
                };
            
            std::error_code ec;
            while (true)
            {
                prox_debug_print("Main server listening for connection");
                socket client = accept(m_sock, ec);
                if (ec) 
                    throw socket_error{"Failed to accept client", ec};
                    
                prox_debug_print("Main server spawning client thread");
                m_spawn_thread(elib::move(client));
            }
        }
        
        /* spawn a thread to handle the request, and return */
        void m_spawn_thread(socket && client)
        {
            request_thread_type r;
            std::thread th{r, elib::move(client)};
            th.detach();
        }
        
        /* the main listening socket */
        socket m_sock;
    };
    
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class RequestBridge, class ResponseBridge>
    class proxy_request
    {
    public:
        ELIB_DEFAULT_CLASS(proxy_request);
        ////////////////////////////////////////////////////////////////////////
        //
        void operator()(socket && client_sock) const
        {
            /* proxy_request is run in its own thread, so it needs
             * to set its own terminate handler */
            setup_term_handler();
            
            if (!client_sock.good())
            {
                prox_debug_print("proxy_request passed bad client thread");
                return;
            }
            
            prox_debug_print("Accepted request from client");
            
            /* get request from client and bridge it */
            RequestBridge req_bridge;
            http_request orig_req = req_bridge(receive_http_request(client_sock));
            
            prox_debug_print("Recieved request from client");
            
            http_response res_back = proxy_to_destination(orig_req);
            
            // Bridge the data to perform checks/transformations
            prox_debug_print("Sending Response to client");
            ResponseBridge res_bridge;
            res_back = res_bridge(res_back);
            
            send(client_sock, generate_http_response(res_back));
            client_sock.close();
            
            prox_debug_print("Ending connection with client");
        }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    struct request_transparent_bridge
    {
        ELIB_DEFAULT_CLASS(request_transparent_bridge);
        
        http_request operator()(http_request const & r) const
        {
            return r;
        }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    struct response_transparent_bridge
    {
        ELIB_DEFAULT_CLASS(response_transparent_bridge);
        
        http_response operator()(http_response const & r) const
        {
            return r;
        }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    struct request_assignment_bridge
    {
        ELIB_DEFAULT_CLASS(request_assignment_bridge);
        
        http_request operator()(http_request const &) const;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    struct response_assignment_bridge
    {
        ELIB_DEFAULT_CLASS(response_assignment_bridge);
        
        http_response operator()(http_response const &) const;
    };
}}                                                      // namespace elib::web
#endif /* ELIB_WEB_PROXY_HPP */