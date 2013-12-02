#ifndef ELIB_MP_DISPATCH_TO_HPP
#define ELIB_MP_DISPATCH_TO_HPP

# include <elib/mp/tag_dispatch.hpp>

namespace elib 
{
  namespace mp
  {
   
   template <class T>
   struct dispatch_to : tag_dispatch<T>
   {};
   
   template <class T>
   using dispatch_to_t = typename dispatch_to<T>::type;
   
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DISPATCH_TO_HPP */