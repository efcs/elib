#ifndef ELIB_FS_COPY_OPTIONS_OPERATORS_HPP
#define ELIB_FS_COPY_OPTIONS_OPERATORS_HPP

// definition for copy_options must already be available

#include <type_traits>


namespace elib
{
  namespace fs
  {
    namespace copy_options_detail
    {
      
      typedef typename std::underlying_type<copy_options>::type base_t;
      
      // upcast: base_t -> copy_options
      constexpr copy_options uc(base_t src) noexcept
      { return static_cast<copy_options>(src); }
      
      // downcast: copy_options -> base_t
      constexpr base_t dc(copy_options p) noexcept
      { return static_cast<base_t>(p); }
      
      
      namespace operators
      {
        
        // pure operators (lhs & rhs) == copy_options
        constexpr copy_options operator~(copy_options lhs) noexcept
        { return uc(~ dc(lhs)); }
          
        constexpr copy_options operator&(copy_options lhs, copy_options rhs) noexcept
        { return uc(dc(lhs) & dc(rhs)); }
          
        constexpr copy_options operator|(copy_options lhs, copy_options rhs) noexcept
        { return uc(dc(lhs) | dc(rhs)); }
          
        constexpr copy_options operator^(copy_options lhs, copy_options rhs) noexcept
        { return uc(dc(lhs) ^ dc(rhs)); }
          
        inline copy_options& operator&=(copy_options& lhs, copy_options rhs) noexcept
        { return lhs = lhs & rhs; }
          
        inline copy_options& operator|=(copy_options& lhs, copy_options rhs) noexcept
        { return lhs = lhs | rhs; }
          
        inline copy_options& operator^=(copy_options& lhs, copy_options rhs) noexcept
        { return lhs = lhs ^ rhs; }
          
        //mixed operators
        constexpr copy_options operator&(base_t lhs, copy_options rhs) noexcept
        { return uc(lhs & dc(rhs)); }
          
        constexpr copy_options operator|(base_t lhs, copy_options rhs) noexcept
        { return uc(lhs | dc(rhs)); }
          
        constexpr copy_options operator^(base_t lhs, copy_options rhs) noexcept
        { return uc(lhs ^ dc(rhs)); }
          
          
        constexpr copy_options operator&(copy_options lhs, base_t rhs) noexcept
        { return uc(dc(lhs) & rhs); }
          
        constexpr copy_options operator|(copy_options lhs, base_t rhs) noexcept
        { return uc(dc(lhs) | rhs); }
          
        constexpr copy_options operator^(copy_options lhs, base_t rhs) noexcept
        { return uc(dc(lhs) ^ rhs); }
          
          
        inline copy_options& operator&=(copy_options& lhs, base_t rhs) noexcept
        { return lhs = lhs & rhs; }
          
        inline copy_options& operator|=(copy_options& lhs, base_t rhs) noexcept
        { return lhs = lhs | rhs; }
          
        inline copy_options& operator^=(copy_options& lhs, base_t rhs) noexcept
        { return lhs = lhs ^ rhs; }
          
          
      } // namespace operators
    } // namespace copy_options_detail
  } // namespace fs
} // namespace elib 
        
        
// insert intro global namespace 
using namespace elib::fs::copy_options_detail::operators;
        
#endif /* ELIB_FS_COPY_OPTIONS_OPERATORS_HPP */