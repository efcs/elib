#ifndef ELIB_AUX_TUPLE_HPP
#define ELIB_AUX_TUPLE_HPP

# include <elib/aux/tuple_fwd.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/integer_sequence.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/type_traits.hpp>
# include <elib/aux/pair.hpp>
# include <elib/params.hpp>
# include <tuple>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple_size
    template <class ...Args>
    struct tuple_size< tuple<Args...> >
      : size_type_<sizeof...(Args)>
    {};
    
    template <class ...Args>
    struct tuple_size< std::tuple<Args...> >
      : size_type_<sizeof...(Args)>
    {};
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple_element
    template <std::size_t I, class ...Args>
    struct tuple_element< I, tuple<Args...> >
      : params::at<tuple<Args...>, I>
    {};
    
    template <std::size_t I, class ...Args>
    struct tuple_element< I, std::tuple<Args...> >
      : std::tuple_element<I, std::tuple<Args...>>
    {};
    
    namespace detail
    {
        template <std::size_t I, class T>
        struct tuple_item
        {
            using type = tuple_item;
            using value_type = T;
            using index = size_type_<I>;
            
            T item;
        };
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple
    template <class ...Type>
    struct tuple;
    
    
    
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_HPP */