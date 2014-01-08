#ifndef ELIB_MP_ITERATOR_ITERATOR_HPP
#define ELIB_MP_ITERATOR_ITERATOR_HPP

# include <elib/mp/iterator/fwd.hpp>
# include <elib/mp/get_impl.hpp>
// to get iterable functionality for integral_constant
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/detail/integral_constant_intrinsics.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Iter>
    using iterator_category_t = 
      typename get_impl_t<Iter>::template iterator_category<Iter>::type;
      
    template <class Iter>
    struct iterator_category : get_impl_t<Iter>::template iterator_category<Iter>
    {};
    
    
    template <class Iter> 
    using deref_t = typename get_impl_t<Iter>::template deref<Iter>::type;
    
    template <class Iter>
    struct deref : get_impl_t<Iter>::template deref<Iter>
    {};
    
    
    template <class Iter, class N>
    using advance_t = 
      typename get_impl_t<Iter>::template advance<Iter, N>::type;
    
    template <class Iter, class N>
    struct advance : get_impl_t<Iter>::template advance<Iter, N>
    {};
    
    
    template <class Iter, long N>
    using advance_c_t = 
      typename get_impl_t<Iter>::template advance_c<Iter, N>::type;
    
    template <class Iter, long N>
    struct advance_c : get_impl_t<Iter>::template advance_c<Iter, N>
    {};
    
    
    template <class First, class Last>
    using distance_t = 
      typename get_impl_t<First>::template distance<First, Last>::type;
    
    template <class First, class Last>
    struct distance : get_impl_t<First>::template distance<First, Last>
    {};
    
    
    template <class Iter>
    using next_t = typename get_impl_t<Iter>::template next<Iter>::type;
    
    template <class Iter>
    struct next : get_impl_t<Iter>::template next<Iter>
    {};
    
    
    template <class Iter>
    using prior_t = typename get_impl_t<Iter>::template prior<Iter>::type;
    
    template <class Iter>
    struct prior : get_impl_t<Iter>::template prior<Iter>
    {};
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_ITERATOR_HPP */