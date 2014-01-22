#ifndef ELIB_TUPLE_TUPLE_ELEMENT_INDEX_HPP
#define ELIB_TUPLE_TUPLE_ELEMENT_INDEX_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/element_index_impl.hpp>
# include <elib/aux.hpp>

namespace elib { namespace tuples 
{
    template <class Value, class Tuple>
    struct tuple_element_index
      : detail::tuple_element_index_impl< Value, aux::uncvref<Tuple> >
    {};
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_TUPLE_ELEMENT_INDEX_HPP */