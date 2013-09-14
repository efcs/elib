#ifndef ELIB_TYPE_TRAITS_ADD_VOLATILE_H
#define ELIB_TYPE_TRAITS_ADD_VOLATILE_H

namespace elib {
namespace type_traits {

    
template <typename T>
struct add_volalite {
    typedef volatile T type;
};
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_ADD_VOLATILE_H */