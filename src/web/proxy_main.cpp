#include <elib/web/fwd.hpp>
#include <elib/web/proxy.hpp>
#include <elib/web/socket.hpp>

#include <elib/aux.hpp>
#include <elib/assert.hpp>
#include <elib/lexical_cast.hpp>

#include <iostream>
#include <string>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace elib { namespace web 
{
    //TODO
    int proxy_main(int argc, char* argv[], char**)
    {
        
        if (argc != 2)
        {
            std::cout << "Usage: proxy <port>" << std::endl;
            return 1;
        }
        
        std::string port_str{argv[1]};
        uint16_t port = elib::lexical_cast<uint16_t>(port_str);
        
        setup_term_handler();
        
        sockaddr_in serv;
        serv.sin_family = AF_INET;
        serv.sin_port = htons(port);
        serv.sin_addr.s_addr = htonl(INADDR_ANY);
        
        socket serv_sock;
        serv_sock.open(sock_domain::inet, sock_type::stream, 0);
        serv_sock.bind(serv);
        serv_sock.listen(5);
        
        ELIB_ASSERT( ((bool)serv_sock) );
        
        //assignment_proxy_server p;
        transparent_proxy_server p;
        p.run(elib::move(serv_sock));
    }
}}                                                       // namespace elib::web