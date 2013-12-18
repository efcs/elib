#ifndef ELIB_MP_ALWAYS_HPP
#define ELIB_MP_ALWAYS_HPP

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct always
    {
      template <class ...>
      struct apply
      {
        using type = T;
      };
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALWAYS_HPP */