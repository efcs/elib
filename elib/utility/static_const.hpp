#ifndef ELIB_UTILITY_STATIC_CONST_HPP
#define ELIB_UTILITY_STATIC_CONST_HPP

namespace elib 
{
  
  template <class T>
  struct static_const
  {
    static constexpr T value{};
  };
  
  template <class T>
  constexpr T static_const<T>::value;
  
}                                                           // namespace elib
#endif /* ELIB_UTILITY_STATIC_CONST_HPP */