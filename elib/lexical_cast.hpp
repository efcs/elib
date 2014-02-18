#ifndef ELIB_LEXICAL_CAST_HPP
#define ELIB_LEXICAL_CAST_HPP

# include <elib/aux.hpp>
# include <stdexcept>
# include <string>
# include <sstream>

namespace elib 
{
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
  /* bad_cast error for lexical casts */
  class bad_lexical_cast : public std::runtime_error {
  public:
# if defined(ELIB_CONFIG_COVERITY_SCAN)
      bad_lexical_cast(std::string && s)
        : std::runtime_error(s)
        {}
# endif
      using std::runtime_error::runtime_error;
      
      ELIB_DEFAULT_COPY_MOVE(bad_lexical_cast);
      
      virtual ~bad_lexical_cast() noexcept {}
  };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

    // TODO: rename this. 
    template <class T>
    using is_lexical = 
        aux::or_<
            aux::is_integral<T>
          , aux::is_floating_point<T>
          >;

    ////////////////////////////////////////////////////////////////////////////
    //
    template <
        class To, class From
      , ELIB_ENABLE_IF(aux::is_same<To, std::string>::value)
      , ELIB_ENABLE_IF(is_lexical<From>::value)
    >
    To lexical_cast(From from)
    {
        std::stringstream ss;
        if (aux::is_same<From, bool>::value)
            ss.setf(std::ios_base::boolalpha);
        ss << from;
        return ss.str();
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <
        class To, class From
      , ELIB_ENABLE_IF(is_lexical<To>::value)
      , ELIB_ENABLE_IF(!aux::is_same<To, bool>::value)
      , ELIB_ENABLE_IF(aux::is_string_type<From>::value)
      >
    To lexical_cast(From const & f)
    {
        To t{};
        std::stringstream ss;  
        
        ss << f;
        ss >> t;
        
        if (!ss) 
            throw bad_lexical_cast{
                std::string{"bad lexical cast from string: \""}
                + f + "\""
            };
        
        return t;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Special case for str -> bool conversion 
    template <
        class To, class From
      , ELIB_ENABLE_IF(aux::is_same<To, bool>::value)
      , ELIB_ENABLE_IF(aux::is_string_type<From>::value)
    >
    To lexical_cast(From const & f)
    {
        bool b{};
        std::stringstream ss;
        
        // try reading as "true" or "false"
        ss << std::boolalpha << f;
        ss >> b;
        
        // success on first try
        // input string was "true" or "false"
        if (ss) return b;
    
        // input string was a digit
        ss.clear();
        ss << std::noboolalpha;
        ss >> b;
        if (ss) return b;
            
        std::string err_str = "Bad lexical cast from string to bool: \"";
        err_str += f + '"';
        throw bad_lexical_cast{err_str};
    }
}                                                            // namespace elib
#endif /* ELIB_LEXICAL_CAST_HPP */