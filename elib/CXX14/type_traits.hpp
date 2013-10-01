#ifndef ELIB_CXX14_TYPE_TRAITS_HPP
#define ELIB_CXX14_TYPE_TRAITS_HPP

# include <elib/config.hpp>

# include <type_traits>

namespace std
{
  
  template <bool Pred, typename Ret=void>
  using enable_if_t = typename enable_if<Pred, Ret>::type;
  
  template <typename T>
  using remove_const_t = typename remove_const<T>::type; 
  
  template <typename T>
  using remove_volatile_t = typename remove_volatile<T>::type;
  
  template <typename T>
  using remove_cv_t = typename remove_cv<T>::type;
  
  template <typename T>
  using add_const_t = typename add_const<T>::type;
  
  template <typename T>
  using add_volatile_t = typename add_volatile<T>::type;
  
  template <typename T>
  using add_cv_t = typename add_cv<T>::type;
  
  
  template <typename T>
  using remove_reference_t = typename remove_reference<T>::type;
  
  template <typename T>
  using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
  
  template <typename T>
  using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
  
  
  template <typename T>
  using remove_pointer_t = typename remove_pointer<T>::type;
  
  template <typename T>
  using add_pointer_t = typename add_pointer<T>::type;
  
  
  template <typename T>
  using make_signed_t = typename make_signed<T>::type;
  
  template <typename T>
  using make_unsigned_t = typename make_unsigned<T>::type;
  
  
  template <typename T>
  using remove_extents_t = typename remove_extent<T>::type;
  
  template <typename T>
  using remove_all_extents_t = typename remove_all_extents<T>::type;
  
  
  template <typename T>
  using decay_t = typename decay<T>::type;
  
  
  template <bool Pred, typename Ret=void>
  using enable_if_t = typename enable_if<Pred, Ret>::type;
  
  
  template <bool Pred,  typename T, typename U>
  using conditional_t = typename conditional<Pred, T, U>::type;
  
  
  template <typename... Args>
  using common_type_t = typename common_type<Args...>::type;
  
  
  template <typename T>
  using underlying_type_t = typename underlying_type<T>::type;
  
  
  template <typename T>
  using result_of_t = typename result_of<T>::type;
  
  
}                                                           // namespace std 
   
#endif /* ELIB_CXX14_TYPE_TRAITS_HPP */