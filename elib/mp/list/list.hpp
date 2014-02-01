#ifndef ELIB_MP_LIST_LIST_HPP
#define ELIB_MP_LIST_LIST_HPP

# include <elib/mp/list/list_intrinsics.hpp>
# include <elib/mp/list/list_iterator.hpp>
# include <elib/mp/list/list_iterator_intrinsics.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/sequence_traits.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct list_tag {};
    
    struct list_model
      : model::variadic
      , model::forward_sequence
      , model::front_extensible_variadic_sequence
      , model::O1_size
    {};
    
    template <class ...Args>
    struct list
    {
      using type = list;
      
      /* for sequence_traits */
      using class_type = list_tag;
      using model_type = list_model;
    };
    
    
    template <class T, T ...Values>
    using list_c = list< integral_constant<T, Values>... >;

    template <class ...Args>
    struct get_impl< list<Args...> >
    {
      using type = list_intrinsics;
    };
    

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_LIST_HPP */