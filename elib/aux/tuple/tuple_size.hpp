#ifndef ELIB_AUX_TUPLE_TUPLE_SIZE_HPP
#define ELIB_AUX_TUPLE_TUPLE_SIZE_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/size_impl.hpp>
# include <elib/aux/tuple/is_tuple_like.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple_size
    template <class T>
    struct tuple_size : tuple_detail::tuple_size_impl<uncvref<T>>
    {
        static_assert(
            is_tuple_like<T>::value
          , "tuple_size: invalid parameters"
        );
    };
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_TUPLE_SIZE_HPP */