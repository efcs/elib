#ifndef ELIB_MP_VECTOR_FWD_HPP
#define ELIB_MP_VECTOR_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct vector;
    
    template <class Vector, std::size_t Pos>
    struct vector_iterator;
    
    namespace detail
    {
      
      struct vector_intrinsics;
      struct vector_iterator_intrinsics;
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VECTOR_FWD_HPP */