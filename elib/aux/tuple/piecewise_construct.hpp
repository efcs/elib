#ifndef ELIB_AUX_TUPLE_PIECWISE_CONSTRUCT_HPP
#define ELIB_AUX_TUPLE_PIECWISE_CONSTRUCT_HPP

namespace elib { namespace aux
{
    struct piecewise_construct_t
    {};
    
    constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_PIECWISE_CONSTRUCT_HPP */