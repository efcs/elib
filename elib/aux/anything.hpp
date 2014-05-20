#ifndef ELIB_AUX_ANYTHING_HPP
#define ELIB_AUX_ANYTHING_HPP

namespace elib { namespace aux
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        // detail::anything
        template <class Ignored = decltype(nullptr)>
        struct anything
        {
            anything();

            template <typename T>
            constexpr anything(T const &) noexcept;

            template <class T>
            operator T &&() const noexcept;
        };
    }                                                   // namespace detail

    ////////////////////////////////////////////////////////////////////////////
    using anything = detail::anything<>;
}}                                                          // namespace elib
#endif /* ELIB_AUX_ANYTHING_HPP */