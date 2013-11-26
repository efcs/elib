#ifndef ELIB_MP_DEQUE_HPP
# define ELIB_MP_DEQUE_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/vector.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    using deque = vector<Args...>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DEQUE_HPP */