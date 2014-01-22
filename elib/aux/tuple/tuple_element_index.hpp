#ifndef ELIB_AUX_TUPLE_TUPLE_ELEMENT_INDEX_HPP
#define ELIB_AUX_TUPLE_TUPLE_ELEMENT_INDEX_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/element_index_impl.hpp>
# include <elib/aux/type_traits.hpp>

namespace elib { namespace aux 
{
    template <class Value, class Tuple>
    struct tuple_element_index
      : tuple_detail::tuple_element_index_impl< Value, uncvref<Tuple> >
    {};
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_TUPLE_ELEMENT_INDEX_HPP */