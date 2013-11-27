#ifndef ELIB_MP_DEQUE_FWD_HPP
#define ELIB_MP_DEQUE_FWD_HPP

# include <elib/mp/vector_fwd.hpp>

namespace elib 
{
  namespace mp
  {
    template <class ...Args>
    using deque = vector<Args...>;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DEQUE_FWD_HPP */