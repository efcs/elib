#ifndef ELIB_TYPE_TRAITS_ADD_CV_H
#define ELIB_TYPE_TRAITS_ADD_CV_H

#include <elib/type_traits/add_const.hpp>
#include <elib/type_traits/add_volatile.hpp>

namespace elib {
namespace type_traits {
        
        
template <typename T>
struct add_cv : public add_const<typename add_volatile<T>::type>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_ADD_CV_H */
