#ifndef ELIB_EXCEPTION_THROW_EXCEPTION_HPP
#define ELIB_EXCEPTION_THROW_EXCEPTION_HPP

# include <elib/exception/fwd.hpp>
# include <elib/exception/exception.hpp>
# include <elib/exception/error_info.hpp>
# include <elib/config.hpp>
# include <elib/aux.hpp>

# define ELIB_THROW_EXCEPTION(...) \
  ::elib::except::throw_exception_from(__VA_ARGS__, __FILE__, __func__, __LINE__)
  
# define ELIB_SET_EXCEPTION_THROW_SITE(...)  \
  ::elib::except::set_exception_throw_site(__VA_ARGS__, __FILE__, __func__, __LINE__)
  
# define ELIB_CATCH_AND_RETHROW(...)                          \
    do {                                                      \
        try {                                                 \
            __VA_ARGS__                                       \
        } catch (::elib::exception & _elib_exception) {       \
            ::elib::except::set_exception_throw_site(         \
                _elib_exception, __FILE__, __func__, __LINE__ \
            );                                                \
            throw;                                            \
        }                                                     \
    } while (false)
    
# define ELIB_RETHROW_BLOCK_BEGIN() try 
        
# define ELIB_RETHROW_BLOCK_END()                           \
    catch (::elib::exception & _elib_exception) {           \
        ::elib::except::set_exception_throw_site(           \
            _elib_exception, __FILE__, __func__, __LINE__); \
        throw;                                              \
    }

    
namespace elib { namespace except
{
    template <class E>
    ELIB_NORETURN void 
    throw_exception(E const & e)
    {
        throw e;
    }
    
    template <class E>
    ELIB_NORETURN void
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
    ELIB_NORETURN void
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
}}                                                          // namespace elib
#endif /* ELIB_EXCEPTION_THROW_EXCEPTION_HPP */