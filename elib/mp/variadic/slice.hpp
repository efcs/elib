#ifndef ELIB_MP_VARIADIC_SLICE_HPP
# define ELIB_MP_VARIADIC_SLICE_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/drop.hpp>
# include <elib/mp/variadic/take.hpp>


namespace elib 
{
  namespace mp
  {
    
    template <
        class Seq
      , std::size_t First
      , std::size_t Last
      >
    struct variadic_slice
    {
      using type = typename
        variadic_take<
            typename variadic_drop<Seq, First>::type
          , Last - First
          >
        ::type;
    };
    
    
    template <
        class Seq
      , std::size_t First
      , std::size_t Last
      >
    using variadic_slice_t = 
      variadic_take_t<
          variadic_drop_t<Seq, First>
        , Last - First
        >;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_SLICE_HPP */