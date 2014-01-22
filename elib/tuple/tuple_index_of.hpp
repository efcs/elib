#ifndef ELIB_TUPLE_TUPLE_INDEX_OF_HPP
#define ELIB_TUPLE_TUPLE_INDEX_OF_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/index_of_impl.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    template <class Key, class T>
    struct tuple_index_of
      : tuple_detail::tuple_index_of_impl<Key, T>
    {};
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_TUPLE_INDEX_OF_HPP *