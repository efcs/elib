#ifndef ELIB_LEXICAL_CAST_HPP
#define ELIB_LEXICAL_CAST_HPP

# include <elib/pragma.hpp>

# include <stdexcept>
# include <string>
# include <type_traits>
# include <sstream>

namespace elib 
{
  
  ELIB_PRAGMA_DIAG_PUSH()
  ELIB_PRAGMA_IGNORE_WEAK_VTABLES()
      
  /* bad_cast error for lexical casts */
  class bad_lexical_cast : public std::runtime_error {
  public:
      inline
      bad_lexical_cast()
          : std::runtime_error("bad lexical cast")
      { }
  };

  ELIB_PRAGMA_DIAG_POP()


  /* static type-traits style struct to
  * check if a type is convertible using a lexical cast */
  template <typename T>
  struct is_lexical {
      static constexpr bool value = 
          std::is_integral<T>::value ||
          std::is_floating_point<T>::value;
  };

  /* specializations needed for strings
  *  C strings can only be used as the source type
  * in a lexical cast, so is_lexical is allowed to fail */
  template <>
  struct is_lexical<std::string>
  {
      static constexpr bool value = true;
  };

  
  /* cast one lexical type to another, generally either to or from a string 
  * ex: string -> float
  *     bool -> string
  *     int -> string
  *     string -> bool */
  template <typename ToType, typename FromType>
  inline ToType lexical_cast(const FromType & from)
  {
      static_assert(is_lexical<ToType>::value, 
                    "cannot lexical cast to type");
      static_assert(is_lexical<FromType>::value,
                    "cannot lexical cast from type");
      
      std::stringstream ss;
      ToType val;
      /* here is the trick, we basically write to
      * and extract from a stringstream to do the cast,
      * for booleans, we set std::boolalpha */
      ss << from;
      ss >> val;
      if (! ss)
          throw bad_lexical_cast();
      
      return val;
  }

  /* A wrapper to invoke the function via const char* */
  template <typename ToType>
  inline ToType
  lexical_cast(const char* from)
  {
      return lexical_cast<ToType>(std::string(from));
  }

  /* see lexical_cast.h for a description of casting */
  template <>
  inline bool
  lexical_cast(const std::string & from)
  {
      std::stringstream ss;
      
      if (from.size() >= 1 && (from[0] == 't' || from[0] == 'f'))
          ss << std::boolalpha;
      
      bool val;
      ss << from;
      ss >> val;
      if (! ss)
          throw bad_lexical_cast();
      
      return val;
  }


  template <>
  inline std::string
  lexical_cast(const bool & b)
  {
      std::stringstream ss;
      ss << std::boolalpha;
      ss << b;
      
      std::string tmp;
      ss >> tmp;
      if (! ss)
          throw bad_lexical_cast();
      
      return tmp;
  }

}                                                            // namespace elib
#endif /* ELIB_LEXICAL_CAST_HPP */