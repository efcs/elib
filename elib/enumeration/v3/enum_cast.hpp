#ifndef ELIB_ENUMERATION_ENUM_CAST_HPP
# define ELIB_ENUMERATION_ENUM_CAST_HPP

# include <elib/config.hpp>

# include <elib/enumeration/v3/detail/enum_helpers.hpp>

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace enumeration
  {
    
    
    template <typename T>
    typename detail::enum_if<T>::underlying_type
    underlying_cast(T v) noexcept
    {
      return static_cast<underlying_t<T>>(v);
    }
    
    
    
    
    
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_CAST_HPP */