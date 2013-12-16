#ifndef ELIB_MP_BACK_EXTENSIBLE_SEQUENCE_HPP
#define ELIB_MP_BACK_EXTENSIBLE_SEQUENCE_HPP

# include <elib/mp/extensible_sequence.hpp>
# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class S, class T>
    using push_back = typename get_impl_t<S>::template push_back<S, T>;
    
    template <class S, class T>
    using push_back_t = typename push_back<S, T>::type;
    
    
    template <class S>
    using pop_back = typename get_impl_t<S>::template pop_back<S>;
    
    template <class S>
    using pop_back_t = typename pop_back<S>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_BACK_EXTENSIBLE_SEQUENCE_HPP */