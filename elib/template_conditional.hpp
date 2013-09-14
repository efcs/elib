#ifndef ELIB_TEMPLATE_CONDITIONAL_HPP
#define ELIB_TEMPLATE_CONDITIONAL_HPP

#include <type_traits>

namespace elib {

    
template <bool b>
struct NOT : public std::false_type
{ };


template <>
struct NOT<false> : public std::true_type
{ };
    
    
template <bool b1, bool b2, bool b3=true, bool b4=true, bool b5=true,
          bool b6=true, bool b7=true, bool b8=true, bool b9=true, bool b10=true>
struct AND : public std::false_type
{ };


template <>
struct AND<true, true, true, true, true, 
           true, true, true, true, true>
    : public std::true_type
{ };


template <bool b1, bool b2, bool b3=false, bool b4=false, bool b5=false,
          bool b6=false, bool b7=false, bool b8=false, bool b9=false, 
          bool b10=false>
struct OR : public std::true_type
{ };

template <>
struct OR<false, false, false, false, false, 
          false, false, false, false, false>
    : public std::false_type
{ };

    
} /* namespace elib */
#endif /* ELIB_TEMPLATE_CONDITIONAL_HPP */