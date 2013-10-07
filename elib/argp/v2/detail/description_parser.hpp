#ifndef ELIB_ARGP_DESCRIPTION_HELPER_HPP
# define ELIB_ARGP_DESCRIPTION_HELPER_HPP

# include <elib/config.hpp>

# include <string>
# include <utility> // for std::pair
# include <cstddef>

namespace elib 
{
  namespace argp
  {
    namespace detail
    {
      
      typedef typename std::string::iterator const_iterator;
      
       enum class option_type
      {
        none, 
        positional,
        short_name,
        long_name
      };                                              // enum class option_type
      
      
      struct parsed_desc
      {
        std::string name;
        std::string value;
        
        option_type type{option_type::none};
        
        bool optional{false};
        bool multi_option{false};
        
        bool value_optional{false};
        bool multi_value{false};
      };                                                  // struct parsed_desc
      
      
      
      
    
      parsed_desc parse_description(const std::string& s);
      
      const_string_iterator parse_option(const str_slice& s);
      const_string_iterator parse_option_name(const str_slice& s);
      const_string_iterator parse_name(const str_slice& s);
      const_string_iterator parse_equals(const str_slice& s);
      const_string_iterator parse_whitespace(const str_slice& s);
      
      const_string_iterator eat_whitespace(const str_slice& s);
      
      
      
      
    }                                                       // namespace detail
  }                                                           // namespace argp
}                                                           // namespace elib
#endif /* ELIB_ARGP_DESCRIPTION_HELPER_HPP */