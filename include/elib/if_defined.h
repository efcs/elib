#ifndef ELIB_IF_DEFINED_H
#define ELIB_IF_DEFINED_H


#include "enable_if.h"


namespace elib {
    
    
template <typename... Args>
struct if_def {
    static constexpr bool value = true; 
};
    

template <typename T, template <typename TProxy> class EnableIf, 
             class = void>          
struct if_defined {
    static constexpr bool value = false;
};


template <typename T, template <typename TProxy> class EnableIf>
struct if_defined<T, EnableIf, typename EnableIf<T>::type> {
    static constexpr bool value = true;
};

template <typename T, template <typename TProxy> class EnableIf>            
struct if_defined<T, EnableIf, typename enable_if<if_def<EnableIf<T>>::value>::type> {
    static constexpr bool value = true;
};




} /* namespace elib */
#endif /* ELIB_IF_DEFINED_H */