#ifndef ELIB_MP_ALGORITHM_FIND_HPP
#define ELIB_MP_ALGORITHM_FIND_HPP

# include <elib/mp/algorithm/find_if.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/lambda.hpp>

namespace elib 
{
  namespace mp
  {
    template <class Seq, class T>
    struct find : find_if<Seq, same_type<T, _1>>
    {};
    
    template <class Seq, class T>
    using find_t = typename find<Seq, T>::type;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FIND_HPP */