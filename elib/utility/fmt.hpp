#ifndef ELIB_FMT_HPP
#define ELIB_FMT_HPP


#include "lexical_cast.hpp"


#include <string>
#include <cstdarg>
#include <cstdio>
#include <memory>
#include <utility>


namespace elib {
    

std::string
fmt(const std::string & msg, ...);

std::string
fmt(const std::string & msg, va_list & vl);

/* Really just a wrapper around lexical_cast<std::string, T> */
template <typename T>
std::string
fmt(T&& value);
   

} /* namespace elib */


/* inline definitions */
#include "detail/_fmt.hpp"


#endif /* ELIB_FMT_HPP */