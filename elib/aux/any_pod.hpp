#ifndef ELIB_AUX_ANY_POD_HPP
#define ELIB_AUX_ANY_POD_HPP

/// A class that can be constructed with any type.
/// It is helpful because the conversion to any_pod ranks low during overload
/// resolution,  it can be used by meta-programs to provide a last-case overload.
namespace elib { namespace aux
{
    template <class Ignored = decltype(nullptr)>
    struct any_pod
    {
        any_pod(...);
    };
}}                                                          // namespace elib
#endif /* ELIB_AUX_ANY_POD_HPP */