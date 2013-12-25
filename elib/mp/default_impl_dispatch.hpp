#ifndef ELIB_MP_DEFAULT_IMPL_DISPATCH_HPP
#define ELIB_MP_DEFAULT_IMPL_DISPATCH_HPP

namespace elib 
{
  namespace mp
  {
    
    
    struct default_impl_dispatch
    {
    //-------------------------- iterator intrinsics ------------------------// 
      template <class Iter> 
      struct iterator_category 
      {
        using type = typename Iter::category;
      };
      
      template <class Iter> 
      struct deref
      {
        using type = typename Iter::type;
      };
      
      template <class> struct next;
      template <class> struct prior;
      template <class, class> struct advance;
      template <class, long> struct advance_c;
      template <class, class> struct distance;
    
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DEFAULT_IMPL_DISPATCH_HPP */