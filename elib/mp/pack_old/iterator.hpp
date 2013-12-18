#ifndef ELIB_MP_PACK_ITERATOR_HPP
#define ELIB_MP_PACK_ITERATOR_HPP

# include <elib/mp/pack/fwd.hpp>
# include <elib/mp/pack/pack.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class Pack, std::size_t Pos>
    struct pack_iterator;
    
    template <class ...Args, std::size_t Pos>
    struct pack_iterator<pack<Args...>, Pos>
    {
      using category = random_access_iterator_tag;
      using type = pack_iterator;
    };
    
    
    template <class Pack, std::size_t Pos>
    struct get_impl< pack_iterator<Pack, Pos> >
    {
      using type = detail::pack_iterator_intrinsics;
    };

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PACK_ITERATOR_HPP */