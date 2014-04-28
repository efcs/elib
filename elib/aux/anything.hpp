#ifndef ELIB_AUX_ANYTHING_HPP
#define ELIB_AUX_ANYTHING_HPP

/// A type that will construct from and convert to anything.
/// It is intended for use with meta-programming. Its methods are never defined
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