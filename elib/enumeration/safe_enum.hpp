#ifndef ELIB_ENUMERATION_SAFE_ENUM_HPP
#define ELIB_ENUMERATION_SAFE_ENUM_HPP

namespace elib {
namespace enumeration {
 
        
template <typename Base, typename Enum = typename Base::type>
class safe_enum : public Base {
public:
    typedef typename Base::type enum_type;
    typedef typename std::underlying_type<enum_type>::type base_type;
    
    safe_enum() = default;
    
    inline
    safe_enum(enum_type e)
        : m_val{e}
    { }
    
    ~safe_enum() = default;
    
    constexpr enum_type
    value() const noexcept
    { return m_val; }
    
    constexpr base_type
    base_value() const noexcept
    { return static_cast<base_type>(m_val); }
    
    
    friend constexpr bool
    operator==(const safe_enum & lhs, const safe_enum & rhs) noexcept
    { return lhs == rhs; }
    
    friend constexpr bool
    operator!=(const safe_enum & lhs, const safe_enum & rhs) noexcept
    { return lhs != rhs; }
    
    friend constexpr bool
    operator<(const safe_enum & lhs, const safe_enum & rhs) noexcept
    { return lhs < rhs; }
    
    friend constexpr bool
    operator<=(const safe_enum & lhs, const safe_enum & rhs) noexcept
    { return lhs <= rhs; }
    
    friend constexpr bool
    operator>(const safe_enum & lhs, const safe_enum & rhs) noexcept
    { return lhs > rhs; }
    
    friend constexpr bool
    operator>=(const safe_enum & lhs, const safe_enum & rhs) noexcept
    { return lhs >= rhs; }
    
private:
    enum_type m_val{};
};


    
} /* namespace enumeration */
} /* namespace elib */
#endif /* ELIB_ENUMERATION_SAFE_ENUM_HPP */