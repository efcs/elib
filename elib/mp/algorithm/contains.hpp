#ifndef ELIB_MP_ALGORITHM_CONTAINS_HPP
#define ELIB_MP_ALGORITHM_CONTAINS_HPP

# include <elib/mp/algorithm/count.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class T>
    struct contains : bool_< count_t<Seq, T>::value != 0 >
    {};
    
    template <class Seq, class T>
    using contains_t = bool_< count_t<Seq, T>::value != 0 >;
    
  }
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_CONTAINS_HPP */