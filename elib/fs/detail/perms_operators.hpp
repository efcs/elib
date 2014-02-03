#ifndef ELIB_FS_PERMS_OPERATORS_HPP
#define ELIB_FS_PERMS_OPERATORS_HPP

# include <elib/aux.hpp>

namespace elib { namespace fs
{
        
////////////////////////////////////////////////////////////////////////////////
//         BITWISE OPERATORS
////////////////////////////////////////////////////////////////////////////////
    
# define ELIB_FS_PERMS_BITWISE_OP(Op)                                                      \
    constexpr perms operator Op (perms lhs, perms rhs) noexcept                            \
    {                                                                                      \
        using UnderT = aux::underlying_type_t<perms>;                                      \
        return static_cast<perms>(                                                         \
            static_cast<UnderT>(lhs) Op static_cast<UnderT>(rhs)                           \
        );                                                                                 \
    }                                                                                      \
                                                                                           \
    constexpr perms operator Op( perms lhs, aux::underlying_type_t<perms> rhs) noexcept    \
    {                                                                                      \
        using UnderT = aux::underlying_type_t<perms>;                                      \
        return static_cast<perms>(                                                         \
                static_cast<UnderT>(lhs) Op rhs                                            \
            );                                                                             \
    }                                                                                      \
                                                                                           \
    inline perms& operator Op##= (perms & lhs, perms rhs) noexcept                         \
    {                                                                                      \
        using UnderT = aux::underlying_type_t<perms>;                                      \
        return reinterpret_cast<perms &>(                                                  \
            reinterpret_cast<UnderT &>(lhs) Op##= static_cast<UnderT>(rhs)                 \
          );                                                                               \
    }                                                                                      \
                                                                                           \
    inline perms& operator Op##= (perms & lhs, aux::underlying_type_t<perms> rhs) noexcept \
    {                                                                                      \
        using UnderT = aux::underlying_type_t<perms>;                                      \
        return reinterpret_cast<perms &>(                                                  \
            reinterpret_cast<UnderT &>(lhs) Op##= rhs                                      \
          );                                                                               \
    }
# 
                
    // pure operators (lhs & rhs) == perms
    constexpr perms operator~(perms lhs) noexcept
    {
        using UnderT = aux::underlying_type_t<perms>;
        return static_cast<perms>( 
            ~ static_cast<UnderT>(lhs) 
          ); 
    }
    
    ELIB_FS_PERMS_BITWISE_OP(&)
    ELIB_FS_PERMS_BITWISE_OP(|)
    ELIB_FS_PERMS_BITWISE_OP(^)
    
# undef ELIB_FS_PERMS_BITWISE_OP
    
////////////////////////////////////////////////////////////////////////////////
//        LOGICAL OPERATORS                   
////////////////////////////////////////////////////////////////////////////////

    constexpr bool operator!(perms lhs) noexcept
    { 
        using UnderT = aux::underlying_type_t<perms>;
        return ! static_cast<UnderT>(lhs);
    }
    
    constexpr bool operator&&(perms lhs, perms rhs) noexcept
    {
        using UnderT = aux::underlying_type_t<perms>;
        return ( static_cast<UnderT>(lhs) && static_cast<UnderT>(rhs) );
    }
    
    constexpr bool operator&&(perms lhs, bool rhs) noexcept
    {
        using UnderT = aux::underlying_type_t<perms>;
        return ( static_cast<UnderT>(lhs) && rhs );
    }
    
    constexpr bool operator||(perms lhs, perms rhs) noexcept
    {
        using UnderT = aux::underlying_type_t<perms>;
        return ( static_cast<UnderT>(lhs) || static_cast<UnderT>(rhs) );
    }
    
    constexpr bool operator||(perms lhs, bool rhs) noexcept
    {
        using UnderT = aux::underlying_type_t<perms>;
        return ( static_cast<UnderT>(lhs) || rhs );
    }
    
}}                                                          // namespace elib
#endif /* ELIB_FS_PERMS_OPERATORS_HPP */
