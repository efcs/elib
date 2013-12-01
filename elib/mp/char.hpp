#ifndef ELIB_MP_CHAR_HPP
#define ELIB_MP_CHAR_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib
{
  namespace mp
  {
    
    template <char Val>
    using char_ = integral_c<char, Val>;
    
    
    template <signed char Val>
    using schar_ = integral_c<signed char, Val>;
    
    
    template <unsigned char Val>
    using uchar_ = integral_c<unsigned char, Val>;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CHAR_HPP */