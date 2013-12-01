#ifndef ELIB_MP_SET_FWD_HPP
#define ELIB_MP_SET_FWD_HPP

namespace elib 
{
  namespace mp
  {
    template <class ...Args> struct set;
    
    namespace detail
    {
      struct set_tag {};
      struct set_iter_tag {};
    }
  }                                                           // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SET_FWD_HPP */