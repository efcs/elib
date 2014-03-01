#include <elib/web/http/parse.hpp>
#include <elib/aux.hpp>
#include <elib/enumeration.hpp>
#include <elib/lexical_cast.hpp>

namespace elib { namespace web { namespace http
{
    using match_type = std::match_results<data_type::const_iterator>;
    
   
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , request_header & dest
    )
    {
        std::regex re{"^([A-Z]+)\\s+([^ ]*)\\s+(HTTP/1\\.[01])\\r\\n"};
        match_type m;
        if (!std::regex_search(begin, end, m, re))
            return begin;
            
        dest.code = elib::enumeration::enum_cast<method>(m[1].str());
        dest.value = m[2].str();
        dest.http_version = string_to_version(m[3]);
        
        std::advance(begin, m[0].length());
        return begin;
    }
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , response_header & dest
    )
    {
        std::regex re{"^(HTTP/1\\.[01])\\s+([[:digit:]]+)\\s+([^\\r]*)\\r\\n"};
        match_type m;
        
        if (!std::regex_search(begin, end, m, re))
            return begin;
            
        dest.http_version = string_to_version(m[1].str());
        dest.code = static_cast<status>(
                            elib::lexical_cast<int>(m[2].str())
                        );
        dest.value = m[3].str();
        

        std::advance(begin, m[0].length());
        return begin;
    }
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , field_type & dest
    )
    {
        std::regex re{"^([a-zA-Z][a-zA-Z0-9-]*):\\s([^\\r]*)\\r\\n"};
        match_type m;
        if (!std::regex_search(begin, end, m, re))
            return begin;
        
        dest.first = m[1].str();
        dest.second = m[2].str();
        
        std::advance(begin, m[0].length());
        return begin;
    }
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , std::vector<field_type> & dest
    )
    {
        ELIB_ASSERT(dest.empty());
        
        bool success = false;
        do
        {
            field_type tmp;
            auto n_begin = parse(begin, end, tmp);
            success = (begin != n_begin);
            
            if (success) 
            {
                dest.push_back(elib::move(tmp));
                begin = n_begin;
            }
        } while (success);
        
        return begin;
    }
    
    data_type::const_iterator 
    parse_newl(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
    )
    {
        std::regex re{"^\\r\\n"};
        if (std::regex_search(begin, end, re))
            std::advance(begin, 2);
        return begin;
    }
}}}                                                         // namespace elib