#ifndef ELIB_ARGP_PARSE_HELPER_HPP
# define ELIB_ARGP_PARSE_HELPER_HPP

# include <elib/argp/v2/config.hpp>

namespace elib 
{
  namespace argp
  {
    namespace detail
    {
      
      // do not use for checking first character
      bool is_valid_name_character(char ch) noexcept;
      
      bool is_valid_name(const std::string& s) noexcept;
      
      inline bool has_short_name_prefix(const std::string& s) noexcept
      {
        return (s.size() >= 1 && s[0] == '-'
                && (s.size() == 1 || s[1] != '-'));
      }
      
      inline bool has_long_name_prefix(const std::string& s) noexcept
      {
        return (s.size() >= 2 && s[0] == '-' && s[1] == '-'
                && (s.size() == 2 || s[2] != '-'));
      }
      
      std::string parse_short_name(const std::string& name);
      
      std::string parse_long_name(const std::string& name);
      
      inline std::string parse_name(const std::string& name)
      {
        if (has_short_name_prefix(name))
          return parse_short_name(name);
        else if (has_long_name_prefix(name))
          return parse_long_name(name);
        return {};
      }
      
      inline bool is_short_name(const std::string& name)
      {
        return parse_short_name(name).size() != 0;
      }
      
      inline bool is_long_name(const std::string& name)
      {
        return parse_long_name(name).size() != 0;
      }
      
      enum class option_type
      {
        none, 
        positional, 
        long_name, 
        short_name
      };
      
      struct parsed_opt
      {
        option_type opt_type{option_type::none};
        std::string name;
        std::string value;
      };                                                   // struct parsed_arg
      
      parsed_opt parse_opt(const std::string& name);
      
    }                                                       // namespace detail
  }                                                           // namespace argp
}                                                           // namespace elib
#endif /* ELIB_ARGP_PARSE_HELPER_HPP */