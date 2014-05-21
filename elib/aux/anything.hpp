#ifndef ELIB_AUX_ANYTHING_HPP
#define ELIB_AUX_ANYTHING_HPP

namespace elib { namespace aux
{
#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wundefined-inline"
#endif
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        // detail::anything
        template <class Ignored = decltype(nullptr)>
        struct anything
        {
            anything();

            template <typename T>
            constexpr anything(T &&) noexcept;

            template <class T>
            operator T &&() const noexcept;

        };
    }                                                   // namespace detail
#if defined(__clang__)
# pragma clang diagnostic pop
#endif
    ////////////////////////////////////////////////////////////////////////////
    using anything = detail::anything<>;
}}                                                          // namespace elib
#endif /* ELIB_AUX_ANYTHING_HPP */