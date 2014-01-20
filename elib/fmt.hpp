#ifndef ELIB_FMT_HPP
#define ELIB_FMT_HPP

# include <elib/assert.hpp>
# include <elib/lexical_cast.hpp>
# include <elib/CXX14/memory.hpp> /* for std::make_unique */

# include <string>
# include <utility>  /* for std::forward */
# include <cstdio>
# include <cstdarg>

namespace elib 
{
  
  inline std::string fmt(std::string msg, ...) 
  {
      va_list args;
      va_start(args, msg);
      auto tmp = fmt(msg, args);
      va_end(args);
      return tmp;
  }

# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wformat-nonliteral"
# endif


  inline std::string fmt(const std::string& msg, va_list& args)
  {
      // we might need a second shot at this, so pre-emptivly make a copy
      va_list args_cp;
      va_copy(args_cp, args);
      
      // guess what the size might be
      std::size_t size = 256;
      auto buff_ptr = std::make_unique<char[]>(size);
      auto ret = vsnprintf(buff_ptr.get(), size, msg.c_str(), args_cp);
      
      // currently there is no error handling for failure, 
      // so this is hack
      ELIB_ASSERT(ret > 0);
        
      va_end(args_cp);
      
      // we did not provide a long enough buffer on our first attempt
      if (static_cast<std::size_t>(ret) >= size)
      {
        // account for null-byte in size
        // cast to prevent overflow
        size = static_cast<std::size_t>(ret) + 1;
        buff_ptr = std::make_unique<char[]>(size);
        ret = vsnprintf(buff_ptr.get(), size, msg.c_str(), args);
        ELIB_ASSERT(ret > 0 && static_cast<std::size_t>(ret) < size);
      }
      
      return { buff_ptr.get() };
  }
    
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
  
  template <typename T>
  std::string fmt(T&& value)
  {
      static_assert(is_lexical<T>::value, "T must be a lexical type");
      
      return lexical_cast<std::string>(std::forward<T>(value));
  }
   
}                                                            // namespace elib
#endif                                                  // ELIB_FMT_HPP