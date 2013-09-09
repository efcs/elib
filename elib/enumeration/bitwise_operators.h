#ifndef ELIB_ENUMERATION_BITWISE_OPERATORS_H
#define ELIB_ENUMERATION_BITWISE_OPERATORS_H


#include <type_traits> 


namespace elib {
namespace enumeration {
    
    

namespace detail {
    

    
template <typename T>
using is_enum_type = std::is_enum<typename std::remove_reference<T>::type>;

template <typename T>
using is_integral_type = std::is_integral<typename std::remove_reference<T>::type>;

template <typename T, typename = void>
struct enable_if_integral {};

template <typename T>
struct enable_if_integral<T, 
        typename std::enable_if<is_integral_type<T>::value>::type> {
    typedef typename std::remove_reference<T>::type type;
};

template <typename T>
using enable_if_integral_t = typename enable_if_integral<T>::type;

    
template <typename T, typename = void>
struct base_type {};

template <typename T>
struct base_type<T, typename std::enable_if<is_enum_type<T>::value>::type>
{
    typedef typename std::underlying_type<
            typename std::remove_reference<T>::type>::type type;
};

template <typename T>
using base_t = typename base_type<T>::type;



template <typename T, typename U>
struct is_enum_enum : public std::integral_constant<bool,
                                is_enum_type<T>::value &&
                                is_enum_type<U>::value>
{ };

template <typename T, typename U>
struct is_enum_integral : public std::integral_constant<bool,
                                    is_enum_type<T>::value &&
                                    is_integral_type<U>::value>
{ };

template <typename T, typename U>
struct is_integral_enum : public std::integral_constant<bool,
                                    is_integral_type<T>::value &&
                                    is_enum_type<U>::value>
{ };



template <bool B, typename T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

    
} /* namespace detail */


template <typename Enum>
struct enum_bitwise_operators {

    typedef typename std::remove_reference<Enum>::type enum_type;
    typedef typename std::underlying_type<enum_type>::type base_type;
    
private:
    static constexpr base_type
    dc(enum_type e) noexcept
    { return static_cast<base_type>(e); }
    
    template <typename T>
    static constexpr enum_type
    uc(T v) noexcept
    { return static_cast<enum_type>(v); }
    
public:
    
//
// operator &
//
    friend constexpr base_type
    operator&(enum_type lhs, enum_type rhs) noexcept
    { return ( dc(lhs) & dc(rhs) ); }
    
    template <typename U>
    friend constexpr detail::enable_if_integral_t<U>
    operator&(enum_type lhs, U rhs) noexcept
    { return ( dc(lhs) & rhs ); }
    
    template <typename U>
    friend constexpr detail::enable_if_integral_t<U>
    operator&(U lhs, enum_type rhs) noexcept
    { return ( lhs & dc(rhs) ); }

//
//operator |
//
    friend constexpr base_type
    operator|(enum_type lhs, enum_type rhs) noexcept
    { return ( dc(lhs) | dc(rhs) ); }
    
    template <typename U>
    friend constexpr detail::enable_if_integral_t<U>
    operator|(enum_type lhs, U rhs) noexcept
    { return ( dc(lhs) | rhs ); }
    
    template <typename U>
    friend constexpr detail::enable_if_integral_t<U>
    operator|(U lhs, enum_type rhs) noexcept
    { return ( lhs | dc(rhs) ); }
    
//
// operator^
//
    friend constexpr base_type
    operator^(enum_type lhs, enum_type rhs) noexcept
    { return ( dc(lhs) ^ dc(rhs) ); }
    
    template <typename U>
    friend constexpr detail::enable_if_integral_t<U>
    operator^(enum_type lhs, U rhs) noexcept
    { return ( dc(lhs) ^ rhs ); }
    
    template <typename U>
    friend constexpr detail::enable_if_integral_t<U>
    operator^(U lhs, enum_type rhs) noexcept
    { return ( lhs ^ dc(rhs) ); }
    
    

};



template <typename T, typename U>
constexpr detail::enable_if_t<detail::is_enum_enum<T, U>::value, 
                              detail::base_t<T>>
operator&(T lhs, U rhs) noexcept
{
    return (static_cast<detail::base_t<T>>(lhs) & 
            static_cast<detail::base_t<U>>(rhs));
}

template <typename T, typename U>
constexpr detail::enable_if_t<detail::is_integral_enum<T, U>::value, 
                              detail::base_t<U>>
operator&(T lhs, U rhs) noexcept
{
    return (lhs & static_cast<detail::base_t<U>>(rhs));
}

template <typename T, typename U>
constexpr detail::enable_if_t<detail::is_enum_integral<T, U>::value, 
                              detail::base_t<T>>
operator&(T lhs, U rhs) noexcept
{
    return (static_cast<detail::base_t<T>>(lhs) & rhs);
}

////////////////////////////////////////////////////////////////////////////////
//                                                                          
////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
constexpr detail::enable_if_t<detail::is_enum_enum<T, U>::value, 
                              detail::base_t<T>>
operator|(T lhs, U rhs) noexcept
{
    return (static_cast<detail::base_t<T>>(lhs) | 
            static_cast<detail::base_t<U>>(rhs));
}

template <typename T, typename U>
constexpr detail::enable_if_t<detail::is_integral_enum<T, U>::value, 
                              detail::base_t<U>>
operator|(T lhs, U rhs) noexcept
{
    return (lhs | static_cast<detail::base_t<U>>(rhs));
}

template <typename T, typename U>
constexpr detail::enable_if_t<detail::is_enum_integral<T, U>::value, 
                              detail::base_t<T>>
operator|(T lhs, U rhs) noexcept
{
    return (static_cast<detail::base_t<T>>(lhs) | rhs);
}

////////////////////////////////////////////////////////////////////////////////
//                                                                          
////////////////////////////////////////////////////////////////////////////////


template <typename T, typename U>
constexpr detail::enable_if_t<detail::is_enum_enum<T, U>::value, 
                              detail::base_t<T>>
operator^(T lhs, U rhs) noexcept
{
    return (static_cast<detail::base_t<T>>(lhs) ^ 
            static_cast<detail::base_t<U>>(rhs));
}

template <typename T, typename U>
constexpr detail::enable_if_t<detail::is_integral_enum<T, U>::value, 
                              detail::base_t<U>>
operator^(T lhs, U rhs) noexcept
{
    return (lhs ^ static_cast<detail::base_t<U>>(rhs));
}

template <typename T, typename U>
constexpr detail::enable_if_t<detail::is_enum_integral<T, U>::value, 
                              detail::base_t<T>>
operator^(T lhs, U rhs) noexcept
{
    return (static_cast<detail::base_t<T>>(lhs) ^ rhs);
}


////////////////////////////////////////////////////////////////////////////////
//                                                                          
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
//                             ASSIGMENTS                                             
////////////////////////////////////////////////////////////////////////////////


template <typename T, typename U>
inline detail::enable_if_t<detail::is_enum_enum<T, U>::value, T>&
operator&=(T& lhs, U rhs) noexcept
{
    lhs = static_cast<detail::base_t<T>>(static_cast<detail::base_t<T>>(lhs) & 
                         static_cast<detail::base_t<U>>(rhs));
    return lhs;
}

template <typename T, typename U>
inline detail::enable_if_t<detail::is_integral_enum<T, U>::value, T>&
operator&=(T& lhs, U rhs) noexcept
{
    lhs = (lhs & static_cast<detail::base_t<U>>(rhs));
    return lhs;
}

template <typename T, typename U>
inline detail::enable_if_t<detail::is_enum_integral<T, U>::value, T>&
operator&=(T& lhs, U rhs) noexcept
{
    lhs = static_cast<detail::base_t<T>>(static_cast<detail::base_t<T>>(lhs) & rhs);
    return lhs;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                          
////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
inline detail::enable_if_t<detail::is_enum_enum<T, U>::value, T>&
operator|=(T& lhs, U rhs) noexcept
{
    lhs = static_cast<detail::base_t<T>>(static_cast<detail::base_t<T>>(lhs) | 
                         static_cast<detail::base_t<U>>(rhs));
    return lhs;
}

template <typename T, typename U>
inline detail::enable_if_t<detail::is_integral_enum<T, U>::value, T>&
operator|=(T& lhs, U rhs) noexcept
{
    lhs = (lhs | static_cast<detail::base_t<U>>(rhs));
    return lhs;
}

template <typename T, typename U>
inline detail::enable_if_t<detail::is_enum_integral<T, U>::value, T>&
operator|=(T& lhs, U rhs) noexcept
{
    lhs = static_cast<detail::base_t<T>>(
            static_cast<detail::base_t<T>>(lhs) | rhs);
    return lhs;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                          
////////////////////////////////////////////////////////////////////////////////


template <typename T, typename U>
inline detail::enable_if_t<detail::is_enum_enum<T, U>::value, T>&
operator^=(T& lhs, U rhs) noexcept
{
    lhs = static_cast<detail::base_t<T>>(static_cast<detail::base_t<T>>(lhs) ^ 
                         static_cast<detail::base_t<U>>(rhs));
    return lhs;
}

template <typename T, typename U>
inline detail::enable_if_t<detail::is_integral_enum<T, U>::value, T>&
operator^=(T& lhs, U rhs) noexcept
{
    lhs = (lhs ^ static_cast<detail::base_t<U>>(rhs));
    return lhs;
}

template <typename T, typename U>
inline detail::enable_if_t<detail::is_enum_integral<T, U>::value, T>&
operator^=(T& lhs, U rhs) noexcept
{
    lhs = static_cast<detail::base_t<T>>(static_cast<detail::base_t<T>>(lhs) ^ rhs);
    return lhs;
}

} /* namespace enumeration */
} /* namespace elib */
#endif /* ELIB_ENUMERATION_BITWISE_OPERATORS_H */