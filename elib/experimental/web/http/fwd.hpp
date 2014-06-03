#ifndef ELIB_WEB_HTTP_FWD_HPP
#define ELIB_WEB_HTTP_FWD_HPP

# include <string>
# include <vector>
# include <utility>

namespace elib { namespace web { namespace http
{

     /* because \n just won't do the trick
     * initialization format is needed to prevent extra null (i think?) 
     * TODO: Fix this */
    constexpr const char newl[2] = {'\r', '\n'};
    
    
    enum class version;
    enum class method;
    enum class status;
    
    using data_type = std::vector<char>;
    using field_type = std::pair<std::string, std::string>;
    
    template <class EnumType>
    struct message_header;
    
    using request_header = message_header<method>;
    using response_header = message_header<status>;
    
    template <class Header>
    struct message;
    
    using request = message<request_header>;
    using response = message<response_header>;
        
}}}                                                         // namespace elib
#endif /* ELIB_WEB_HTTP_FWD_HPP */
