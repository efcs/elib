#ifndef ELIB_WEB_HTTP_SERIALIZE_HPP
#define ELIB_WEB_HTTP_SERIALIZE_HPP

# include <elib/experimental/web/http/core.hpp>
# include <string>
# include <vector>

////////////////////////////////////////////////////////////////////////////////
//                         Serialization
////////////////////////////////////////////////////////////////////////////////
/* Serialize http data for sending over connections */
//============================================================================//
namespace elib { namespace web { namespace http
{
    data_type serialize(request_header const &);
    data_type serialize(response_header const &);
    data_type serialize(field_type const &);
    data_type serialize(std::vector<field_type> const &);
    
    template <class HeaderType>
    data_type serialize(message<HeaderType> const & m)
    {
        data_type dt;
        
        data_type tmp = serialize(m.header);
        dt.insert(dt.end(), tmp.begin(), tmp.end());
        
        tmp = serialize(m.fields);
        dt.insert(dt.end(), tmp.begin(), tmp.end());
        
        dt.push_back(newl[0]);
        dt.push_back(newl[1]);
        
        dt.insert(dt.end(), m.data.begin(), m.data.end());
        
        return dt;
    }

}}}                                                         // namespace elib
#endif /* ELIB_WEB_HTTP_SERIALIZE_HPP */