#ifndef ELIB_FMT_HPP
#define ELIB_FMT_HPP


#include "lexical_cast.hpp"


#include <string>
#include <cstdarg>
#include <cstdio>
#include <memory>
#include <utility>


namespace elib {
    

inline std::string
fmt(std::string msg, ...) 
{
    va_list args;
    va_start(args, msg);
    
    va_list args_cp;
    va_copy(args_cp, args);
    
    auto size = vsnprintf(nullptr, 0, msg.c_str(), args_cp);
    
    va_end(args_cp);
    
    std::unique_ptr<char[]> buff_ptr(new char[size+1]);
    vsnprintf(buff_ptr.get(), size+1, msg.c_str(), args);
    
    va_end(args);
    
    return std::string(buff_ptr.get());
}

inline std::string
fmt(const std::string & msg, va_list & vl)
{
    va_list args_cp;
    va_copy(args_cp, vl);
    
    auto size = vsnprintf(nullptr, 0, msg.c_str(), args_cp);
    
    va_end(args_cp);
    
    std::unique_ptr<char[]> buff_ptr(new char[size+1]);
    vsnprintf(buff_ptr.get(), size+1, msg.c_str(), vl);
    
    va_end(vl);
    
    return std::string(buff_ptr.get());
}
    
    
template <typename T>
inline std::string
fmt(T&& value)
{
    static_assert(is_lexical<T>::value, "T must be a lexical type");
    
    return lexical_cast<std::string>(std::forward<T>(value));
}
   

} /* namespace elib */



#endif /* ELIB_FMT_HPP */