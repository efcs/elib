#include "elib/fmt.h"



#define BUFF_MAX 10000

namespace elib {
    
std::string
fmt(const std::string & msg, ...) 
{
    va_list args;
    va_start(args, msg);
    
    char buff[BUFF_MAX];
    vsnprintf(buff, BUFF_MAX-1, msg.c_str(), args);
    
    va_end(args);
    
    return std::string(buff);
}

std::string
fmt(const std::string & msg, va_list & vl)
{
    char buff[BUFF_MAX];
    vsnprintf(buff, BUFF_MAX-1, msg.c_str(), vl);
    return std::string(buff);
}
    
} /* namespace elib */