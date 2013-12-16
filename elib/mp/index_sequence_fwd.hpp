#ifndef ELIB_MP_FWD_INDEX_SEQUENCE_HPP
#define ELIB_MP_FWD_INDEX_SEQUENCE_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
        
    namespace detail
    {
      
      template <class LHS, class RHS>
      struct append_index_seq;
      
      template <std::size_t N>
      struct make_index_seq_impl;
      
    }                                                       // namespace detail
    
    
    template <std::size_t ...Indexes>
    struct index_seq;
    
    
    template <std::size_t N>
    using make_index_seq = detail::make_index_seq_impl<N>;
    
    
    template <std::size_t N>
    using make_index_seq_t = typename detail::make_index_seq_impl<N>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_FWD_INDEX_SEQUENCE_HPP */