#ifndef ELIB_MP_PRINT_HPP
#define ELIB_MP_PRINT_HPP

# include <elib/mp/identity.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct print_type;
    
    
    template <class T>
    struct print : identity<T>
    {
      static constexpr auto _ = sizeof( print_type<T> );
    };
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PRINT_HPP */