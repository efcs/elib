#ifndef ELIB_WEB_HTTP_PARSE_HPP
#define ELIB_WEB_HTTP_PARSE_HPP

# include <elib/web/http/core.hpp>
#include <iterator>
#include <regex>


namespace elib { namespace web { namespace http
{
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , request_header & dest
    );
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , response_header & dest
    );
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , field_type & dest
    );
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , std::vector<field_type> & dest
    );
    
    data_type::const_iterator 
    parse_newl(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
    );
    
    template <class Header>
    data_type::const_iterator
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , message<Header> & dest
    )
    {
        auto orig_begin = begin;
        
        auto new_begin = parse(begin, end, dest.header);
        if (new_begin == begin) return orig_begin;
        
        begin = new_begin;
        new_begin = parse(new_begin, end, dest.fields);
        if (new_begin == end) return orig_begin;
            
        begin = new_begin;
        new_begin = parse_newl(begin, end);
        if (new_begin == begin) return orig_begin;
            
        dest.data.insert(dest.data.back(), new_begin, end);
        return end;
    }
    
   
}}}                                                          // namespace elib
#endif /* ELIB_WEB_HTTP_PARSE_HPP */