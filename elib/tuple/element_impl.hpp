#ifndef ELIB_TUPLE_ELEMENT_IMPL_HPP
#define ELIB_TUPLE_ELEMENT_IMPL_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/type_traits.hpp>
# include <elib/params.hpp>
# include <tuple>
# include <cstddef>

namespace elib { namespace aux 
{
    namespace tuple_detail
    {
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_element_impl
        template <std::size_t I, class T>
        struct tuple_element_impl
          : std::tuple_element<I, T>
        {};
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, tuple_types<Args...> >
          : params::at<tuple_types<Args...>, I>
        {};
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, aux::tuple<Args...>>
          : params::at<aux::tuple<Args...>, I>
        {};
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, aux::tuple<Args...> const>
        {
            using type = 
                add_const_t<
                    params::at_t<aux::tuple<Args...>, I>
                >;  
        };
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, aux::tuple<Args...> volatile>
        {
            using type =
                add_volatile_t<
                    params::at_t<aux::tuple<Args...>, I>
                >;
        };
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, aux::tuple<Args...> const volatile>
        {
            using type = 
                add_cv_t<
                    params::at_t<aux::tuple<Args...>, I>
                  >;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, aux::pair<First, Second>>
        {
            using type = params::at_t<aux::pair<First, Second>, I>;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, aux::pair<First, Second> const>
        {
            using type = 
                add_const_t<
                    params::at_t<aux::pair<First, Second>, I>
                >;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, aux::pair<First, Second> volatile>
        {
            using type = 
                add_volatile_t<
                    params::at_t<aux::pair<First, Second>, I>
                >;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, aux::pair<First, Second> const volatile>
        {
            using type = 
                add_cv_t<
                    params::at_t<aux::pair<First, Second>, I>
                >;
        };        
    }
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_ELEMENT_IMPL_HPP */