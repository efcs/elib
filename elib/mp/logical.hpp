#ifndef ELIB_MPL_LOGICAL_HPP
# define ELIB_MPL_LOGICAL_HPP

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
    
    
    
  }                                                         //  namespace mp
}                                                           // namespace elib
#endif /* ELIB_MPL_LOGICAL_HPP */