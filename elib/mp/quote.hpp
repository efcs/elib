#ifndef ELIB_MP_QUOTE_HPP
# define ELIB_MP_QUOTE_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>
# include <elib/mp/detail/has_type.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
     
      //-------------------------------- quote_impl --------------------------------// 
      
      template <class F, class = typename has_type<F>::type>
      struct quote_impl
      {
        typedef F type;
      };
      
      
      template <class F>
      struct quote_impl<F, true_>
      {
        typedef typename F::type type;
      };
      
      
    }                                                       // namespace detail
    
    
    //-------------------------------- quote --------------------------------// 
    
    template <template <class...> class F>
    struct quote
    {
      template <class ...Args>
      struct apply
      {
        typedef typename detail::quote_impl<F<Args...>>::type type;
      };
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_QUOTE_HPP */