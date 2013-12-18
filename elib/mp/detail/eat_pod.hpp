#ifndef ELIB_MP_DETAIL_EAT_POD_HPP
#define ELIB_MP_DETAIL_EAT_POD_HPP

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class=decltype(nullptr)>
      struct eat_pod
      {
        eat_pod(...);
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_EAT_POD_HPP */