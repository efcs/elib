#ifndef ELIB_MP_ITERATOR_DISTANCE_HPP
#define ELIB_MP_ITERATOR_DISTANCE_HPP

# include <elib/mp/iterator/iterator_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {

      //TODO
      template <class Tag>
      struct distance_impl
      {
        template <class First, class Last>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_DISTANCE_HPP */