#ifndef ELIB_MP_LIST_FWD_HPP
#define ELIB_MP_LIST_FWD_HPP

namespace elib 
{
  namespace mp
  {
    template <class ...Args> struct list;
    template <class T, T ...Values> struct list_c;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_FWD_HPP */