#ifndef ELIB_TYPE_TRAITS_ADD_CONST_H
#define ELIB_TYPE_TRAITS_ADD_CONST_H

namespace elib {
namespace type_traits {
      
                
template <typename T>
struct add_const { 
    typedef const T type;
};
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_ADD_CONST_H */