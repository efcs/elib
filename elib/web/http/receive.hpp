#ifndef ELIB_WEB_HTTP_RECEIVE_HPP
#define ELIB_WEB_HTTP_RECEIVE_HPP

# include <elib/web/http/core.hpp>
# include <elib/web/http/parse.hpp>
# include <elib/web/error.hpp>
# include <elib/web/socket.hpp>
# include <elib/aux.hpp>
# include <elib/eprintf.hpp>
# include <elib/lexical_cast.hpp>
# include <algorithm>
# include <chrono>
# include <iterator>
# include <system_error>
# include <cstddef>

namespace elib { namespace web { namespace http
{

    namespace detail
    {
        template <class Message>
        Message receive(
            web::socket const & s
          , std::chrono::seconds timeout_in = std::chrono::seconds(5)
        );
    }
    
    inline request receive_request(web::socket const & s)
    {
        return detail::receive<request>(s);
    }
    
    inline response receive_response(web::socket const & s)
    {
        return detail::receive<response>(s);
    }
    
    namespace detail
    {
        inline std::size_t content_size(request const & msg)
        {
            // if there is content, and the length to the size of the buffer
            auto field_pos = find_field(msg.fields, "Content-Length");
            if (field_pos != msg.fields.end())
                return elib::lexical_cast<std::size_t>(field_pos->second);
            return 0;
        }
        
        inline std::size_t content_size(response const & msg)
        {
            auto field_pos = find_field(msg.fields, "Content-Length");
            if (field_pos != msg.fields.end())
                return elib::lexical_cast<std::size_t>(field_pos->second);
            return 0;
        }
    
        template <class Message>
        Message receive(
            web::socket const & s
          , std::chrono::seconds timeout_in
        )
        {
            static_assert(
                elib::aux::is_same<Message, request>::value
                || elib::aux::is_same<Message, response>::value
              , "The only two choices"
            );
            
            Message msg;
            data_type buff(10024);
            data_type remaining;
            
            
            
            const auto timeout_at = std::chrono::system_clock::now() + timeout_in;
                             
            auto timeout_receive = 
                [&]()
                {
                    std::error_code ec;
                    while (std::chrono::system_clock::now() < timeout_at)
                    {
                        ec.clear();
                        ::ssize_t ret = web::receive(s, buff, ec);
                        if (ec.value() == EAGAIN || ec.value() == EWOULDBLOCK)
                            continue;
                        if (ec)
                        {
                            ELIB_THROW_EXCEPTION(socket_error(
                                elib::fmt(
                                    "http::receive failed with error %s"
                                  , ec.message()
                                )
                              , ec
                            ));
                        }
                        ELIB_ASSERT(ret >= 0);
                        std::copy_n(
                            buff.begin()
                          , static_cast<std::size_t>(ret)
                          , std::back_inserter(remaining)
                        );
                   
                        return ret;
                    }
                    
                    ELIB_THROW_EXCEPTION(web_error(
                        "http::receive timed out"
                    ));
                };
               
            // get header
       
            while (true)
            {
                timeout_receive();
        
                auto pos = parse(remaining.begin(), remaining.end(), msg.header);
                
                if (pos == remaining.begin()) continue;
                
                remaining.erase(remaining.begin(), pos);
                break;
            }
            // get fields and newline
            while (true)
            {
                auto field_end = parse(remaining.begin(), remaining.end(), msg.fields);
                remaining.erase(remaining.begin(), field_end);
                
                auto newl_end = parse_newl(remaining.begin(), remaining.end());
                
                bool have_newl = newl_end != remaining.begin();
                
                remaining.erase(remaining.begin(), newl_end);
                
                if (have_newl) break;
                    
                // receive must only happen if we fail to parse till the 
                // newline break. othewise we could be waiting on a message
                // we already have
                timeout_receive();
            }
            
           
            std::size_t const con_size = content_size(msg);
            ELIB_ASSERT(con_size >= remaining.size());
            
            // get remaining data if needed 
            while (remaining.size() != con_size)
            {
                timeout_receive();                
            }
            
            msg.data.insert(msg.data.end(), remaining.begin(), remaining.end());
            
            return msg;
        }
    }                                                       // namespace detail
}}}                                                          // namespace elib
#endif /* ELIB_WEB_HTTP_RECEIVE_HPP */
