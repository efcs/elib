#ifndef ELIB_MP_VARIADIC_ITERATOR_HPP
# define ELIB_MP_VARIADIC_ITERATOR_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/iterator.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, std::size_t N>
    struct variadic_iterator
    {
      using type = variadic_iterator;
      using category = random_access_iterator_tag;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_ITERATOR_HPP */