#ifndef ELIB_ARGP_OPTION_SEMANTICS_HPP
#define ELIB_ARGP_OPTION_SEMANTICS_HPP

# include <elib/argp/fwd.hpp>

namespace elib { namespace argp
{
    enum class option_semantics 
    {
        none = 0, 
        required = 1 << 0, 
        composing = 1 << 2, 
        optional_value = 1 << 3, 
        required_value = 1 << 4, 
        multi_value = 1 << 5, 
        
    };
    
    constexpr option_semantics none = option_semantics::none;
    constexpr option_semantics required = option_semantics::required;
    constexpr option_semantics composing = option_semantics::composing;
    constexpr option_semantics optional_value = option_semantics::optional_value;
    constexpr option_semantics required_value = option_semantics::required_value;
    constexpr option_semantics multi_value = option_semantics::multi_value;
    
    
    bool validate_option_semantics(option_semantics);
    
    constexpr option_semantics operator~(option_semantics s) noexcept
    {
        return static_cast<option_semantics>(
            ~ static_cast<int>(s)
          );
    }
    
    constexpr option_semantics operator&(option_semantics lhs, option_semantics rhs) noexcept
    {
        return static_cast<option_semantics>(
            static_cast<int>(lhs) & static_cast<int>(rhs)
          );
    }
    
    constexpr option_semantics operator|(option_semantics lhs, option_semantics rhs) noexcept
    {
        return static_cast<option_semantics>(
            static_cast<int>(lhs) | static_cast<int>(rhs)
          );
    }
    
    constexpr option_semantics operator^(option_semantics lhs, option_semantics rhs) noexcept
    {
        return static_cast<option_semantics>(
            static_cast<int>(lhs) ^ static_cast<int>(rhs)
          );
    }
    
    constexpr bool operator !(option_semantics s) noexcept
    {
        return !(static_cast<int>(s));
    }
    
    constexpr bool is_set(option_semantics lhs, option_semantics rhs) noexcept
    {
        return static_cast<int>(lhs) & static_cast<int>(rhs);
    }
}}                                                          // namespace elib
#endif /* ELIB_ARGP_OPTION_SEMANTICS_HPP */