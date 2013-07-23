#ifndef ELIB_LEXICALCAST_H
#define ELIB_LEXICALCAST_H


#include <stdexcept>
#include <sstream>
#include <string>

namespace elib {
    
    
class bad_lexical_cast : public std::runtime_error {
public:
    bad_lexical_cast()
        : std::runtime_error("bad lexical cast")
    { }
};


template <typename ToType, typename FromType>
ToType
lexical_cast(const FromType & from);


/* specializations for booleans
 * attempt to use std::boolalpha when appropriate */
template <>
bool
lexical_cast(const std::string & from);

template <>
std::string
lexical_cast(const bool & b);

    
template <typename ToType, typename FromType>
inline ToType
lexical_cast(const FromType & from)
{
    std::stringstream ss;
    ToType val;
    
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


    
} /* namespace elib */
#endif /* ELIB_LEXICALCAST_H */