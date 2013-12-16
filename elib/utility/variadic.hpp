#ifndef ELIB_UTILITY_VARIADIC_HPP
#define ELIB_UTILITY_VARIADIC_HPP

# include <type_traits>
# include <cstddef>

namespace elib 
{
  
  // fwd
  template <class...> struct parameter_pack;
  
  // detail fwd
  namespace variadic_detail
  {
    
    template <std::size_t N, class ...> type_at;
    template <std::size_t N, class ...> 
    
  }  
  
  
  template <class ...Args>
  struct parameter_pack
  {
    using type = parameter_pack;
    static constexpr std::size_t size = sizeof...(Args);
  };
  
  
  template <class T>
  struct is_parameter_pack 
    : std::false_type
  {};
  
  
  template <class ...Args>
  struct is_parameter_pack< parameter_pack<Args...> >
    : std::true_type
  {};
  
  
  template <class T>
  struct make_parameter_pack;
  
  
  template <template <class...Args> class T, class ...Args>
  struct make_parameter_pack< T<Args...> >
  {
    using type = parameter_pack<Args...>;
  };
  
  
  template <class T>
  using make_parameter_pack_t = typename make_parameter_pack<T>::type;
  
  
  
                                                 // namespace variadic_detail
  
}                                                           // namespace elib
#endif /* ELIB_UTILITY_VARIADIC_HPP */