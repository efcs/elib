#ifndef ELIB_MP_VOID_HPP
#define ELIB_MP_VOID_HPP

# include <elib/mp/integral_constant.hpp>
# include <elib/mp/same_type.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct void_ { using type = void_; };
    
    template <class T>
    using is_void = same_type<T, void_>;
    
    template <class T>
    using is_void_t = typename same_type<T, void_>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VOID_HPP */
