#ifndef ELIB_AUX_TRAITS_UNCVREF_HPP
#define ELIB_AUX_TRAITS_UNCVREF_HPP

# include <elib/aux/traits/remove_cv.hpp>
# include <elib/aux/traits/remove_reference.hpp>

namespace elib { namespace aux
{
    template <class T>
    using uncvref = remove_cv_t<remove_reference_t<T>>;
}}                                                           //namespace elib
namespace elib
{
    using aux::uncvref;
}
#endif /* ELIB_AUX_TRAITS_UNCVREF_HPP */
