#ifndef ELIB_MP_VECTOR_FWD_HPP
#define ELIB_MP_VECTOR_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    struct vector_tag {};
    
    template <class ...Args>
    struct vector;
    
    template <class Vector, std::size_t Pos>
    struct vector_iterator;
    
    namespace detail
    {
      
      struct vector_intrinsics;
      struct vector_iterator_intrinsics;
      
      template <class Tag, class Vector, class ...Args>
      struct vector_item;
      
      template <class Tag, class Vector>
      struct vector_mask;
      
      struct vector_front_tag {};
      struct vector_back_tag {};
      
    }                                                       // namespace detail
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VECTOR_FWD_HPP */