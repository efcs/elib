#ifndef ELIB_MP_ITERATOR_HPP
#define ELIB_MP_ITERATOR_HPP

# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {   
    
    struct forward_iterator_tag {};
    struct bidirectional_iterator_tag {};
    struct random_access_iterator_tag {};
    
    
    template <class Iter>
    using iterator_category = 
      typename get_impl_t<Iter>::template iterator_category<Iter>;
      
    template <class Iter>
    using iterator_category_t = typename iterator_category<Iter>::type;
    
    
    template <class Iter> 
    using deref = typename get_impl_t<Iter>::template deref<Iter>;
    
    template <class Iter>
    using deref_t = typename deref<Iter>::type;
    
    
    template <class Iter, class N>
    using advance = typename get_impl_t<Iter>::template advance<Iter, N>;
    
    template <class Iter, class N>
    using advance_t = typename advance<Iter, N>::type;
    
    
    template <class Iter, long N>
    using advance_c = typename get_impl_t<Iter>::template advance_c<Iter, N>;
    
    template <class Iter, long N>
    using advance_c_t = typename advance_c<Iter, N>::type;
    
    
    template <class First, class Last>
    using distance = typename get_impl_t<First>::template distance<First, Last>;
    
    template <class First, class Last>
    using distance_t = typename distance<First, Last>::type;
    
    
    template <class Iter>
    using next = typename get_impl_t<Iter>::template next<Iter>;
    
    template <class Iter>
    using next_t = typename next<Iter>::type;
    
    
    template <class Iter>
    using prior = typename get_impl_t<Iter>::template prior<Iter>;
    
    template <class Iter>
    using prior_t = typename prior<Iter>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_HPP */