#ifndef ELIB_MP_IF_HPP
# define ELIB_MP_IF_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>


namespace elib 
{
  namespace mp
  {
    
    //-------------------------------- if_c --------------------------------// 
  
    template <bool B, class If, class Else>
    struct if_c 
    {
      using type = Else;
      static_assert(!B, "B must be false");
    };
    
    template <class If, class Else>
    struct if_c<true, If, Else>
    {
      using type = If;
    };
    
    template <bool P, class If, class Else>
    using if_c_t = typename if_c<P, If, Else>::type;
    
    //-------------------------------- if_ --------------------------------// 

    template <class P, class If, class Else>
    struct if_ : if_c<static_cast<bool>(P::value), If, Else>
    {};
    
    
    template <class P, class If, class Else>
    using if_t = typename if_<P, If, Else>::type;
  
    //------------------------------ eval_if --------------------------------// 
    
    template <class P, class If, class Else>
    struct eval_if
    {
      using type = typename if_c_t<static_cast<bool>(P::value), If, Else>::type;
    };
    
    
    template <class P, class If, class Else>
    using eval_if_t = typename eval_if<P, If, Else>::type;
    
    //------------------------------- eval_if_c -----------------------------// 
    
    template <bool P, class If, class Else>
    struct eval_if_c
    {
      using type = typename if_c_t<P, If, Else>::type;
    };
    

    template <bool P, class If, class Else>
    using eval_if_c_t = typename eval_if_c<P, If, Else>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_IF_HPP */