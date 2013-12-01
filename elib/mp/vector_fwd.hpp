#ifndef ELIB_MP_CONTAINER_VECTOR_FWD_HPP
#define ELIB_MP_CONTAINER_VECTOR_FWD_HPP

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args> struct vector;
    
    namespace detail
    {
      struct vector_tag {};
      struct vector_iter_tag {};

      struct vector_front_tag {};
      struct vector_back_tag {};
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CONTAINER_VECTOR_FWD_HPP */