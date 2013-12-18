#ifndef ELIB_MP_LIST_HPP
# define ELIB_MP_LIST_HPP

# include <elib/mp/variadic_list.hpp>
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
    };
    
    
    template <class T, T ...Values>
    using list_c = list< integral_constant<T, Values>... >;
    
    
    template <class ...Args>
    using list_iterator = variadic_list_iterator<Args...>;
    

    template <class ...Args>
    struct get_impl< list<Args...> >
    {
      using type = variadic_list_intrinsics<>;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_HPP */