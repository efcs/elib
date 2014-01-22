#ifndef ELIB_TUPLE_TUPLE_INDEXES_HPP
#define ELIB_TUPLE_TUPLE_INDEXES_HPP

# include <elib/tuple/fwd.hpp>
# include <cstddef>

namespace elib { namespace tuples
{
    ////////////////////////////////////////////////////////////////////////
    // tuple_indexes
    template <std::size_t ...I>
    struct tuple_indexes {};
    
    
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        // detail::make_tuple_indexes_impl
        template <std::size_t Start, class Indexes, std::size_t End>
        struct make_tuple_indexes_impl;
        
        template <std::size_t Start, std::size_t ...Indexes, std::size_t End>
        struct make_tuple_indexes_impl<Start, tuple_indexes<Indexes...>, End>
        {
            using type = typename
                make_tuple_indexes_impl< 
                    Start + 1
                  , tuple_indexes<Indexes..., Start>
                  , End
                >::type;
        };
        
        template <std::size_t End, std::size_t ...Indexes>
        struct make_tuple_indexes_impl<End, tuple_indexes<Indexes...>, End>
        {
            using type = tuple_indexes<Indexes...>;
        };
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////
    // make_tuple_indexes
    template <std::size_t End, std::size_t Start /* = 0 */>
    struct make_tuple_indexes
    {
        using type = typename 
            detail::make_tuple_indexes_impl<Start, tuple_indexes<>, End>::type;
                
        static_assert(
            Start <= End
          , "Invalid parameters for make_tuple_indexes"
        );
    };
    
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_TUPLE_INDEXES_HPP */