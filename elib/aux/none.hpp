#ifndef ELIB_AUX_NONE_HPP
#define ELIB_AUX_NONE_HPP

# include <elib/aux/traits/is_same.hpp>

namespace elib { namespace aux
{
    struct none {};

    template <class T>
    using is_none = is_same<T, none>;
}}                                                          // namespace elib
#endif /* ELIB_AUX_NONE_HPP */