#ifndef ELIB__FMT_H
#define ELIB__FMT_H


#ifndef ELIB_FMT_H
#   error only include this file through fmt.h
#endif


namespace elib {
    
    
template <typename T>
std::string
fmt(T&& value)
{
    static_assert(is_lexical<T>::value, "T must be a lexical type");
    
    return lexical_cast<std::string>(std::forward<T>(value));
}


} /* namespace elib */
#endif /* ELIB__FMT_H */