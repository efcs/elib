#ifndef ELIB_ARGP_PARSE_HELPER_HPP
# define ELIB_ARGP_PARSE_HELPER_HPP

# include <elib/config.hpp>

# include <elib/argp/argp_error.hpp>

namespace elib 
{
  namespace argp
  {
    namespace parse
    {
      
      constexpr std::size_t npos = static_cast<std::size_t>(-1);
      
      
      bool is_name_first(char ch) noexcept;
      bool is_name_rest(char ch) noexcept;
      
      // basic parse tokens
      std::size_t whitespace(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t ellipses(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t equals(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t lbracket(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t rbracket(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t long_name_prefix(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t short_name_prefix(const std::string& str, std::size_t pos=0) noexcept;
      
      // 
      std::size_t name(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t long_name(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t short_name(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t option_name(const std::string& str, std::size_t pos=0) noexcept;
      std::size_t argument(const std::string& str, std::size_t pos=0) noexcept;
      
      class parser
      {
      public:
        typedef std::function<std::size_t(const std::string&, std::size_t)>
                function_type;
        
        parser(const std::string& xstr, std::size_t xpos=0) noexcept
          : str(xstr)
          , pos{xpos}
        { }
        
        explicit operator bool() const noexcept
        { return pos != npos; }
        
        const std::string& str;
        std::size_t pos;
      };                                                    // class parser
      
      
      parser& operator>>(parser& p, function_type fn)
      {
        if (p)
        {
          p.pos = fn(p.str, p.pos);
        }
        return p;
      }
      
      
    }                                                       // namespace parse
  }                                                           // namespace argp
}                                                           // namespace elib
#endif /* ELIB_ARGP_PARSE_HELPER_HPP */