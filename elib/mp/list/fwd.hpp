#ifndef ELIB_MP_LIST_FWD_HPP
#define ELIB_MP_LIST_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct list;
    
    template <class Node>
    struct list_iterator;
    
    namespace detail
    {

      struct list_intrinsics;
      struct list_iterator_intrinsics;
    
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_FWD_HPP */