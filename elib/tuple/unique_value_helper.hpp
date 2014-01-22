#ifndef ELIB_TUPLE_UNIQUE_VALUE_HELPER_HPP
#define ELIB_TUPLE_UNIQUE_VALUE_HELPER_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/tuple_indexes.hpp>
# include <elib/tuple/tuple_types.hpp>
# include <elib/aux.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    namespace tuple_detail
    {
        template <std::size_t I0, class T0, std::size_t I1, class T1>
        using is_unique_value_helper = 
            or_<
                bool_<I0 == I1>
              , not_<is_same<T0, T1>>
            >;
            
        template <std::size_t I, class T, class Indexes, class Types>
        struct is_unique_value;
        
        template <std::size_t I, class T, std::size_t ...Indexes, class ...Types>
        struct is_unique_value<I, T, tuple_indexes<Indexes...>, tuple_types<Types...>>
          : fast_and< is_unique_value_helper<I, T, Indexes, Types>... >
        {};
        
        template <std::size_t I0, class T0, std::size_t I1, class Pair>
        using is_unique_key_helper =
            or_<
                bool_<I0 == I1>
              , not_<is_same<T0, typename Pair::first>>
            >;
            
        template <std::size_t I, class T, class Indexes, class Types>
        struct is_unique_key;
        
        template <
            std::size_t I, class T
          , std::size_t ...Indexes, class ...Types
        >
        struct is_unique_key<I, T, tuple_indexes<Indexes...>, tuple_types<Types...>>
          : fast_and<is_unique_key_helper<I, T, Indexes, Types>...>
        {};
        
    }                                                       // namespace tuple_detail
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_UNIQUE_VALUE_HELPER_HPP */