#ifndef ELIB__LEXICAL_CAST_H
#define ELIB__LEXICAL_CAST_H


#ifndef ELIB_LEXICAL_CAST_H
#   error do not include this file directly
#endif


#include <sstream>


namespace elib {
    

template <typename ToType, typename FromType>
inline ToType
lexical_cast(const FromType & from)
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

    
} /* namespace elib */
#endif /* ELIB__LEXICAL_CAST_H */