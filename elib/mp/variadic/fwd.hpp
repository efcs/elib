#ifndef ELIB_MP_VARIADIC_FWD_HPP
#define ELIB_MP_VARIADIC_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <std::size_t N, class Pack>
    struct get_nth;
    
    template <class Pack>
    
    template <std::size_t N, class Pack>
    struct drop;
    
    template <std::size_t N, class ...Args>
    struct take;
    
    template <std::size_t First, std::size_t Last, class ...Args>
    struct slice;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_FWD_HPP */