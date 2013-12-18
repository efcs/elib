#ifndef ELIB_MP_LIST_LIST_HPP
#define ELIB_MP_LIST_LIST_HPP

# include <elib/mp/list/fwd.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct list
    {
      using type = list;
      
      static_assert(sizeof...(Args) == 0, "Overload resolution check");
    };
    
    
    template <class T, class ...Args>
    struct list<T, Args...>
    {
      using type = list;
    };
    
    
    template <class T, T ...Values>
    using list_c = list< integral_constant<T, Values>... >;
    
    
    template <class ...Args>
    struct get_impl< list<Args...> >
    {
      using type = detail::list_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_LIST_HPP */