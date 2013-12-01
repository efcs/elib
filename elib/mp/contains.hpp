#ifndef ELIB_MP_CONTAINS_HPP
#define ELIB_MP_CONTAINS_HPP

# include <elib/mp/algorithm_fwd.hpp>

namespace elib
{
  namespace mp
  {

    //TODO
    template <class Seq, class T>
    struct contains;
    
    template <class Seq, class T>
    using contains_t = typename contains<Seq, T>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CONTAINS_HPP */
