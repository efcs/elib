#ifndef ELIB_CMD_OPTIONS_OPTION_SEMANTICS_HPP
#define ELIB_CMD_OPTIONS_OPTION_SEMANTICS_HPP

# include <elib/cmd_options/fwd.hpp>

namespace elib { namespace cmd_options
{
    enum class option_semantics : unsigned 
    {
        none = 0, 
        required = 1 << 0, 
        multi_token = 1 << 2, 
        composing = 1 << 3, 
        value_required = 1 << 4, 
        has_default_value = 1 << 5
    };
    
    constexpr option_semantics none = option_semantics::none;
    constexpr option_semantics required = option_semantics::required;
    constexpr option_semantics multi_value = option_semantics::multi_token;
    constexpr option_semantics composing = option_semantics::composing;
    constexpr option_semantics value_required = option_semantics::value_required;
    constexpr option_semantics has_default_value = option_semantics::has_default_value;
    
    constexpr option_semantics operator~(option_semantics s) noexcept
    {
        return static_cast<option_semantics>(
            ~ static_cast<unsigned>(s)
          );
    }
    
    constexpr option_semantics operator&(option_semantics lhs, option_semantics rhs) noexcept
    {
        return static_cast<option_semantics>(
            static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs)
          );
    }
    
    constexpr option_semantics operator|(option_semantics lhs, option_semantics rhs) noexcept
    {
        return static_cast<option_semantics>(
            static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs)
          );
    }
    
    constexpr option_semantics operator^(option_semantics lhs, option_semantics rhs) noexcept
    {
        return static_cast<option_semantics>(
            static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs)
          );
    }
    
    constexpr bool operator !(option_semantics s) noexcept
    {
        return !(static_cast<unsigned>(s));
    }
    
    constexpr bool is_set(option_semantics lhs, option_semantics rhs) noexcept
    {
        return static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs);
    }
}}                                                          // namespace elib
#endif /* ELIB_CMD_OPTIONS_OPTION_SEMANTICS_HPP */