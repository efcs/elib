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
    typedef unique_ptr<T> _single_object;
  };
  
  template <typename T>
  struct _unique_if<T[]>
  {
    typedef unique_ptr<T[]> _unknown_bound;
  };
  
  template <typename T, size_t N>
  struct _unique_if<T[N]>
  {
    typedef void _known_bound;
  };
  
  
  template <typename T, typename... Args>
  typename _unique_if<T>::_single_object
  make_unique(Args&&... args) 
  {
      return unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
  
  template <typename T>
  typename _unique_if<T>::_unknown_bound
  make_unique(size_t n)
  {
    typedef typename remove_extent<T>::type U;
    return unique_ptr<T>(new U[n]());
  }
  
  template <typename T, typename... Args>
  typename _unique_if<T>::_known_bound
  make_unique(Args&&...) = delete;
  
# endif
}                                                           // namespace std
#endif                                                 // ELIB_CXX14_MEMORY_HPP