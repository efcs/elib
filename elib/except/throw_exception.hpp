#ifndef ELIB_EXCEPT_THROW_EXCEPTION_HPP
#define ELIB_EXCEPT_THROW_EXCEPTION_HPP

# include <elib/except/fwd.hpp>
# include <elib/except/exception.hpp>
# include <elib/except/error_info.hpp>
# include <elib/aux.hpp>

# define ELIB_THROW_EXCEPTION(Ex) \
  ::elib::except::throw_exception_from(Ex, __FILE__, __func__, __LINE__)
  
# define ELIB_SET_EXCEPTION_THROW_SITE(Ex)  \
  ::elib::except::set_exception_throw_site(Ex, __FILE__, __func__, __LINE__)

namespace elib { namespace except
{
    template <class E>
    [[noreturn]] void 
    throw_exception(E const & e)
    {
        throw e;
    }
    
    template <class E>
    [[noreturn]] void
    throw_exception_from(
        E & e
      , const char *file, const char* func, unsigned line
    )
    {
        throw (
            e << throw_file(file) << throw_func(func) << throw_line(line)
        );
    }
    
    template <
        class E
      , ELIB_ENABLE_IF(!aux::is_lvalue_reference<E>::value)
    >
    [[noreturn]] void
    throw_exception_from(
        E && e
      , const char *file, const char* func, unsigned line
    )
    {
        e << throw_file(file) << throw_func(func) << throw_line(line);
        throw e;
    }
    
    template <class E>
    E & set_exception_throw_site(
        E & e
      , const char* file, const char* func, unsigned line
    )
    {
        return (e << throw_file(file) << throw_func(func) << throw_line(line));
    }
    
    template <class E>
    E & set_exception_throw_site(
        E && e
      , const char* file, const char* func, unsigned line
    )
    {
        return (e << throw_file(file) << throw_func(func) << throw_line(line));
    }
}}                                                          // namespace elib
#endif /* ELIB_EXCEPT_THROW_EXCEPTION_HPP */