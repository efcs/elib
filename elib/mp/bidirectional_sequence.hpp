#ifndef ELIB_MP_BIDIRECTIONAL_SEQUENCE_HPP
#define ELIB_MP_BIDIRECTIONAL_SEQUENCE_HPP

# include <elib/mp/forward_sequence.hpp>
# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class S>
    using back = typename get_impl_t<S>::template back<S>;

    template <class S>
    using back_t = typename back<S>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_BIDIRECTIONAL_SEQUENCE_HPP */