#ifndef ELIB_MP_ALGORITHM_DETAIL_SELECT_FOLDL_OVERLOAD_HPP
#define ELIB_MP_ALGORITHM_DETAIL_SELECT_FOLDL_OVERLOAD_HPP

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <bool IsVariadic, bool HasO1Size>
      struct select_foldl_overload_impl;
      
      template <bool HasO1Size>
      struct select_foldl_overload_impl<true, HasO1Size>
      {
        template <class Var, class >
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_SELECT_FOLDL_OVERLOAD_HPP */
