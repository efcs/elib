#ifndef ELIB_MP_DETAIL_INTEGRAL_CONSTANT_HPP
#define ELIB_MP_DETAIL_INTEGRAL_CONSTANT_HPP

# include <type_traits>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    using std::integral_constant;
    
    template <class T, T Val>
    using integral_c = integral_constant<T, Val>;
    
  //-------------------------------- bool --------------------------------// 
    
    template <bool V>
    using bool_ = integral_c<bool, V>;
    
    using true_ = bool_<true>;
    using false_ = bool_<false>;
    
  //-------------------------------- char --------------------------------// 
    
    template <char V>
    using char_ = integral_c<char, V>;
    
    template <signed char V>
    using schar_ = integral_c<signed char, V>;
    
    template <unsigned char V>
    using uchar_ = integral_c<unsigned char, V>;
    
  //-------------------------------- short --------------------------------// 
  
    template <short V>
    using short_ = integral_c<short, V>;
    
    template <unsigned short V>
    using ushort_ = integral_c<unsigned short, V>;
    
  //-------------------------------- int --------------------------------// 
  
    template <int V>
    using int_ = integral_c<int, V>;
    
    template <unsigned V>
    using uint_ = integral_c<unsigned, V>;
    
  //-------------------------------- long --------------------------------// 
  
    template <long V>
    using long_ = integral_c<long, V>;
    
    template <unsigned long V>
    using ulong_ = integral_c<unsigned long, V>;
    
  //-------------------------------- long long --------------------------------// 
  
    template <long long V>
    using llong_ = integral_c<long long, V>;
    
    template <unsigned long long V>
    using ullong_ = integral_c<unsigned long long, V>;
    
  //-------------------------------- size_type --------------------------------// 
  
    template <std::size_t V>
    using size_t_ = integral_c<std::size_t, V>;
    
    template <std::size_t V>
    using size_type = integral_c<std::size_t, V>;
    
    
  //-------------------------------- integral_cast --------------------------// 
  
    template <class IntC, class T>
    using integral_cast = integral_constant<T, static_cast<T>(IntC::type::value)>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_INTEGRAL_CONSTANT_HPP */