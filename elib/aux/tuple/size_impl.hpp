#ifndef ELIB_AUX_TUPLE_SIZE_IMPL_HPP
#define ELIB_AUX_TUPLE_SIZE_IMPL_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/integral_constant.hpp>
# include <tuple>

namespace elib { namespace aux
{
    namespace tuple_detail
    {
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_size_impl
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
        struct tuple_size_impl< aux::tuple<Types...> >
          : size_type_<sizeof...(Types)>
        {};
        
        template <class First, class Second>
        struct tuple_size_impl< aux::pair<First, Second>>
          : size_type_<2>
        {};
        
    }                                                       // namespace tuple_detail
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_SIZE_IMPL_HPP */