#ifndef ELIB_MP_DETAIL_CONDITIONAL_HPP
#define ELIB_MP_DETAIL_CONDITIONAL_HPP

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <bool B, class Then, class Else>
      struct conditional;
      
      template <class Then, class Else>
      struct conditional<true, Then, Else> 
      {
        using type = Then;
      };
      
      template <class Then, class Else>
      struct conditional<false, Then, Else>
      {
        using type = Else;
      };
      
      template <bool B, class T, class E>
      using conditional_t = typename conditional<B, T, E>::type;
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_CONDITIONAL_HPP */