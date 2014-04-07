#ifndef ELIB_AUX_NONE_HPP
#define ELIB_AUX_NONE_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/is_same.hpp>

namespace elib { namespace aux
{
    struct none {};

    template <class T>
    using is_none = is_same<T, none>;
    
    template <class T>
    using is_not_none = elib::bool_<
        not is_none<T>::value
      >;
}}                                                          // namespace elib
#endif /* ELIB_AUX_NONE_HPP */