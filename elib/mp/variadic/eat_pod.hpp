#ifndef ELIB_MP_VARIADIC_EAT_POD_HPP
#define ELIB_MP_VARIADIC_EAT_POD_HPP

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class>
      struct eat_pod
      {
        eat_pod(...);
      };
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_EAT_POD_HPP */