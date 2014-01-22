#ifndef ELIB_MP_INTEGRAL_CONSTANT_HPP
#define ELIB_MP_INTEGRAL_CONSTANT_HPP

# include <elib/aux/integral_constant.hpp>

namespace elib { namespace mp
{
    using aux::integral_constant;
    
    using aux::bool_;
    using aux::true_;
    using aux::false_;
    
    using aux::char_;
    
    using aux::short_;
    using aux::ushort_;
    
    using aux::int_;
    using aux::uint_;
    
    using aux::long_;
    using aux::ulong_;
    
    using aux::llong_;
    using aux::ullong_;
    
    using aux::size_type_;
    
    using aux::intc_cast;
    using aux::bool_cast;

}}                                                          // namespace elib
#endif /* ELIB_MP_INTEGRAL_CONSTANT_HPP */