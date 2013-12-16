#ifndef ELIB_MP_EXTENSIBLE_SEQUENCE_HPP
#define ELIB_MP_EXTENSIBLE_SEQUENCE_HPP

# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class S, class Pos, class T>
    struct insert 
      : typename get_impl_t<S>::template insert<S, Pos, T>
    {};
    
    template <class S, class Pos, class T>
    using insert_t = typename insert<S, Pos, T>::type;
    
    
    template <class S, class Pos, class Range>
    struct insert_range 
      : typename get_impl_t<S>::template insert_range<S, Pos, Range>
    {};
    
    template <class S, class Pos, class Range>
    using insert_range_t = typename insert_range<S, Pos, Range>::type;
    
    
    template <class S, class Pos, class Last = na>
    struct erase 
      : typename get_impl_t<S>::template erase<S, Pos, Last>
    {};
    
    template <class S, class Pos, class Last = na>
    using erase_t = typename erase<S, Pos, Last>::type;
    
    
    template <class S>
    struct clear 
      : typename get_impl_t<S>::template clear<S>
    {};
    
    template <class S>
    using clear_t = typename clear<S>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_EXTENSIBLE_SEQUENCE_HPP */