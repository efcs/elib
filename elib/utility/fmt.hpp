#ifndef ELIB_FMT_HPP
#define ELIB_FMT_HPP

# include <elib/config.hpp>
# include <elib/utility/lexical_cast.hpp>

# include <string>
# include <cstdarg>
# include <utility>


namespace elib {
  
  
std::string fmt(std::string msg, ...);
std::string fmt(const std::string& msg, va_list& args);
  

template <typename T>
std::string fmt(T&& value)
{
    static_assert(is_lexical<T>::value, "T must be a lexical type");
    
    return lexical_cast<std::string>(std::forward<T>(value));
}
   

} /* namespace elib */



#endif /* ELIB_FMT_HPP */