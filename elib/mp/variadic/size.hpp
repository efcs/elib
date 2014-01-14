#ifndef ELIB_MP_VARIADIC_SIZE_HPP
#define ELIB_MP_VARIADIC_SIZE_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/integral_constant.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    template <class Seq>
    struct variadic_size;
    
    template <class Seq>
    using variadic_size_t = typename variadic_size<Seq>::type;
    
    
    template <
        template <class...> class Seq
      , class ...As
    >
    struct variadic_size< Seq<As...> >
      : size_type< sizeof...(As) >
    {};
    
    
    template <class Seq, class ...As>
    struct variadic_size< Seq(As...) >
      : size_type< sizeof...(As) >
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_SIZE_HPP */