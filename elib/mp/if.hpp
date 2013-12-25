#ifndef ELIB_MP_IF_HPP
#define ELIB_MP_IF_HPP

# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/identity.hpp>

namespace elib 
{
  namespace mp
  {

  //-------------------------------- if_c --------------------------------// 
    
    template <bool Pred, class Then, class Else>
    struct if_c;
    
    template <class Then, class Else>
    struct if_c<true, Then, Else> : identity<Then>
    {};
    
    template <class Then, class Else>
    struct if_c<false, Then, Else> : identity<Else>
    {};
    
    template <bool P, class T, class E>
    using if_c_t = typename if_c<P, T, E>::type;
    
  //-------------------------------- if_ --------------------------------// 
  
    template <class P, class Then, class Else>
    struct if_ : if_c<static_cast<bool>(P::type::value), Then, Else>
    {};
    
    
    template <class P, class Then, class Else>
    using if_t = if_c_t<static_cast<bool>(P::type::value), Then, Else>;
  
  
  //-------------------------------- eval_if_ ------------------------------// 
  
    template <class P, class Then, class Else>
    struct eval_if_ : identity< typename if_t<P, Then, Else>::type >
    {};
    
    
    template <class P, class Then, class Else>
    using eval_if_t = typename if_t<P, Then, Else>::type;
    
  //-------------------------------- eval_if_c --------------------------------// 
  
    template <bool P, class Then, class Else>
    struct eval_if_c : identity< typename if_c_t<P, Then, Else>::type >
    {};
    
    
    template <bool P, class Then, class Else>
    using eval_if_c_t = typename if_c_t<P, Then, Else>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_IF_HPP */