#ifndef ELIB_MP_ARG_HPP
#define ELIB_MP_ARG_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/get_arg.hpp>

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    /* arg is one indexed, get_arg is zero indexed
     * so we have to account for the OBOB */
    template <std::size_t N>
    struct arg
    {
      template <class ...Args>
      struct apply
      {
        typedef get_arg_t<N-1, Args...> type;
        
      };
      static_assert(N != 0, "0 is not a valid arg index (one indexed)");
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ARG_HPP */