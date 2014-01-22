#ifndef ELIB_TUPLE_TUPLE_ELEMENT_HPP
#define ELIB_TUPLE_TUPLE_ELEMENT_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/element_impl.hpp>
# include <elib/aux/tuple/is_tuple_like.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple_element
    template <std::size_t I, class T>
    struct tuple_element : tuple_detail::tuple_element_impl<I, T>
    {
        static_assert(
            is_tuple_like<T>::value
          , "tuple_element: invalid parameters"
        );
    };
}}                                                           // namespace elib
#endif /* ELIB_TUPLE_TUPLE_ELEMENT_HPP */