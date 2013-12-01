#ifndef ELIB_MP_SET_HPP
#define ELIB_MP_SET_HPP

# include <elib/mp/set_fwd.hpp>
# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
    //-------------------------------- set tags -----------------------------// 
      
    }                                                       // namespace detail
    
    template <class ...Args>
    struct set
    {
      using type = set;
      using tag = detail::set_tag;
    };
    
    template <class T, T ...Values>
    struct set_c
    {
      using value_type = T;
      using type = set<integral_c<T, Values>...>;
      using tag = typename type::tag;
    };                                                    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SET_HPP */