#ifndef ELIB_AUX_TRAITS_ADD_CV_HPP
#define ELIB_AUX_TRAITS_ADD_CV_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::add_cv;
        
    template <class T>
    using add_cv_t = typename add_cv<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ADD_CV_HPP */
