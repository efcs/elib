#ifndef ELIB_EXCEPT_THROW_EXCEPTION_HPP
#define ELIB_EXCEPT_THROW_EXCEPTION_HPP

# include <elib/except/fwd.hpp>
# include <elib/except/exception.hpp>
# include <elib/except/error_info.hpp>

# define ELIB_THROW_EXCEPTION(Ex) \
  ::elib::except::throw_exception_from(ex, __FILE__, __func__, __LINE__)

namespace elib { namespace except
{
    template <class E>
    [[noreturn]] void throw_exception(E const & e)
    {
        throw e;
    }
    
    template <class E>
    [[noreturn]] void t
    throw_exception_from(
        E & e
      , const char *file, const char* func, unsigned line
    )
    {
        throw (
            e << throw_file(file) << throw_func(func) << throw_line(line);
        );
    }
}}                                                          // namespace elib
#endif /* ELIB_EXCEPT_THROW_EXCEPTION_HPP */