#ifndef ELIB_MP_DEREF_HPP
#define ELIB_MP_DEREF_HPP

# include <elib/mp/iterator_fwd.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- deref ----------------------------------// 
    
    template <class Iter>
    struct deref
    { using type = typename Iter::type; };
    
    
    template <class Iter>
    using deref_t = typename deref<Iter>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DEREF_HPP */