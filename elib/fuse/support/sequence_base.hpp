#ifndef ELIB_FUSE_SUPPORT_SEQUENCE_BASE_HPP
#define ELIB_FUSE_SUPPORT_SEQUENCE_BASE_HPP

namespace elib { namespace fuse
{
    namespace detail
    {
        struct from_sequence_convertible_type
        {};
    }                                                       // namespace detail
    
    template <class Seq>
    struct sequence_base
    {
        Seq const& derived() const noexcept
        {
            return static_cast<Seq const&>(*this);
        }
        
        Seq& derived() noexcept
        {
            return static_cast<Seq&>(*this);
        }
        
        constexpr operator detail::from_sequence_convertible_type() const noexcept
        {
            return detail::from_sequence_convertible_type{};
        }
    };
    
    struct fusion_sequence_tag {};
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SUPPORT_SEQUENCE_BASE_HPP */