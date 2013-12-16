#ifndef ELIB_MP_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_ITERATOR_INTRINSICS_HPP

# include <elib/mp/get_impl.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Iter, class N>
    using advance = typename get_impl_t<Iter>::template advance<Iter, N>;
    
    template <class Iter, class N>
    using advance_t = typename advance<Iter, N>::type;
    
    
    template <class Iter, long N>
    using advance_c = typename get_impl_t<Iter>::template 
      advance<Iter, integral_constant<long, N> >;
    
    template <class Iter, long N>
    using advance_c_t = typename advance_c<Iter, N>::type;
    
    
    template <class Begin, class End>
    using distance = typename get_impl_t<Begin>::template distance<Begin, End>;
    
    template <class Begin,  class End>
    using distance_t = typename distance<Begin, End>::type;
    
    
    template <class Iter>
    using next = typename get_impl_t<Iter>::template next<Iter>;
    
    template <class Iter>
    using next_t = typename next<Iter>::type;
    
    
    template <class Iter>
    using prior = typename get_impl_t<Iter>::template prior<Iter>;
    
    template <class Iter>
    using prior_t = typename prior<Iter>::type;
    
    
    template <class Iter>
    using deref = typename get_impl_t<Iter>::template deref<Iter>;
    
    template <class Iter>
    using deref_t = typename deref<Iter>::type;
    
    
    template <class Iter>
    using iterator_category = typename get_impl_t<Iter>::template 
      iterator_category<Iter>;
      
    template <class Iter>
    using iterator_category_t = typename iterator_category<Iter>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_INTRINSICS_HPP */