#ifndef ELIB_FS_PERMS_OPERATORS_HPP
#define ELIB_FS_PERMS_OPERATORS_HPP

// definition for perms must already be available

#include <type_traits>


namespace elib
{
  namespace fs
  {
    namespace perms_detail
    {
      
      typedef typename std::underlying_type<perms>::type base_t;
      
      // upcast: base_t -> perms
      constexpr perms uc(base_t src) noexcept
      { return static_cast<perms>(src); }
      
      // downcast: perms -> base_t
      constexpr base_t dc(perms p) noexcept
      { return static_cast<base_t>(p); }
      
      
      namespace operators
      {
        
      // pure operators (lhs & rhs) == perms
        constexpr perms operator~(perms lhs) noexcept
        { return uc(~ dc(lhs)); }
      
        constexpr perms operator&(perms lhs, perms rhs) noexcept
        { return uc(dc(lhs) & dc(rhs)); }
        
        constexpr perms operator|(perms lhs, perms rhs) noexcept
        { return uc(dc(lhs) | dc(rhs)); }
        
        constexpr perms operator^(perms lhs, perms rhs) noexcept
        { return uc(dc(lhs) ^ dc(rhs)); }
        
        inline perms& operator&=(perms& lhs, perms rhs) noexcept
        { return lhs = lhs & rhs; }
        
        inline perms& operator|=(perms& lhs, perms rhs) noexcept
        { return lhs = lhs | rhs; }
        
        inline perms& operator^=(perms& lhs, perms rhs) noexcept
        { return lhs = lhs ^ rhs; }
        
      //mixed operators
        constexpr perms operator&(base_t lhs, perms rhs) noexcept
        { return uc(lhs & dc(rhs)); }
    
        constexpr perms operator|(base_t lhs, perms rhs) noexcept
        { return uc(lhs | dc(rhs)); }
    
        constexpr perms operator^(base_t lhs, perms rhs) noexcept
        { return uc(lhs ^ dc(rhs)); }
    
    
        constexpr perms operator&(perms lhs, base_t rhs) noexcept
        { return uc(dc(lhs) & rhs); }
    
        constexpr perms operator|(perms lhs, base_t rhs) noexcept
        { return uc(dc(lhs) | rhs); }
    
        constexpr perms operator^(perms lhs, base_t rhs) noexcept
        { return uc(dc(lhs) ^ rhs); }
        
        
        inline perms& operator&=(perms& lhs, base_t rhs) noexcept
        { return lhs = lhs & rhs; }
        
        inline perms& operator|=(perms& lhs, base_t rhs) noexcept
        { return lhs = lhs | rhs; }
        
        inline perms& operator^=(perms& lhs, base_t rhs) noexcept
        { return lhs = lhs ^ rhs; }
      
      
      } // namespace operators
    } // namespace perms_detail
  } // namespace fs
} // namespace elib 


// insert intro global namespace 
using namespace elib::fs::perms_detail::operators;

#endif /* ELIB_FS_PERMS_OPERATORS_HPP */