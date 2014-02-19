#ifndef ELIB_EXCEPT_THROW_EXCEPTION_HPP
#define ELIB_EXCEPT_THROW_EXCEPTION_HPP

# include <elib/except/fwd.hpp>

namespace elib { namespace except
{
    template <class E>
    [[noreturn]] void throw_exception(E const &);
}}                                                          // namespace elib
#endif /* ELIB_EXCEPT_THROW_EXCEPTION_HPP */