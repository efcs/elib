#ifndef ELIB_STATIC_STRING_H
#define ELIB_STATIC_STRING_H


#include <string>


namespace elib {
    
    
/* this class is a usefull abstraction. 
 * brace initalization allows for 
 * compile-time evaluation of this class 
 * basic_static_string<> s{"abc"} */
template <unsigned N=1024>
struct basic_static_string {
    
    /* the actual value, uniform initalization of 
     * this basic_static_string can be used in a constexpr */
    char string_value[N];
    
    /* returns the actual size of the string (not N)
     * ie strlen(string_value) */
    unsigned
    size() const;
    
    /* return string_value[0] == '\0' */
    constexpr
    operator bool() const;
    
    /* return string_value */
    constexpr const char*
    c_str() const;
    
    /* same as above */
    constexpr
    operator const char*() const;
    
    /* string access */
    constexpr char
    operator[](unsigned i) const;
    
    char &
    operator[](unsigned i);
    
    std::string
    str() const;
};


typedef basic_static_string<> static_string;

    
} /* namespace elib */


#include "detail/_static_string.h"


#endif /* ELIB_STATIC_STRING_H */