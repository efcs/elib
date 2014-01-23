#ifndef ELIB_TUPLE_BITS_TUPLE_ELEMENT_IMPL_HPP
# define ELIB_TUPLE_BITS_TUPLE_ELEMENT_IMPL_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/aux.hpp>
# include <elib/params.hpp>
# include <tuple>
# include <cstddef>

namespace elib { namespace tuples
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        // detail::tuple_element_impl
        template <std::size_t I, class T>
        struct tuple_element_impl
          : std::tuple_element<I, T>
        {};
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, tuple_types<Args...> >
          : params::at<tuple_types<Args...>, I>
        {};
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, tuple<Args...>>
          : params::at<tuple<Args...>, I>
        {};
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, tuple<Args...> const>
        {
            using type = 
                aux::add_const_t<
                    params::at_t<tuple<Args...>, I>
                >;  
        };
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, tuple<Args...> volatile>
        {
            using type =
                aux::add_volatile_t<
                    params::at_t<tuple<Args...>, I>
                >;
        };
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, tuple<Args...> const volatile>
        {
            using type = 
                aux::add_cv_t<
                    params::at_t<tuple<Args...>, I>
                  >;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, pair<First, Second>>
        {
            using type = params::at_t<pair<First, Second>, I>;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, pair<First, Second> const>
        {
            using type = 
                aux::add_const_t<
                    params::at_t<pair<First, Second>, I>
                >;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, pair<First, Second> volatile>
        {
            using type = 
                aux::add_volatile_t<
                    params::at_t<pair<First, Second>, I>
                >;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, pair<First, Second> const volatile>
        {
            using type = 
                aux::add_cv_t<
                    params::at_t<pair<First, Second>, I>
                >;
        };        
    }                                                       // namespace detail
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_BITS_TUPLE_ELEMENT_IMPL_HPP */