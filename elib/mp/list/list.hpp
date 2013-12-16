#ifndef ELIB_MP_LIST_LIST_HPP
#define ELIB_MP_LIST_LIST_HPP

# include <elib/mp/list/fwd.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct list 
    {
      using list = type;
      
      static_assert( sizeof...(Args) == 0, "Overload resolution check");
    };
    
    
    template <class T, class ...Args>
    struct list
    {
      using type = list;
      using item = T;
      using next = list<Args...>;
    };

    
    template <class Integral, Integral ...Values>
    using list_c = list< integral_constant<Integral, Values>... >;
    
    
    template <class ...Args>
    struct get_impl< list<Args...> >
    {
      using type = detail::list_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_LIST_HPP */
