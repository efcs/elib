#ifndef ELIB_AUX_META_COMPARISON_HPP
#define ELIB_AUX_META_COMPARISON_HPP

# include <elib/aux/integral_constant.hpp>

namespace elib { namespace aux
{
    template <class LHS, class RHS>
    struct equal_to : bool_<LHS::type::value == RHS::type::value> {};

    template <class LHS, class RHS>
    struct not_equal_to : bool_<LHS::type::value != RHS::type::value> {};

    template <class LHS, class RHS>
    struct less : bool_<(LHS::type::value < RHS::type::value)> {};

    template <class LHS, class RHS>
    struct less_equal : bool_<(LHS::type::value <= RHS::type::value)> {};

    template <class LHS, class RHS>
    struct greater : bool_<(LHS::type::value > RHS::type::value)> {};

    template <class LHS, class RHS>
    struct greater_equal : bool_<(LHS::type::value >= RHS::type::value)> {};
}}                                                          // namespace elib
#endif /* ELIB_AUX_META_COMPARISON_HPP */