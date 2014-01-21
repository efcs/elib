#ifndef ELIB_FUSE_SUPPORT_UNUSED_HPP
#define ELIB_FUSE_SUPPORT_UNUSED_HPP

# include <elib/fuse/support/support_fwd.hpp>
# include <iosfwd>

namespace elib { namespace fuse
{
    struct unused_type
    {
        constexpr unused_type() noexcept {}
        
        template <class T>
        constexpr unused_type(T const&) noexcept {}
        
        template <class T>
        unused_type const& 
        operator=(T const&) const noexcept
        { return *this; }
        
        template <class T>
        unused_type&
        operator=(T const&) noexcept
        { return *this; }
        
        unused_type const&
        operator=(unused_type const&) const noexcept
        { return *this; }
        
        unused_type&
        operator=(unused_type const&) noexcept
        { return *this; }
    };
    
    constexpr unused_type const unused{};
    
    namespace detail
    {
        struct unused_only
        {
            constexpr unused_only(unused_type const&) noexcept {}
        };
    }                                                       // namespace detail
    
    constexpr std::ostream& operator<<(std::ostream& out, detail::unused_only const&) noexcept
    { return out; }
    
    constexpr std::istream& operator>>(std::istream& in, unused_type&) noexcept
    { return in; }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SUPPORT_UNUSED_HPP */