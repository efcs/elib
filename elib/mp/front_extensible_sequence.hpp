#ifndef ELIB_MP_FRONT_EXTENSIBLE_SEQUENCE_HPP
#define ELIB_MP_FRONT_EXTENSIBLE_SEQUENCE_HPP

# include <elib/mp/extensible_sequence.hpp>
# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class S, class T>
    using push_front = typename get_impl_t<S>::template push_front<S, T>;
    
    template <class S, class T>
    using push_front_t = typename push_front<S, T>::type;
    
    
    template <class S>
    using pop_front = typename get_impl_t<S>::template pop_front<S>;
    
    template <class S>
    using pop_front_t = typename pop_front<S>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_FRONT_EXTENSIBLE_SEQUENCE_HPP */