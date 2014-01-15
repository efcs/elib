#ifndef ELIB_CXX14_MEMORY_HPP
#define ELIB_CXX14_MEMORY_HPP

# include <memory>
# include <type_traits>
# include <utility>

namespace std
{
 
# if __cplusplus < 201300L

  template <typename T> 
  struct _Unique_if 
  {
    typedef unique_ptr<T> _Single_object;
  };
  
  template <typename T>
  struct _Unique_if<T[]>
  {
    typedef unique_ptr<T[]> _Unknown_bound;
  };
  
  template <typename T, size_t N>
  struct _Unique_if<T[N]>
  {
    typedef void _Known_bound;
  };
  
  
  template <typename T, typename... Args>
  typename _Unique_if<T>::_Single_object
  make_unique(Args&&... args) 
  {
      return unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
  
  template <typename T>
  typename _Unique_if<T>::_Unknown_bound
  make_unique(size_t n)
  {
    typedef typename remove_extent<T>::type U;
    return unique_ptr<T>(new U[n]());
  }
  
  template <typename T, typename... Args>
  typename _Unique_if<T>::_Known_bound
  make_unique(Args&&...) = delete;
  
# endif
}                                                           // namespace std
#endif                                                 // ELIB_CXX14_MEMORY_HPP