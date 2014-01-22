#ifndef ELIB_TUPLE_SIZE_IMPL_HPP
#define ELIB_TUPLE_SIZE_IMPL_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/aux.hpp>
# include <tuple>
# include <utility>

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
        
        template <class ...Types>
        struct tuple_size_impl< tuple<Types...> >
          : size_type_<sizeof...(Types)>
        {};
        
        template <class First, class Second>
        struct tuple_size_impl< pair<First, Second>>
          : size_type_<2>
        {};
        
    }                                                       // namespace detail
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_SIZE_IMPL_HPP */