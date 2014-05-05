#ifndef ELIB_FILESYSTEM_COPY_OPTIONS_OPERATORS_HPP
#define ELIB_FILESYSTEM_COPY_OPTIONS_OPERATORS_HPP

# include <elib/aux.hpp>

namespace elib { namespace fs
{
        
////////////////////////////////////////////////////////////////////////////////
//         BITWISE OPERATORS
////////////////////////////////////////////////////////////////////////////////
    
# define ELIB_FILESYSTEM_COPY_OPTIONS_BITWISE_OP(Op)                                                      \
    constexpr copy_options operator Op (copy_options lhs, copy_options rhs) noexcept                            \
    {                                                                                      \
        using UnderT = aux::underlying_type_t<copy_options>;                                      \
        return static_cast<copy_options>(                                                         \
            static_cast<UnderT>(lhs) Op static_cast<UnderT>(rhs)                           \
        );                                                                                 \
    }                                                                                      \
                                                                                           \
    constexpr copy_options operator Op( copy_options lhs, aux::underlying_type_t<copy_options> rhs) noexcept    \
    {                                                                                      \
        using UnderT = aux::underlying_type_t<copy_options>;                                      \
        return static_cast<copy_options>(                                                         \
                static_cast<UnderT>(lhs) Op rhs                                            \
            );                                                                             \
    }                                                                                      \
                                                                                           \
    inline copy_options& operator Op##= (copy_options & lhs, copy_options rhs) noexcept                         \
    {                                                                                      \
        using UnderT = aux::underlying_type_t<copy_options>;                                      \
        return reinterpret_cast<copy_options &>(                                                  \
            reinterpret_cast<UnderT &>(lhs) Op##= static_cast<UnderT>(rhs)                 \
          );                                                                               \
    }                                                                                      \
                                                                                           \
    inline copy_options& operator Op##= (copy_options & lhs, aux::underlying_type_t<copy_options> rhs) noexcept \
    {                                                                                      \
        using UnderT = aux::underlying_type_t<copy_options>;                                      \
        return reinterpret_cast<copy_options &>(                                                  \
            reinterpret_cast<UnderT &>(lhs) Op##= rhs                                      \
          );                                                                               \
    }
# 
                
    // pure operators (lhs & rhs) == copy_options
    constexpr copy_options operator~(copy_options lhs) noexcept
    {
        using UnderT = aux::underlying_type_t<copy_options>;
        return static_cast<copy_options>( 
            ~ static_cast<UnderT>(lhs) 
          ); 
    }
    
    ELIB_FILESYSTEM_COPY_OPTIONS_BITWISE_OP(&)
    ELIB_FILESYSTEM_COPY_OPTIONS_BITWISE_OP(|)
    ELIB_FILESYSTEM_COPY_OPTIONS_BITWISE_OP(^)
    
# undef ELIB_FILESYSTEM_COPY_OPTIONS_BITWISE_OP
    
////////////////////////////////////////////////////////////////////////////////
//        LOGICAL OPERATORS                   
////////////////////////////////////////////////////////////////////////////////

    constexpr bool operator!(copy_options lhs) noexcept
    { 
        using UnderT = aux::underlying_type_t<copy_options>;
        return ! static_cast<UnderT>(lhs);
    }
    
    constexpr bool operator&&(copy_options lhs, copy_options rhs) noexcept
    {
        using UnderT = aux::underlying_type_t<copy_options>;
        return ( static_cast<UnderT>(lhs) && static_cast<UnderT>(rhs) );
    }
    
    constexpr bool operator&&(copy_options lhs, bool rhs) noexcept
    {
        using UnderT = aux::underlying_type_t<copy_options>;
        return ( static_cast<UnderT>(lhs) && rhs );
    }
    
    constexpr bool operator||(copy_options lhs, copy_options rhs) noexcept
    {
        using UnderT = aux::underlying_type_t<copy_options>;
        return ( static_cast<UnderT>(lhs) || static_cast<UnderT>(rhs) );
    }
    
    constexpr bool operator||(copy_options lhs, bool rhs) noexcept
    {
        using UnderT = aux::underlying_type_t<copy_options>;
        return ( static_cast<UnderT>(lhs) || rhs );
    }
    
}}                                                          // namespace elib
#endif /* ELIB_FILESYSTEM_COPY_OPTIONS_OPERATORS_HPP */