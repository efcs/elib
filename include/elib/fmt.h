#ifndef ELIB_FMT_H
#define ELIB_FMT_H

#include <string>
#include <cstdarg>

namespace elib {

std::string
fmt(const std::string & msg, ...);

std::string
fmt(const std::string & msg, va_list & vl);
    
} /* namespace elib */
#endif /* ELIB_FMT_H */