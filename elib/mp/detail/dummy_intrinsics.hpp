#ifndef ELIB_MP_DETAIL_DUMMY_INTRINSICS_HPP
#define ELIB_MP_DETAIL_DUMMY_INTRINSICS_HPP

# include <elib/mp/detail/nil.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      struct dummy_intrinsics
      {
        template <class> struct iterator_category;
        template <class> struct deref;
        template <class> struct 
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_DUMMY_INTRINSICS_HPP */