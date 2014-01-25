#ifndef ELIB_CXX14_MEMORY_HPP
#define ELIB_CXX14_MEMORY_HPP

# include <memory>
# include <type_traits>
# include <utility>

namespace std
{
# if __cplusplus < 201300L

  template <typename T> 
  struct _unique_if 
  {
    using single_object = unique_ptr<T>;
  };
  
  template <typename T>
  struct _unique_if<T[]>
  {
    using unknown_bound = unique_ptr<T[]>;
  };
  
  template <typename T, size_t N>
  struct _unique_if<T[N]>
  {
    using known_bound = void;
  };
  
  
  template <typename T, typename... Args>
  typename _unique_if<T>::single_object
  make_unique(Args&&... args) 
  {
      return unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
  
  template <typename T>
  typename _unique_if<T>::unknown_bound
  make_unique(size_t n)
  {
    using U = typename remove_extent<T>::type;
    return unique_ptr<T>(new U[n]());
  }
  
  template <typename T, typename... Args>
  typename _unique_if<T>::known_bound
  make_unique(Args&&...) = delete;
  
# endif
}                                                           // namespace std
#endif                                                 // ELIB_CXX14_MEMORY_HPP