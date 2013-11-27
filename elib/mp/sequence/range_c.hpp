#ifndef ELIB_MP_SEQUENCE_RANGE_C_HPP
#define ELIB_MP_SEQUENCE_RANGE_C_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
    //-------------------------------- range_c tags -------------------------// 
      struct range_c_tag {};
      struct range_c_iter_tag {};
    }                                                       // namespace detail
    
  //-------------------------------- range_c --------------------------------// 
    
    template <class T, T Begin, T End>
    struct range_c 
    {
      using type = range_c;
      using tag = detail::range_c_tag;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_RANGE_C_HPP */