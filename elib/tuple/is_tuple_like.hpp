#ifndef ELIB_TUPLE_IS_TUPLE_LIKE_HPP
#define ELIB_TUPLE_IS_TUPLE_LIKE_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/aux.hpp>
# include <array>
# include <tuple>
# include <utility>
# include <cstddef>

namespace elib { namespace tuples
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        // detail::tuple_like_impl
        template <class T>
        struct tuple_like_impl : false_
        {};
        
        template <class ...Ts>
        struct tuple_like_impl<tuple<Ts...>> : true_
        {};
        
        template <class ...Ts>
        struct tuple_like_impl<tuple_types<Ts...>> : true_
        {};
        
        template <class First, class Second>
        struct tuple_like_impl<pair<First, Second>> : true_
        {};
        
        template <class ...Ts>
        struct tuple_like_impl<std::tuple<Ts...>> : true_
        {};
        
        template <class First, class Second>
        struct tuple_like_impl<std::pair<First, Second>> : true_
        {};
        
        template <class T, std::size_t N>
        struct tuple_like_impl<std::array<T, N>> : true_
        {};
    }                                                       // namespace detail
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_IS_TUPLE_LIKE_HPP */
