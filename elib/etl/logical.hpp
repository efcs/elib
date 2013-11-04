#ifndef ELIB_ETL_LOGICAL_HPP
# define ELIB_ETL_LOGICAL_HPP

# include <elib/etl/config.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace etl
  {
    
    
    template <class T>
    struct not_ : std::integral_constant<typename T::value_type, !T::value>
    {};
    
    template <class T, class U>
    struct and_ : std::integral_constant<typename T::value_type, T::value && U::value>
    {};
    
    template <class T, class U>
    struct or_ : std::integral_constant<typename T::value_type, T::value || U::value>
    {};
    
    
  }                                                         //  namespace etl
}                                                           // namespace elib
#endif /* ELIB_ETL_LOGICAL_HPP */