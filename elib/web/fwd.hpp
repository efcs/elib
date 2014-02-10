#ifndef ELIB_WEB_FWD_HPP
#define ELIB_WEB_FWD_HPP

# include <elib/aux.hpp>

# include <vector>
# include <string>
# include <system_error>

# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
//                            PROX
////////////////////////////////////////////////////////////////////////////////
/*
 * Prox is divided into 3 main parts. Socket, HTTP, and Proxy.
 * 
 * Socket: A C++ interface over POSIX sockets. 
 *      The main design goals of Socket are:
 *      - Proper resource handling of socket descriptors
 *      - Better error reporting on the state of the socket
 *      - Type safety through the use of typesafe enums and concrete classes
 *      - Better error reporting on the outcome of socket operations
 *      - Safer buffer handling through the use of std::vector, as well as
 *          internaly detecting the size of the buffer and AddrTypes
 * 
 * HTTP: A set of tools to convert between HTTP headers and their respective
 *      internal representations.
 * 
 * Proxy: The proxy core. A main proxy server, request_threads, and "bridges" 
 *          to handle filtering/translation of HTTP
 */
//============================================================================//
namespace elib { namespace web
{

    /* entry point to start the proxy */
    int proxy_main(int, char**, char**);
    
    void setup_term_handler();
    void proxy_term_handler();
    
    // most basic exception that all others must derive from
    class basic_prox_error;
 
////////////////////////////////////////////////////////////////////////////////
//                            Socket
////////////////////////////////////////////////////////////////////////////////

    using sock_fd_t = int;
    using message_t = struct msghdr;
    
    // many methods in socket assume ::socklen_t is an integral type
    static_assert(aux::is_integral<::socklen_t>::value
                , "::socklen_t must be an integral type"); 
    
    ////////////////////////////////////////////////////////////////////////////
    //
    /* the C++ interface uses strongly typed enums to add type safety */
    enum class sock_type;
    enum class sock_option;
    enum class msg_flags;
    enum class sock_domain;
    enum class sock_shut;
    
    ////////////////////////////////////////////////////////////////////////////
    // 
    /* Provides descriptive string and std::error_code for cause of exception */
    class socket_error;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    /* C++ RAII exception safe wrapper around socket file descriptors.
     * socket also handles non-const modifications to the file descriptor, 
     * as well as providing error information about previous failures 
     * and the state of the file descriptor */
    class socket;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    /* TODO: should accept me a member of socket? I don't really think it should
     * be because it should not change the state of socket */
    socket accept(socket const &);
    
    template <class SockAddr>
    socket accept(socket const &, SockAddr &);
    
    template <class SockAddr>
    socket accept(socket const &, SockAddr &, socklen_t &);
    
    socket accept(socket const &, std::error_code & ec) noexcept;
    
    template <class SockAddr>
    socket accept(socket const &, SockAddr &, std::error_code &) noexcept;
    
    template <class SockAddr>
    socket accept(socket const &, SockAddr &, socklen_t &, std::error_code &) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    //                        Sending and Receiving
    ////////////////////////////////////////////////////////////////////////////
    /* all of the overloads are a futile attempt to provide a default
     * value for msg_flags as well as providing throwing and non-throwing
     * versions of the function. This pattern repeats itself throughout 
     * the send and receive functions.
     * 
     * For each POSIX send/receive function, there is a proxy. Except
     * for recvfrom. recvfrom requires that the user pass in an non-const lvalue
     * integral "address_len". This would create a really akward translation
     * to C++, so I'm ommiting it if I can avoid it.
     *
     * Functions that take std::error_code as their last argument report errors
     * via that variable. Functions that don't throw a socket_error when they
     * encounter a error. */
    //========================================================================//
    
    ////////////////////////////////////////////////////////////////////////////
    //
    /* receive maps to recv. If no vector is supplied it attempts to 
     * use a vector of size default_receive_length to store the data.
     *  
     * when a vector is return, it is sized to fit exactly the
     * data that was inserted into it.
     * HOWEVER: When ssize_t is return, the vector passed in DOES NOT have its 
     * size modified
     */
    constexpr const std::size_t default_receive_length = 1024;
    
    std::vector<char>
    receive(socket const &); 
    
    std::vector<char> 
    receive(socket const &, msg_flags);
    
    std::vector<char>
    receive(socket const &, std::error_code & ec) noexcept;
    
    std::vector<char>
    receive(socket const &, msg_flags, std::error_code & ec) noexcept;
    
    ssize_t 
    receive(socket const &, std::vector<char> &);
    
    ssize_t 
    receive(socket const &, std::vector<char> &, msg_flags);
    
    ssize_t
    receive(socket const &, std::vector<char> &, std::error_code & ec) noexcept;
    
    ssize_t
    receive(socket const &, std::vector<char> &, msg_flags, std::error_code & ec) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    ssize_t
    receive_msg(socket const &, message_t &);
    
    ssize_t 
    receive_msg(socket const &, message_t &, msg_flags);
    
    ssize_t 
    receive_msg(socket const &, message_t &, msg_flags, std::error_code & ec) noexcept;
    
    ssize_t
    receive_msg(socket const &, message_t &, std::error_code & ec) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    ssize_t
    send(socket const &, std::vector<char> const &);
    
    ssize_t
    send(socket const &, std::vector<char> const &, msg_flags);
    
    ssize_t
    send(socket const &, std::vector<char> const &, msg_flags, std::error_code & ec) noexcept;
    
    ssize_t
    send(socket const &, std::vector<char> const &, std::error_code & ec) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    ssize_t
    send_msg(socket const &, message_t const &);
    
    ssize_t
    send_msg(socket const &, message_t const &, msg_flags);
    
    ssize_t
    send_msg(socket const &, message_t const &, msg_flags, std::error_code & ec) noexcept;
    
    ssize_t
    send_msg(socket const &, message_t const &, std::error_code & ec) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class SockAddr>
    ssize_t
    send_to(socket const &, std::vector<char> const &, SockAddr const &);
    
    template <class SockAddr>
    ssize_t
    send_to(socket const &, std::vector<char> const &, msg_flags
          , SockAddr const &);
          
    template <class SockAddr>
    ssize_t
    send_to(socket const &, std::vector<char> const &, msg_flags
          , SockAddr const &, std::error_code & ec) noexcept;
          
    template <class SockAddr>
    ssize_t
    send_to(socket const &, std::vector<char> const &
            , SockAddr const &, std::error_code & ec) noexcept;
    
////////////////////////////////////////////////////////////////////////////////
//                                HTTP
////////////////////////////////////////////////////////////////////////////////

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
    
////////////////////////////////////////////////////////////////////////////////
//                               Proxy
////////////////////////////////////////////////////////////////////////////////
/* Proxy consists of two main parts. proxy_server and proxy_thread. As well
 * as the concept of a Bridge.
 * 
 * proxy_server is responsible for setting up the main listening socket.
 * when the server receives a request it spawns a proxy_thread and detaches itself
 * from that thread.
 * 
 * proxy_thread handles taking the request from the client, forwarding it 
 * to the end destination as a client, and receiving the response. once
 * it has received the response, it passes it through proxy_bridge before
 * relaying it to the original client. Upon completion proxy_thread terminates
 * 
 * A Bridge is a function object that has the following signature.
 *    http_response operator(http_response const &) const
 * It is very important that it is a const operation, since a single bridge
 * is shared across multiple threads.
 * A Bridge must be default constructable and copy constructable 
 */
//============================================================================//
    
    class proxy_error;
    class proxy_protocol_error;
    class proxy_internal_error;
    
    enum class internal_errc;
    
    /* throws proxy errors */
    template <class RequestBridge, class ResponseBridge>
    class proxy_server;
    /* throws proxy & socket errors */
    template <class RequestBridge, class ResponseBridge>
    class proxy_request;
    
    /* transpart_bridge returns THE EXACT SAME data that was passed in */
    struct request_transparent_bridge;
    struct response_transparent_bridge;
    
    /* bridge that implements assignment requirments */
    struct request_assignment_bridge;
    struct response_assignment_bridge;
    
    using transparent_proxy_server = 
        proxy_server<request_transparent_bridge, response_transparent_bridge>;
        
    using assignment_proxy_server = 
        proxy_server<request_assignment_bridge, response_assignment_bridge>;
    
    http_request  receive_http_request(socket const &);
    http_response receive_http_response(socket const &);
    
    http_response resolve_request_and_receive(http_request const &);
    http_request  resolve_redirect(http_request const &, http_response const &);
    
    http_response proxy_to_destination(http_request const &);
    
    http_response generate_odd_content_response();
    
////////////////////////////////////////////////////////////////////////////////
//                          Debug
////////////////////////////////////////////////////////////////////////////////

    constexpr const bool prox_debug_print_on = true;
    
    void prox_debug_print(std::string const &);
    void prox_debug_print(http_data const &);
    void prox_debug_print(http_request const &);
    void prox_debug_print(http_response const &);
    void prox_debug_print(http_request_header const &);
    void prox_debug_print(http_response_header const &);
    void prox_debug_print(http_field const &);
    void prox_debug_print(std::vector<http_field> const &);
    
}}                                                       // namespace elib::web
#endif /* ELIB_WEB_FWD_HPP */