#ifndef ELIB_MP_TYPE_WRAPPER_HPP
#define ELIB_MP_TYPE_WRAPPER_HPP

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct type_
    {
      using type = T;
    };
    
    template <class T>
    using unwrap_t = typename T::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPE_WRAPPER_HPP */