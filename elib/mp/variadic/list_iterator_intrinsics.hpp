#ifndef ELIB_MP_VARIADIC_LIST_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_VARIADIC_LIST_ITERATOR_INTRINSICS_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/list_iterator.hpp>
# include <elib/mp/variadic/list_intrinsics.hpp>
# include <elib/mp/variadic/detail/list_advance_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    struct variadic_list_iterator_intrinsics
    {
     
    //-------------------------------- deref --------------------------------// 
      
      template <class It> struct deref;
      
      template <template <class...> class It, class First, class ...Rest>
      struct deref< It<First, Rest...> > : identity< First >
      {};
      
    //-------------------------------- next --------------------------------// 
    
      template <class It> struct next;
      
      template <template <class...> class It, class First, class ...Rest>
      struct next< It<First, Rest...> > : identity< It<Rest...> >
      {};
      
    //-------------------------------- advance --------------------------------// 
    
      template <class S, class N>
      using advance = detail::variadic_list_advance_impl<S, N::type::value>;
      
      template <class S, std::size_t N>
      using advance_c = detail::variadic_list_advance_impl<S, N>;
    
    //-------------------------------- distance --------------------------------// 
    
      template <class Left, class Right> struct distance;
      
      template <template <class...> class It, class ...Left, class ...Right>
      struct distance< It<Left...>, It<Right...> >
        : llong_< static_cast<long long>(sizeof...(Left) - sizeof...(Right))>
      {};
      
    };                                                      // variadic_list_iterator_intrinsics
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_LIST_ITERATOR_INTRINSICS_HPP */