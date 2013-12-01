#ifndef ELIB_MP_RANGE_C_FWD_HPP
#define ELIB_MP_RANGE_C_FWD_HPP

namespace elib 
{
  namespace mp
  {
    template <class T, T Start, T Finish> struct range_c;
    
    namespace detail
    {
      struct range_c_tag {};
      struct range_c_iter_tag {};
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_RANGE_C_FWD_HPP */