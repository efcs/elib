#ifndef ELIB_AUX_ANYTHING_HPP
#define ELIB_AUX_ANYTHING_HPP

namespace elib { namespace aux
{
#if defined(__clang__)
# pragma clang diagnostic push
// Some clang version don't support undefined inlines. 
// suppress unknown pragma warning as well.
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wundefined-inline"
#endif
  
    ////////////////////////////////////////////////////////////////////////
    // anything_type
    template <class Ignored = decltype(nullptr)>
    struct anything_type
    {
        anything_type();

        template <typename T>
        constexpr anything_type(T &&) noexcept;
            
        template <class T>
        operator T() const noexcept;
    };
#if defined(__clang__)
# pragma clang diagnostic pop
#endif
    ////////////////////////////////////////////////////////////////////////////
    using anything = anything_type<>;
}}                                                          // namespace elib
#endif /* ELIB_AUX_ANYTHING_HPP */