#ifndef ELIB_SIZE_TYPE_HPP
#define ELIB_SIZE_TYPE_HPP

#include <cstddef>

namespace elib 
{
      
  template <typename T, T NPOS = static_cast<T>(-1)>
  struct size_type_traits {
      typedef T type;
      typedef T size_type;
      static constexpr size_type npos = NPOS;
  };

  using elib_size_type = size_type_traits<std::size_t>;

  using elib_size_t = typename elib_size_type::size_type; 
        
}                                                            // namespace elib
#endif /* ELIB_SIZE_TYPE_HPP */