#ifndef ELIB_TUPLE_TUPLE_TYPES_HPP
#define ELIB_TUPLE_TUPLE_TYPES_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/element_impl.hpp>
# include <elib/aux.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    
    ////////////////////////////////////////////////////////////////////////
    // tuple_types
    template <class ...Types>
    struct tuple_types {};
    
    
    namespace tuple_detail
    {
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::make_tuple_types_impl
        template <
            class TupleTypes, class Tuple
          , std::size_t Start, std::size_t End
        >
        struct make_tuple_types_impl;
        
        template <
            class ...Types, class Tuple
          , std::size_t Start, std::size_t End
        >
        struct make_tuple_types_impl<tuple_types<Types...>, Tuple, Start, End>
        {
            using TupleType = remove_ref_t<Tuple>;
            using ElementType =
                if_t<
                    is_lvalue_ref<Tuple>
                  , tuple_element_impl_t<Start, TupleType>&
                  , tuple_element_impl_t<Start, TupleType>
                  >;
            
            using type = typename
                make_tuple_types_impl<
                    tuple_types<Types..., ElementType>
                  , Tuple
                  , Start + 1, End
                >::type;
        };
        
        template <
            class ...Types, class Tuple
          , std::size_t End
        >
        struct make_tuple_types_impl<tuple_types<Types...>, Tuple, End, End>
        {
            using type = tuple_types<Types...>;
        };
    }                                                       // namespace tuple_detail
    
    ////////////////////////////////////////////////////////////////////////
    // make_tuple_types
    template <
        class Tuple
      , std::size_t End /* = tuple_size_impl<remove_ref_t<Tuple>>::value */
      , std::size_t Start /* = 0 */
    >
    struct make_tuple_types
    {
        using type = typename
            tuple_detail::make_tuple_types_impl<tuple_types<>, Tuple, Start, End>::type;
                
        static_assert( Start <= End, "make_tuple_types: invalid params");
    };
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_TUPLE_TYPES_HPP */