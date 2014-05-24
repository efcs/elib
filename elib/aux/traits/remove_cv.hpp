#ifndef ELIB_AUX_TRAITS_REMOVE_CV_HPP
#define ELIB_AUX_TRAITS_REMOVE_CV_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::remove_cv;
        
    template <class T>
    using remove_cv_t = typename remove_cv<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_REMOVE_CV_HPP */
