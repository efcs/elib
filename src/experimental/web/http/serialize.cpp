#include <elib/experimental/web/http/serialize.hpp>
#include <elib/lexical_cast.hpp>

namespace elib { namespace web { namespace http
{
    
    data_type serialize(request_header const & h)
    {        
        std::string str = 
            elib::enumeration::enum_cast<std::string>(h.code)
            + " " + h.value + " " + to_string(h.http_version) + '\r' + '\n';
        
        return data_type(str.begin(), str.end());
    }
    
    data_type serialize(response_header const & h)
    {
        std::string str = to_string(h.http_version);
        str = str + " " + elib::lexical_cast<std::string>(static_cast<int>(h.code))
              + " " + h.value
              + '\r' + '\n';
              
        return data_type(str.begin(), str.end());
    }
    
    data_type serialize(field_type const & f)
    {
        std::string str = f.first + ": " + f.second + '\r' + '\n';
        return data_type{str.begin(), str.end()};
    }
    
    data_type serialize(std::vector<field_type> const & flist)
    {
        data_type dt;
        for (auto & f : flist)
        {
            data_type tmp = serialize(f);
            dt.insert(dt.end(), tmp.begin(), tmp.end());
        }
        return dt;
    }
    
}}}                                                         // namespace elib