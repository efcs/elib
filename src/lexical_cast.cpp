#include "elib/lexical_cast.h"

namespace elib {
   
    
template <>
bool
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
std::string
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