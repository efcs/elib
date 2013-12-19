#ifndef ELIB_MP_LIST_HPP
# define ELIB_MP_LIST_HPP

# include <elib/mp/variadic_list.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/detail/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct list_tag {};
    
    template <class ...Args>
    struct list
    {
      using type = list;
      
      /* for sequence_traits */
      using class_type = list_tag;
      using category = mpl_variadic_list_tag;
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