#ifndef ELIB_MP_METAFUNCTION_SIZEOF_HPP
#define ELIB_MP_METAFUNCTION_SIZEOF_HPP

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct sizeof_ 
      : std::integral_constant<
          decltype(sizeof(T))
          , sizeof(T) 
        >
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_SIZEOF_HPP */