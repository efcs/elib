#ifndef ELIB_MP_ALGORITHM_COUNT_HPP
#define ELIB_MP_ALGORITHM_COUNT_HPP

# include <elib/mp/algorithm/count_if.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/same_type.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class T>
    struct count : count_if<Seq, same_type<T, _1>>
    {};
    
    template <class Seq, class T>
    using count_t = typename count_if<Seq, same_type<T, _1>>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_COUNT_HPP */