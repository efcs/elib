#ifndef ELIB_TYPE_TRAITS_REMOVE_CV_H
#define ELIB_TYPE_TRAITS_REMOVE_CV_H

#include <elib/type_traits/remove_const.h>
#include <elib/type_traits/remove_volatile.h>

namespace elib {
namespace type_traits {

        
template <typename T>
struct remove_cv : public remove_const<typename remove_volatile<T>::type>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REMOVE_CV_H */