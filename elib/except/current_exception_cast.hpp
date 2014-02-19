#ifndef ELIB_EXCEPT_CURRENT_EXCEPTION_CAST_HPP
#define ELIB_EXCEPT_CURRENT_EXCEPTION_CAST_HPP

# include <elib/except/fwd.hpp>

namespace elib { namespace except
{
    template <class E>
    E * current_exception_cast();
}}                                                          // namespace elib
#endif /* ELIB_EXCEPT_CURRENT_EXCEPTION_CAST_HPP */