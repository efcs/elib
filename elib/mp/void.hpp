#ifndef ELIB_MP_VOID_HPP
#define ELIB_MP_VOID_HPP

# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct void_ { using type = void_; };
    
    template <class T>
    using is_void = aux::is_same<T, void_>;
    
    template <class T>
    using is_void_t = typename aux::is_same<T, void_>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VOID_HPP */
