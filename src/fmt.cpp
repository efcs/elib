#include "elib/fmt.h"

#include <cstdarg>

namespace elib {
    
std::string
fmt(const std::string & msg, ...) 
{
    va_list args;
    va_start(args, msg);
    
    /* get the size that is needed, then allocate a buffer for it*/
    unsigned n = vsnprintf(nullptr, 0, msg.c_str(), args);
    char *buff = new char[n + 10];
    
    vsnprintf(buff, n + 10, msg.c_str(), args);
    
    std::string tmp(buff);
    delete [] buff;
    return tmp;
}
    
} /* namespace elib */