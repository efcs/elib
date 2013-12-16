#ifndef ELIB_MP_RANDOM_ACCESS_SEQUENCE_HPP
#define ELIB_MP_RANDOM_ACCESS_SEQUENCE_HPP

# include <elib/mp/bidirectional_sequence.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class S, class N>
    using at = typename get_impl_t<S>::template at<S, N>;
    
    template <class S, class N>
    using at_t = typename at<S, N>::type;
    
    
    template <class S, std::size_t N>
    using at_c = at<S, size_type<N>>;
    
    template <class S, std::size_t N>
    using at_c_t = typename at<S, size_type<N>>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_RANDOM_ACCESS_SEQUENCE_HPP */