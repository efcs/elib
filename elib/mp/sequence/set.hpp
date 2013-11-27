#ifndef ELIB_MP_SEQUENCE_SET_HPP
#define ELIB_MP_SEQUENCE_SET_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
    //-------------------------------- set tags -----------------------------// 
      struct set_tag {};
      struct set_iter_tag {};
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
      using type = set<std::integral_constant<T, Values>...>;
      using tag = typename type::tag;
    };                                                    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_SET_HPP */