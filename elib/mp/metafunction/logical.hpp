#ifndef ELIB_MP_METAFUNCTION_LOGICAL_HPP
#define ELIB_MP_METAFUNCTION_LOGICAL_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
   
  ////////////////////////////////////////////////////////////////////////////////
  //                                 NOT
  ////////////////////////////////////////////////////////////////////////////////
    

    template <class T>
    struct not_ 
      : std::integral_constant<bool, static_cast<bool>(!T::type::value)>
    {};
    
    
    template <class T>
    using not_t = typename not_<T>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                          AND                                                   
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
      
      template <bool B, class ...Args>
      struct and_impl : false_
      {
        static_assert(!B, "B must be false");
      };
      
      template <class ...Args>
      struct and_impl<true, Args...> : true_
      {
        static_assert(sizeof...(Args) == 0,  "Param pack must be empty");
      };
    
      template <class First, class ...Rest>
      struct and_impl<true, First, Rest...>
        : and_impl<static_cast<bool>(First::type::value), Rest...>
      {};
      
      
    }                                                       // namespace detail
    
    template <class P1, class P2, class ...Rest>
    struct and_ 
      : detail::and_impl<static_cast<bool>(P1::type::value), P2, Rest...>
    {};
    
    
    template <class P1, class P2, class ...Rest>
    using and_t = typename and_<P1, P2, Rest...>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                             OR                                             
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
        
      template <bool B, class ...Args>
      struct or_impl : false_
      {
        static_assert(!B, "B must be false");
      };
      
      template <class ...Args>
      struct or_impl<true, Args...> : true_
      {};
      
      template <class First, class ...Rest>
      struct or_impl<false, First, Rest...> 
        : or_impl<static_cast<bool>(First::type::value), Rest...>
      {};
      
    }                                                       // namespace detail
    
    
    template <class P1, class P2, class ...Rest>
    struct or_ 
      : detail::or_impl<static_cast<bool>(P1::type::value), P2, Rest...>
    {};
    
    
    template <class P1, class P2, class ...Rest>
    using or_t = typename or_<P1, P2, Rest...>::type;
    
  }                                                         //  namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_LOGICAL_HPP */