#ifndef ELIB__FMT_H
#define ELIB__FMT_H


#ifndef ELIB_FMT_H
#   error only include this file through fmt.h
#endif


namespace elib {
    
        
inline std::string
fmt(const std::string & msg, ...) 
{
    constexpr unsigned BUFF_MAX = 10000;
    
    va_list args;
    va_start(args, msg);
    
    char buff[BUFF_MAX];
    vsnprintf(buff, BUFF_MAX-1, msg.c_str(), args);
    
    va_end(args);
    
    return std::string(buff);
}

inline std::string
fmt(const std::string & msg, va_list & vl)
{
    constexpr unsigned BUFF_MAX = 10000;
    
    char buff[BUFF_MAX];
    vsnprintf(buff, BUFF_MAX-1, msg.c_str(), vl);
    return std::string(buff);
}
    
    
template <typename T>
inline std::string
fmt(T&& value)
{
    static_assert(is_lexical<T>::value, "T must be a lexical type");
    
    return lexical_cast<std::string>(std::forward<T>(value));
}


} /* namespace elib */
#endif /* ELIB__FMT_H */