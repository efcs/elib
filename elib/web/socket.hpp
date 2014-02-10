#ifndef ELIB_WEB_SOCKET_HPP
#define ELIB_WEB_SOCKET_HPP

# include <elib/web/fwd.hpp>
# include <elib/web/basic_prox_error.hpp>
# include <elib/aux.hpp>

# include <memory>
# include <string>
# include <system_error>
# include <utility>
# include <vector>
# include <cerrno>

# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

namespace elib { namespace web
{
    ////////////////////////////////////////////////////////////////////////////
    //
    /* This is how the free function overloads are handled. Every free function
     * passes through one of these */
    namespace detail
    {
        socket accept_impl(socket const &, sockaddr *addr, socklen_t *len
                         , std::error_code *ec = nullptr);
                         
        ssize_t receive_impl(socket const &, std::vector<char> &, msg_flags
                           , std::error_code *ec = nullptr);
                            
        ssize_t receive_msg_impl(socket const &, message_t &, msg_flags
                               , std::error_code *ec = nullptr);
                               
        ssize_t send_impl(socket const &, std::vector<char> const &, msg_flags
                        , std::error_code *ec = nullptr); 
                           
        ssize_t send_msg_impl(socket const &, message_t const &, msg_flags 
                             , std::error_code *ec = nullptr);
                             
        ssize_t send_to_impl(socket const &, std::vector<char> const &, msg_flags
                           , const sockaddr *dest_addr, socklen_t len
                           , std::error_code *ec = nullptr);
    }                                                       // namespace detail
    
    /* To provide some type safety as compared against
     * the C interface */
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class sock_type
    {
        dgram = SOCK_DGRAM, 
        raw = SOCK_RAW,
        seqpacket = SOCK_SEQPACKET, 
        stream = SOCK_STREAM
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class sock_option
    {
        accept_conn = SO_ACCEPTCONN, 
        broadcast = SO_BROADCAST, 
        debug = SO_DEBUG, 
        dont_route = SO_DONTROUTE, 
        error = SO_ERROR, 
        keep_alive = SO_KEEPALIVE, 
        linger = SO_LINGER, 
        oob_in_line = SO_OOBINLINE,
        receive_buff = SO_RCVBUF, 
        receive_low_water = SO_RCVLOWAT, 
        receive_timeout = SO_RCVTIMEO, 
        reuse_addr = SO_REUSEADDR, 
        send_buff = SO_SNDBUF, 
        send_low_water = SO_SNDLOWAT, 
        send_timeout = SO_SNDTIMEO, 
        type = SO_TYPE
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class msg_flags
    {
        none = 0, 
        control_trunc = MSG_CTRUNC, 
        dont_route = MSG_DONTROUTE, 
        end_of_record = MSG_EOR, 
        out_of_band = MSG_OOB, 
        trunc = MSG_TRUNC, 
        wait_all = MSG_WAITALL, 
        peek = MSG_PEEK
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class sock_domain
    {
        inet = AF_INET, 
        inet6 = AF_INET6, 
        unix = AF_UNIX, 
        unspec = AF_UNSPEC
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    enum class sock_shut
    {
        read = SHUT_RD, 
        write = SHUT_WR, 
        read_write = SHUT_RDWR
    };
    
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    /////////////////////////////////////////////////////////////////////////////
    //
    class socket_error
      : public basic_prox_error
    {
    public:
        socket_error(std::string what_arg, std::error_code ec)
          : basic_prox_error{static_cast<std::string &&>(what_arg)}
          , m_ec{ec}
        {}
          
        
        ELIB_DEFAULT_COPY_MOVE(socket_error);
        
        const std::error_code & error_code() const noexcept
        { return m_ec; }
        
        virtual ~socket_error() = default;
    private:
        std::error_code m_ec;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class socket
    {
    public:
        socket() noexcept
          : m_fd{-1}, m_ec{}
        {}
        
        socket(sock_domain d, sock_type t, int protocol = 0) noexcept
          : m_fd{-1}, m_ec{}
        {
            this->open(d, t, protocol);
        }
        
        socket(socket && other) noexcept
          : m_fd{-1}, m_ec{}
        {
            this->swap(other);
        }
        
        socket & operator=(socket && other) noexcept
        {
            this->swap(other);
            return *this;
        }
        
        socket(socket const &) = delete;
        socket & operator=(socket const &) = delete;
        
        ~socket() noexcept
        { 
            this->close();
        }
        
        ////////////////////////////////////////////////////////////////////////
        //
        bool is_open() const noexcept
        { return (m_fd != -1); }
        
        void open(sock_domain d, sock_type t, int protocol = 0) noexcept;
        void shutdown(sock_shut = sock_shut::read_write) noexcept;
        void close() noexcept;
        
        int raw_socket() const noexcept
        { return m_fd; }
        
        ////////////////////////////////////////////////////////////////////////
        //
        /* bind and connect are converted to non-template forms so I can
         * get the implementation out of this header */
        template <class SockAddr>
        bool bind(SockAddr const & addr) noexcept
        {
            return m_bind((const sockaddr*)elib::addressof(addr), sizeof(SockAddr));
        }
        
        template <class SockAddr>
        bool connect(SockAddr const & addr) noexcept
        {
            return m_connect((const sockaddr*)elib::addressof(addr), sizeof(SockAddr));
        }
        
        bool listen(int backlog) noexcept;
        
        ////////////////////////////////////////////////////////////////////////
        // Status and Error Reporting
        /* good checks that a socket is ready for use, fail() return if there
         * is currently an error stored. */
        bool good() const noexcept
        { return (is_open() && !fail()); }
        
        bool fail() const noexcept
        { return static_cast<bool>(m_ec); }
        
        operator bool() const noexcept
        { return good(); }
        
        const std::error_code & error_code() const noexcept
        { return m_ec; }
        
        /* reset the internal error, don't touch the socket */
        void clear() noexcept 
        { m_ec.clear(); }
        
        /* close the current socket and clear any errors */
        void reset() noexcept
        {
            close();
            m_ec.clear();
        }
        
        void swap(socket & other) noexcept
        {
            std::swap(m_fd, other.m_fd);
            std::swap(m_ec, other.m_ec);
        }
        
    private:
        
        /* accept_impl needs to access m_fd so it can insert a raw 
         * file descriptor */
        friend socket detail::accept_impl(socket const &, sockaddr*, socklen_t*
                                         , std::error_code*);
        
        bool m_bind(const sockaddr *addr, socklen_t len) noexcept;
        bool m_connect(const sockaddr *addr, socklen_t len) noexcept;
        
        sock_fd_t m_fd;
        std::error_code m_ec;
    };
    
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline socket accept(socket const & s)
    {
        return detail::accept_impl(s, nullptr, nullptr);
    }
    
    template <class SockAddr>
    socket accept(socket const & s, SockAddr & addr)
    {
        socklen_t m_len = sizeof(SockAddr);
        return detail::accept_impl(s, (sockaddr*)elib::addressof(addr), &m_len);
    }
    
    template <class SockAddr>
    socket accept(socket const & s, SockAddr & addr, socklen_t & len)
    {
        len = sizeof(SockAddr);
        return detail::accept_impl(s, (sockaddr*)elib::addressof(addr), &len);
    }
    
    inline socket accept(socket const & s, std::error_code & ec) noexcept
    {
        return detail::accept_impl(s, nullptr, nullptr, &ec);
    }
    
    template <class SockAddr>
    socket accept(socket const & s, SockAddr & addr, std::error_code & ec) noexcept
    {
        socklen_t m_len = sizeof(SockAddr);
        return detail::accept_impl(s, (sockaddr*)elib::addressof(addr), &m_len, &ec);
    }
    
    template <class SockAddr>
    socket accept(socket const & s, SockAddr & addr, socklen_t & len
                , std::error_code & ec) noexcept
    {
        len = sizeof(SockAddr);
        return detail::accept_impl(s, (sockaddr*)elib::addressof(addr), &len, &ec);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline std::vector<char> 
    receive(socket const & s)
    {
        return receive(s, msg_flags::none);
    }
    
    inline std::vector<char> 
    receive(socket const & s, msg_flags f)
    {
        std::vector<char> v(default_receive_length);
        ssize_t ret = detail::receive_impl(s, v, f);
        /* ret >= 0 since receive_impl didn't throw */
        v.resize(static_cast<std::size_t>(ret));
        return v;
    }
    
    inline std::vector<char> 
    receive(socket const & s, std::error_code & ec) noexcept
    {
        return receive(s, msg_flags::none, ec);
    }
    
    inline std::vector<char> 
    receive(socket const & s, msg_flags f, std::error_code & ec) noexcept
    {
        std::vector<char> v(default_receive_length);
        ssize_t ret = detail::receive_impl(s, v, f, &ec);
        if (!ec) 
            v.resize(static_cast<std::size_t>(ret));
        else 
            v.resize(0);
        return v;
    }
    
    inline ssize_t 
    receive(socket const & s, std::vector<char> & v)
    {
        return detail::receive_impl(s, v, msg_flags::none);
    }
    
    inline ssize_t 
    receive(socket const & s, std::vector<char> & v, msg_flags f)
    {
        return detail::receive_impl(s, v, f);
    }
    
    inline ssize_t 
    receive(socket const & s, std::vector<char> & v, std::error_code & ec) noexcept
    {
        return detail::receive_impl(s, v, msg_flags::none, &ec);
    }
    
    inline ssize_t
    receive(socket const & s, std::vector<char> & v, msg_flags f
          , std::error_code & ec) noexcept
    {
        return detail::receive_impl(s, v, f, &ec);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline ssize_t
    receive_msg(socket const & s, message_t & m)
    {
        return detail::receive_msg_impl(s, m, msg_flags::none);
    }
    
    inline ssize_t
    receive_msg(socket const & s, message_t & m, msg_flags f)
    {
        return detail::receive_msg_impl(s, m, f);
    }
    
    inline ssize_t
    receive_msg(socket const & s, message_t & m, std::error_code & ec) noexcept
    {
        return detail::receive_msg_impl(s, m, msg_flags::none, &ec);
    }
    
    inline ssize_t
    receive_msg(socket const & s, message_t & m, msg_flags f
              , std::error_code & ec) noexcept
    {
        return detail::receive_msg_impl(s, m, f, &ec);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline ssize_t
    send(socket const & s, std::vector<char> const & v)
    {
        return detail::send_impl(s, v, msg_flags::none);
    }
    
    inline ssize_t
    send(socket const & s, std::vector<char> const & v, msg_flags f)
    {
        return detail::send_impl(s, v, f);
    }
    
    inline ssize_t
    send(socket const & s, std::vector<char> const & v, std::error_code & ec) noexcept
    {
        return detail::send_impl(s, v, msg_flags::none, &ec);
    }
    
    inline ssize_t
    send(socket const & s, std::vector<char> const & v, msg_flags f
       , std::error_code & ec) noexcept
    {
        return detail::send_impl(s, v, f, &ec);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline ssize_t
    send_msg(socket const & s, message_t const & m)
    {
        return detail::send_msg_impl(s, m, msg_flags::none);
    }
    
    inline ssize_t
    send_msg(socket const & s, message_t const & m, msg_flags f)
    {
        return detail::send_msg_impl(s, m, f);
    }
    
    inline ssize_t
    send_msg(socket const & s, message_t const & m, std::error_code & ec) noexcept
    {
        return detail::send_msg_impl(s, m, msg_flags::none, &ec);
    }
    
    inline ssize_t
    send_msg(socket const & s, message_t const & m, msg_flags f
            , std::error_code & ec) noexcept
    {
        return detail::send_msg_impl(s, m, f, &ec);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class SockAddr>
    ssize_t
    send_to(socket const & s, std::vector<char> const & v, SockAddr const & addr)
    {
        return detail::send_to_impl(
                      s, v, msg_flags::none
                    , (const sockaddr*)elib::addressof(addr), sizeof(SockAddr)
                );
    }
    
    template <class SockAddr>
    ssize_t
    send_to(socket const & s, std::vector<char> const & v, msg_flags f 
          , SockAddr const & addr)
    {
        return detail::send_to_impl(
                      s, v, f
                    , (const sockaddr*)elib::addressof(addr), sizeof(SockAddr)
                );
    }
    
    template <class SockAddr>
    ssize_t
    send_to(socket const & s, std::vector<char> const & v, SockAddr const & addr
          , std::error_code & ec) noexcept
    {
        return detail::send_to_impl(
                    s, v, msg_flags::none
                  , (const sockaddr*)elib::addressof(addr), sizeof(SockAddr)
                  , &ec
            );
    }
    
    template <class SockAddr>
    ssize_t
    send_to(socket const & s, std::vector<char> const & v, msg_flags f
          , SockAddr const & addr, std::error_code & ec) noexcept
    {
        return detail::send_to_impl(
                    s, v, f
                  , (const sockaddr*)elib::addressof(addr), sizeof(SockAddr)
                  , &ec
            );
    }

}}                                                       // namespace elib::web
#endif /* ELIB_WEB_SOCKET_HPP */