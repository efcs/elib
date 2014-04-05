#ifndef ELIB_AUX_SUPPORT_BY_REF_HPP
#define ELIB_AUX_SUPPORT_BY_REF_HPP

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////
    struct by_ref_
    {
        template <class T>
        constexpr T const& operator()(T && t) const noexcept
        { return t;}
    };

    constexpr by_ref_ by_ref{};
}}                                                          // namespace elib
#endif /* ELIB_AUX_SUPPORT_BY_REF_HPP */