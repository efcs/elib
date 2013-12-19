#ifndef ELIB_MP_DETAIL_INTEGRAL_CONSTANT_HPP
#define ELIB_MP_DETAIL_INTEGRAL_CONSTANT_HPP

# include <type_traits>
# include <cstddef>

# define ELIB_MP_AUTO_INTC(...) \
    ::elib::mp::integral_constant<decltype(__VA_ARGS__), __VA_ARGS__>

namespace elib 
{
  namespace mp
  {
    
    using std::integral_constant;
    
  //-------------------------------- bool --------------------------------// 
    
    template <bool V>
    using bool_ = integral_constant<bool, V>;
    
    using true_ = bool_<true>;
    using false_ = bool_<false>;
    
  //-------------------------------- char --------------------------------// 
    
    template <char V>
    using char_ = integral_constant<char, V>;
    
    template <signed char V>
    using schar_ = integral_constant<signed char, V>;
    
    template <unsigned char V>
    using uchar_ = integral_constant<unsigned char, V>;
    
  //-------------------------------- short --------------------------------// 
  
    template <short V>
    using short_ = integral_constant<short, V>;
    
    template <unsigned short V>
    using ushort_ = integral_constant<unsigned short, V>;
    
  //-------------------------------- int --------------------------------// 
  
    template <int V>
    using int_ = integral_constant<int, V>;
    
    template <unsigned V>
    using uint_ = integral_constant<unsigned, V>;
    
  //-------------------------------- long --------------------------------// 
  
    template <long V>
    using long_ = integral_constant<long, V>;
    
    template <unsigned long V>
    using ulong_ = integral_constant<unsigned long, V>;
    
  //-------------------------------- long long --------------------------------// 
  
    template <long long V>
    using llong_ = integral_constant<long long, V>;
    
    template <unsigned long long V>
    using ullong_ = integral_constant<unsigned long long, V>;
    
  //-------------------------------- size_type --------------------------------// 
    
    template <std::size_t V>
    using size_type = integral_constant<std::size_t, V>;
    
    
  //-------------------------------- integral_cast --------------------------// 
  
    template <class IntC, class T>
    using integral_cast = integral_constant<T, static_cast<T>(IntC::type::value)>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_INTEGRAL_CONSTANT_HPP */