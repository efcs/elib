#ifndef ELIB_ENUMERATION_BASIC_ENUM_TRAITS_HPP
#define ELIB_ENUMERATION_BASIC_ENUM_TRAITS_HPP

# include <elib/config.hpp>

# include <string>
# include <map>

namespace elib 
{
  namespace enumeration
  {
    
    template <typename EnumT>
    struct basic_enum_traits
    {
      static const std::map<EnumT, std::string> name_map;
      
      typedef void m_default;
    };
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_BASIC_ENUM_TRAITS_HPP */
