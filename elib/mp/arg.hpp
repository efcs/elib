#ifndef ELIB_MP_ARG_HPP
#define ELIB_MP_ARG_HPP

# include <elib/mp/pack.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/detail/integral_constant.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <std::size_t N>
    struct arg
    {
      template <class ...Args>
      using apply = at_c<pack<Args...>, N - 1>;
      
      static_assert(N != 0, "0 is not a valid arg index (one indexed)");
    };

    
    template <class S> 
    struct is_placeholder : false_ {};
    
    template <std::size_t N> 
    struct is_placeholder< arg<N> > : true_ {};

    
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