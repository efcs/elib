#ifndef ELIB_TYPE_TRAITS_ADD_CONST_HPP
#define ELIB_TYPE_TRAITS_ADD_CONST_HPP

namespace elib {
namespace type_traits {
      
                
template <typename T>
struct add_const { 
    typedef const T type;
};
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_ADD_CONST_HPP */