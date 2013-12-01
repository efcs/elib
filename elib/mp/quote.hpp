#ifndef ELIB_MP_QUOTE_HPP
#define ELIB_MP_QUOTE_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/detail/has_type.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
     
      //-------------------------------- quote_impl -------------------------// 
      
      template <
        class F
        , class = typename has_type<F>::type
      >
      struct quote_impl
      {
        using type = F;
      };
      
      
      template <class F>
      struct quote_impl< F, true_ >
      {
        using type = typename F::type;
      };
      
    }                                                       // namespace detail
    
    //-------------------------------- quote --------------------------------// 
    template <
      template <class...> class F
    >
    struct quote
    {
      template <class ...Args>
      struct apply
      {
        using type = typename detail::quote_impl<F<Args...>>::type;
      };
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_QUOTE_HPP */