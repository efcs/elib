#include <elib/web/fwd.hpp>
#include <elib/web/http.hpp>
#include <elib/web/basic_web_error.hpp>
#include <elib/web/proxy_error.hpp>
#include <elib/web/socket.hpp>

#include <elib/enumeration.hpp>

#include <exception>
#include <iostream>

namespace elib { namespace web
{
    void setup_term_handler()
    {
        std::set_terminate(&proxy_term_handler);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    void proxy_term_handler()
    {
        if (std::current_exception() != std::exception_ptr())
        {
            std::cout << "proxy terminate with uncaught exception" << std::endl;
            try {
                std::rethrow_exception(std::current_exception());
            } catch (proxy_protocol_error const & ppe) {
                std::cout << "Proxy Protocol Error: " << ppe.what() << std::endl;
                if (ppe.status() != http_status::none)
                    std::cout << elib::enumeration::enum_cast<std::string>(ppe.status())
                              << std::endl;
            } catch (proxy_internal_error const & pee) {
                std::cout << "Proxy Internal Error: " << pee.what() << std::endl;
            } catch (proxy_error const & pe) {
                std::cout << "Proxy error: " << pe.what() << std::endl;
            } catch (socket_error const & se) {
                std::cout << "Socket error: " << se.what() << std::endl;
                std::cout << se.error_code().message() << std::endl;
            } catch (basic_web_error const & be) {
                std::cout << "Basic Prox Error: " << be.what() << std::endl;
            } catch (...) {
                std::cout << "Unknown exception type!" << std::endl;
            }
        }
        else
        {
            std::cout << "No uncaught exception? " << std::endl;
        }
    }
}}                                                      // namespace elib::web