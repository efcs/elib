#ifndef ELIB_MP_IF_HPP
# define ELIB_MP_IF_HPP

# include <elib/mp/config.hpp>

# include <elib/mp/types.hpp>


namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      
      template <class P, class If, class Else, bool=static_cast<bool>(P::value)>
      struct if__
      {
        typedef Else type;
      };
      
      
      template <class P, class If, class Else>
      struct if__<P, If, Else, true>
      {
        typedef If type;
      };
      
      
    }                                                       //  namespace detail
    
    template <class P, class If, class Else>
    struct if_ : detail::if__<P, If, Else>
    {};
    
    
    template <bool P, class If, class Else>
    struct if_c : if_<bool_<P>, If, Else>
    {};
    
    
    template <class P, class If, class Else>
    struct eval_if
    {
      typedef typename if_<P, If, Else>::type::type type;
    };
    
    template <bool P, class If, class Else>
    struct eval_if_c : eval_if<bool_<P>, If, Else>
    {};
    
    
    template <class P, class If, class Else>
    using if_t = typename if_<P, If, Else>::type;
    
    template <bool P, class If, class Else>
    using if_c_t = typename if_c<P, If, Else>::type;
    
    template <class P, class If, class Else>
    using eval_if_t = typename eval_if<P, If, Else>::type;
    
    template <bool P, class If, class Else>
    using eval_if_c_t = typename eval_if_c<P, If, Else>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_IF_HPP */