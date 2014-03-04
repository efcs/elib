#ifndef ELIB_TUPLE_BITS_TUPLE_SIZE_HPP
#define ELIB_TUPLE_BITS_TUPLE_SIZE_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/is_tuple_like.hpp>
# include <elib/aux.hpp>
# include <tuple>
# include <utility>
# include <cstddef>

namespace elib { namespace tuples
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        // detail::tuple_size_impl
        template <class T>
        struct tuple_size_impl
          : std::tuple_size<T>
        {};
        
        template <class T>
        struct tuple_size_impl<T const>
          : tuple_size_impl<T>
        {};
        
        template <class T>
        struct tuple_size_impl<T volatile>
          : tuple_size_impl<T>
        {};
        
        template <class T>
        struct tuple_size_impl<T const volatile>
          : tuple_size_impl<T>
        {};
        
        template <class ...Types>
        struct tuple_size_impl< tuple_types<Types...> >
          : size_type_<sizeof...(Types)>
        {};
        
        template <class Indexes, class ...Types>
        struct tuple_size_impl< tuple_impl<Indexes, Types...> >
          : size_type_<sizeof...(Types)>
        {};
        
        template <class ...Types>
        struct tuple_size_impl< tuple<Types...> >
          : size_type_<sizeof...(Types)>
        {};
        
        template <class First, class Second>
        struct tuple_size_impl< pair<First, Second>>
          : size_type_<2>
        {};
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    // tuple_size
    template <class T>
    struct tuple_size : detail::tuple_size_impl<aux::uncvref<T>>
    {
        static_assert(
            is_tuple_like<T>::value
          , "tuple_size: invalid parameters"
        );
    };
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_BITS_TUPLE_SIZE_HPP */