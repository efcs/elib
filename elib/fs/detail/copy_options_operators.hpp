#ifndef ELIB_FS_COPY_OPTIONS_OPERATORS_HPP
#define ELIB_FS_COPY_OPTIONS_OPERATORS_HPP

// definition for copy_options must already be available
# include <elib/pragma.hpp>
#include <type_traits>


namespace elib
{
  namespace fs
  {
    namespace cp_detail
    {
      
      typedef typename std::underlying_type<copy_options>::type base_t;
      
      // upcast: base_t -> copy_options
      constexpr copy_options uc(base_t src) noexcept
      { return static_cast<copy_options>(src); }
      
      // downcast: copy_options -> base_t
      constexpr base_t dc(copy_options p) noexcept
      { return static_cast<base_t>(p); }
      
      //bool cast
      constexpr bool bc(copy_options p) noexcept
      { return static_cast<bool>(p); }
      
    }                                                    // namespace cp_detail
        
    // pure operators (lhs & rhs) == copy_options
    constexpr copy_options operator~(copy_options lhs) noexcept
    { return cp_detail::uc(~ cp_detail::dc(lhs)); }
      
    constexpr copy_options operator&(copy_options lhs, copy_options rhs) noexcept
    { return cp_detail::uc(cp_detail::dc(lhs) & cp_detail::dc(rhs)); }
      
    constexpr copy_options operator|(copy_options lhs, copy_options rhs) noexcept
    { return cp_detail::uc(cp_detail::dc(lhs) | cp_detail::dc(rhs)); }
      
    constexpr copy_options operator^(copy_options lhs, copy_options rhs) noexcept
    { return cp_detail::uc(cp_detail::dc(lhs) ^ cp_detail::dc(rhs)); }
      
    inline copy_options& operator&=(copy_options& lhs, copy_options rhs) noexcept
    { return lhs = lhs & rhs; }
      
    inline copy_options& operator|=(copy_options& lhs, copy_options rhs) noexcept
    { return lhs = lhs | rhs; }
      
    inline copy_options& operator^=(copy_options& lhs, copy_options rhs) noexcept
    { return lhs = lhs ^ rhs; }
      
    //mixed operators
    constexpr copy_options operator&(copy_options lhs, cp_detail::base_t rhs) noexcept
    { return cp_detail::uc(cp_detail::dc(lhs) & rhs); }
      
    constexpr copy_options operator|(copy_options lhs, cp_detail::base_t rhs) noexcept
    { return cp_detail::uc(cp_detail::dc(lhs) | rhs); }
      
    constexpr copy_options operator^(copy_options lhs, cp_detail::base_t rhs) noexcept
    { return cp_detail::uc(cp_detail::dc(lhs) ^ rhs); }
      
      
    inline copy_options& operator&=(copy_options& lhs, cp_detail::base_t rhs) noexcept
    { return lhs = lhs & rhs; }
      
    inline copy_options& operator|=(copy_options& lhs, cp_detail::base_t rhs) noexcept
    { return lhs = lhs | rhs; }
      
    inline copy_options& operator^=(copy_options& lhs, cp_detail::base_t rhs) noexcept
    { return lhs = lhs ^ rhs; }
    
    
    ////////////////////////////////////////////////////////////////////////////////
    //            LOGICAL OPERATORS                               
    ////////////////////////////////////////////////////////////////////////////////
    
/* suppress warning about always evaluating both sides */
ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_EFFCXX()

    constexpr bool operator!(copy_options lhs) noexcept
    { return ! cp_detail::bc(lhs); }
    
    constexpr bool operator&&(copy_options lhs, copy_options rhs) noexcept
    { return cp_detail::bc(lhs) && cp_detail::bc(rhs); }
    
    constexpr bool operator||(copy_options lhs, copy_options rhs) noexcept
    { return cp_detail::bc(lhs) || cp_detail::bc(rhs); }
    
    constexpr bool operator&&(copy_options lhs, bool rhs) noexcept
    { return cp_detail::bc(lhs) && rhs; }
    
    constexpr bool operator||(copy_options lhs, bool rhs) noexcept
    { return cp_detail::bc(lhs) || rhs; }

    
ELIB_PRAGMA_DIAG_POP()

    
  } // namespace fs
} // namespace elib 
        
        
#endif /* ELIB_FS_COPY_OPTIONS_OPERATORS_HPP */