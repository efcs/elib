#ifndef ELIB_FS_PERMS_OPERATORS_HPP
#define ELIB_FS_PERMS_OPERATORS_HPP

// definition for perms must already be available
# include <elib/pragma.hpp>

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
      
      // boolean cast
      constexpr bool bc(perms p) noexcept
      { return static_cast<bool>(p); }
      
    } // namespace perms_detail
    
    ////////////////////////////////////////////////////////////////////////////////
    //         BITWISE OPERATORS                       
    ////////////////////////////////////////////////////////////////////////////////
    // pure operators (lhs & rhs) == perms
    constexpr perms operator~(perms lhs) noexcept
    { return perms_detail::uc(~ perms_detail::dc(lhs)); }
    
    constexpr perms operator&(perms lhs, perms rhs) noexcept
    { return perms_detail::uc(perms_detail::dc(lhs) & perms_detail::dc(rhs)); }
    
    constexpr perms operator|(perms lhs, perms rhs) noexcept
    { return perms_detail::uc(perms_detail::dc(lhs) | perms_detail::dc(rhs)); }
    
    constexpr perms operator^(perms lhs, perms rhs) noexcept
    { return perms_detail::uc(perms_detail::dc(lhs) ^ perms_detail::dc(rhs)); }
    
    inline perms& operator&=(perms& lhs, perms rhs) noexcept
    { return lhs = lhs & rhs; }
    
    inline perms& operator|=(perms& lhs, perms rhs) noexcept
    { return lhs = lhs | rhs; }
    
    inline perms& operator^=(perms& lhs, perms rhs) noexcept
    { return lhs = lhs ^ rhs; }
    
    //mixed operators
    
    
    constexpr perms operator&(perms lhs, perms_detail::base_t rhs) noexcept
    { return perms_detail::uc(perms_detail::dc(lhs) & rhs); }
    
    constexpr perms operator|(perms lhs, perms_detail::base_t rhs) noexcept
    { return perms_detail::uc(perms_detail::dc(lhs) | rhs); }
    
    constexpr perms operator^(perms lhs, perms_detail::base_t rhs) noexcept
    { return perms_detail::uc(perms_detail::dc(lhs) ^ rhs); }
    
    inline perms& operator&=(perms& lhs, perms_detail::base_t rhs) noexcept
    { return lhs = lhs & rhs; }
    
    inline perms& operator|=(perms& lhs, perms_detail::base_t rhs) noexcept
    { return lhs = lhs | rhs; }
    
    inline perms& operator^=(perms& lhs, perms_detail::base_t rhs) noexcept
    { return lhs = lhs ^ rhs; }
    
    ////////////////////////////////////////////////////////////////////////////////
    //        LOGICAL OPERATORS                   
    ////////////////////////////////////////////////////////////////////////////////
    
/* suppress warning about always evaluating both sides */
ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_EFFCXX()
    
    constexpr bool operator!(perms lhs) noexcept
    { return ! perms_detail::bc(lhs); }
    
    constexpr bool operator&&(perms lhs, perms rhs) noexcept
    { return perms_detail::bc(lhs) && perms_detail::bc(rhs); }
    
    constexpr bool operator||(perms lhs, perms rhs) noexcept
    { return perms_detail::bc(lhs) || perms_detail::bc(rhs); }
    
    constexpr bool operator&&(perms lhs, bool rhs) noexcept
    { return perms_detail::bc(lhs) && rhs; }
    
    constexpr bool operator||(perms lhs, bool rhs) noexcept
    { return perms_detail::bc(lhs) || rhs; }
    
ELIB_PRAGMA_DIAG_POP()
    
  } // namespace fs
} // namespace elib 

#endif /* ELIB_FS_PERMS_OPERATORS_HPP */
