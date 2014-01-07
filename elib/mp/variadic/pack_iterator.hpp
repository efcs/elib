#ifndef ELIB_MP_VARIADIC_PACK_ITERATOR_HPP
#define ELIB_MP_VARIADIC_PACK_ITERATOR_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/iterator/default_random_access_iterator.hpp>
# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, std::size_t N>
    using variadic_pack_iterator = default_random_access_iterator<Seq, N>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_PACK_ITERATOR_HPP */