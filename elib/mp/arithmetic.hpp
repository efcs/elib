#ifndef ELIB_MP_ARITHMETIC_HPP
#define ELIB_MP_ARITHMETIC_HPP

# include <elib/aux/arithmetic.hpp>

namespace elib { namespace mp
{
    using aux::negate;
    using aux::negate_t;
    using aux::add;
    using aux::add_t;
    using aux::subtract;
    using aux::subtract_t;
    using aux::multiply;
    using aux::multiply_t;
    using aux::divide;
    using aux::divide_t;
    using aux::modulus;
    using aux::modulus_t;
    using aux::increment;
    using aux::increment_t;
    using aux::decrement;
    using aux::decrement_t;
}}                                                          // namespace elib
#endif /* ELIB_MP_ARITHMETIC_HPP */