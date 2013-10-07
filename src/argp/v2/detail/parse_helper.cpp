#include <elib/argp/v2/detail/parse_helper.hpp>

#include <cctype>
#include <cstddef>

namespace elib
{
  namespace argp
  {
    namespace detail
    {
      
      
      bool is_valid_name_character(char ch) noexcept
      {
        return (std::isalpha(ch) || std::isdigit(ch) || ch == '-'
                || ch == '_');
      }
      
      
      bool is_valid_name(const std::string& s)
      {
        if (s.size() == 0) return false;
        if (! std::isalpha(s[0])) return false;
        
        for (std::size_t i=1; i < s.size(); ++i)
        {
          if (! is_valid_name_character(s[i]))
            return false;
        }
        
        return true;
      }
      
      
      std::string parse_short_name(const std::string& name)
      
    }                                                       // namespace detail
  }                                                           // namespace argp
}                                                           // namespace elib