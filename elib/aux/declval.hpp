#ifndef ELIB_AUX_DECLVAL_HPP
#define ELIB_AUX_DECLVAL_HPP

# include <elib/aux/traits/add_rvalue_reference.hpp>

namespace elib { namespace aux
{
    template <class T>
    aux::add_rvalue_reference_t<T>
    declval() noexcept;
}}                                                          // namespace elib
namespace elib
{
    using aux::declval;
}                                                           // namespace elib
#endif /* ELIB_AUX_DECLVAL_HPP */