#ifndef ELIB_AUX_TRAITS_ALIGNED_UNION_HPP
#define ELIB_AUX_TRAITS_ALIGNED_UNION_HPP

# include <elib/config.hpp>
# include <type_traits>
# include <cstddef>

namespace elib { namespace aux
{
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
    using std::aligned_union;
        
    template <std::size_t Len, class ...Types>
    using aligned_union_t = typename aligned_union<Len, Types...>::type;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ALIGNED_UNION_HPP */
