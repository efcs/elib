#ifndef ELIB_MP_LIST_FWD_HPP
#define ELIB_MP_LIST_FWD_HPP

namespace elib 
{
  namespace mp
  {
    template <class ...Args> struct list;
    
    namespace detail
    {
      struct list_tag {};
      struct list_iter_tag {};
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_FWD_HPP */