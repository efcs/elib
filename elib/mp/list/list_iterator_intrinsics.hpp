#ifndef ELIB_MP_LIST_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_LIST_ITERATOR_INTRINSICS_HPP

# include <elib/mp/list/list_iterator.hpp>
# include <elib/mp/list/list_intrinsics.hpp>
# include <elib/aux.hpp>
# include <elib/params.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    struct list_iterator_intrinsics
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
      using advance = params::drop<S, N::type::value>;
      
      template <class S, std::size_t N>
      using advance_c = params::drop<S, N>;
    
    //-------------------------------- distance --------------------------------// 
    
      template <class Left, class Right> struct distance;
      
      template <template <class...> class It, class ...Left, class ...Right>
      struct distance< It<Left...>, It<Right...> >
        : aux::llong_< static_cast<long long>(sizeof...(Left) - sizeof...(Right))>
      {};
      
    };                                                      // list_iterator_intrinsics
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_ITERATOR_INTRINSICS_HPP */