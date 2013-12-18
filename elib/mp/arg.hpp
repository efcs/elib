#ifndef ELIB_MP_ARG_HPP
#define ELIB_MP_ARG_HPP

# include <elib/mp/pack.hpp>
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
        using type = at_c_t<pack<Args...>, N>;
      };
      
      static_assert(N != 0, "0 is not a valid arg index (one indexed)");
    };
    
    
    namespace placeholders
    {
      using _1 = arg<1>;
      using _2 = arg<2>;
      using _3 = arg<3>;
      using _4 = arg<4>;
      using _5 = arg<5>;
      using _6 = arg<6>;
      using _7 = arg<7>;
      using _8 = arg<8>;
      using _9 = arg<9>;
    }                                                 // namespace placeholders
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ARG_HPP */