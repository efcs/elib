#ifndef ELIB_MP_CHAR_HPP
#define ELIB_MP_CHAR_HPP

# include <type_traits>

namespace elib
{
  namespace mp
  {
    
    template <char Val>
    using char_ = std::integral_constant<char, Val>;
    
    
    template <signed char Val>
    using schar_ = std::integral_constant<signed char, Val>;
    
    
    template <unsigned char Val>
    using uchar_ = std::integral_constant<unsigned char, Val>;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CHAR_HPP */