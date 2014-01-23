#ifndef ELIB_TUPLE_TUPLE_ELEMENT_HPP
#define ELIB_TUPLE_TUPLE_ELEMENT_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/bits/tuple_element_impl.hpp>
# include <elib/tuple/is_tuple_like.hpp>
# include <elib/aux.hpp>
# include <elib/params.hpp>
# include <tuple>
# include <cstddef>

namespace elib { namespace tuples
{
    ////////////////////////////////////////////////////////////////////////////
    // tuple_element
    template <std::size_t I, class T>
    struct tuple_element : detail::tuple_element_impl<I, T>
    {};
}}                                                           // namespace elib
#endif /* ELIB_TUPLE_TUPLE_ELEMENT_HPP */