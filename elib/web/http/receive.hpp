#ifndef ELIB_WEB_HTTP_RECEIVE_HPP
#define ELIB_WEB_HTTP_RECEIVE_HPP

# include <elib/web/http/core.hpp>
# include <elib/web/http/parse.hpp>
# include <elib/web/socket.hpp>
# include <elib/aux.hpp>
# include <elib/lexical_cast.hpp>
# include <algorithm>
# include <chrono>
# include <cstddef>

namespace elib { namespace web { namespace http
{

    namespace detail
    {
        template <class Message>
        Message receive(web::socket const & s);
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
        Message receive(web::socket const & s)
        {
            static_assert(
                elib::aux::is_same<Message, request>::value
                || elib::aux::is_same<Message, response>::value
              , "The only two choices"
            );
            
            ELIB_ASSERT(s);
            
            Message msg;
            data_type buff(10024);
            data_type remaining;
            
            const auto timeout_at = std::chrono::seconds(30)
                                  + std::chrono::system_clock::now();
                                  
            auto timeout_receive = 
                [&]()
                {
                    if (std::chrono::system_clock::now() > timeout_at)
                        throw "TODO";
                    
                    ::ssize_t ret = web::receive(s, buff);
                    ELIB_ASSERT(ret >= 0);
                    
                    std::copy_n(
                        buff.begin()
                      , static_cast<std::size_t>(ret)
                      , remaining.end()
                    );
                    
                    return ret;
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
                
                auto newl_end = parse_newl(field_end, remaining.end());
                remaining.erase(remaining.begin(), newl_end);
                
                if (newl_end != field_end) break;
                    
                // receive must only happen if we fail to parse till the 
                // newline break. othewise we could be waiting on a message
                // we already have
                timeout_receive();
            }
            
            // insert remaining into data
            msg.data.insert(msg.data.end(), remaining.begin(), remaining.end());
            // find out size of remaining content
            std::size_t needed_size = content_size(msg) - remaining.size();
            ELIB_ASSERT(content_size(msg) >= remaining.size());
            // get remaining data if needed 
            if (needed_size != 0)
            {
                buff.resize(needed_size);
                ::ssize_t ret = web::receive(s, buff, msg_flags::wait_all);
                ELIB_ASSERT(ret >= 0);
                ELIB_ASSERT(static_cast<std::size_t>(ret) == needed_size);
                msg.data.insert(msg.data.end(), buff.begin(), buff.end());
            }
            
            return msg;
        }
    }                                                       // namespace detail
}}}                                                          // namespace elib
#endif /* ELIB_WEB_HTTP_RECEIVE_HPP */
