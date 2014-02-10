#ifndef ELIB_FMT_HPP
#define ELIB_FMT_HPP

# include <elib/assert.hpp>
# include <elib/aux.hpp>
# include <elib/lexical_cast.hpp>
# include <elib/CXX14/memory.hpp> /* for std::make_unique */

# include <stdexcept>
# include <string>
# include <utility>  /* for std::forward */
# include <cstdio>
# include <cstdarg>

namespace elib 
{
    namespace fmt_detail
    {
        //////////////////////////////////////////////////////////////////////////
        //
        template <class T, ELIB_ENABLE_IF(aux::is_integral<T>::value)>
        constexpr long normalize_arg(T v) noexcept
        { return v; }
        
        template <class T, ELIB_ENABLE_IF(aux::is_floating_point<T>::value)>
        constexpr double normalize_arg(T v) noexcept
        { return v; }
        
        template <class T, ELIB_ENABLE_IF(aux::is_pointer<T>::value)>
        constexpr T normalize_arg(T v) noexcept
        { return v; }
        
        inline const char* normalize_arg(std::string const & s) noexcept
        { return s.c_str(); }
        
        // TODO: Other transformations as well? 
        // - unwrap std::reference_wrapper
        // - explicitly convertible to std::string
        // - implicitly convertible to const char*
    }                                                       // namespace fmt_detail
      
    //////////////////////////////////////////////////////////////////////////
    // 
    inline void check_fmt(const char *f)
    {
        for (; *f; ++f)
        {
            if (*f != '%' || *++f == '%') continue;
            // else
            throw std::logic_error(
                "Too few format specifiers for format string"
                );
        }
    }
        
    template <class T, class ...Ts>
    inline void check_fmt(const char *f, T const &, Ts const &... ts)
    {
        for (; *f; ++f)
        {
            if (*f != '%' || *++f == '%') continue;
            switch (*f)
            {
                default:
                    throw std::logic_error(
                        std::string{"Invalid format char: "} + *f
                        );
                case 'd': case 'i': case 'u': case 'o': 
                case 'x': case 'X': case 'c':
                    if (!aux::is_integral<T>::value)
                        throw std::logic_error(
                            "Type mismatch: expected integral"
                            );
                    break;
                case 'f': case 'F': case 'e': case 'E': 
                case 'g': case 'G': case 'a': case 'A':
                    if (!aux::is_floating_point<T>::value)
                        throw std::logic_error(
                            "Type mismatch: expected floating point"
                            );
                    break;
                case 's':
                    if (!aux::is_same<const char*, T>::value)
                        throw std::logic_error(
                            "Type mismatch: expected C string"
                            );
                        break;
                case 'p':
                    if (!aux::is_pointer<T>::value)
                        throw std::logic_error(
                            "Type mismatch: expected pointer"
                            );
                    break;
                case 'n':
                    if (!(aux::is_pointer<T>::value
                            && aux::is_integral<aux::remove_pointer_t<T>>::value
                        ))
                        throw std::logic_error(
                            "Type mismatch: expected pointer to integral"
                        );
                    break;
            }                                               // switch
            return check_fmt(++f, ts...);
        }                                               // for (f)
        throw std::logic_error(
            "Too few format specifiers for format string"
            );
    }                                                   // check_fmt
     
/* When you have to suppress two warnings for one function
 * thats probably a bad function. I blame C. */
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wformat-nonliteral"
# elif defined(__GNUG__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wsuggest-attribute=format"
# endif
    inline std::string fmt_varargs(const char *msg, va_list args)
    {
        // we might need a second shot at this, so pre-emptivly make a copy
        va_list args_cp;
        va_copy(args_cp, args);
        
        //TODO, use std::array for first attempt to avoid one memory allocation
        // guess what the size might be
        std::size_t size = 256;
        auto buff_ptr = std::make_unique<char[]>(size);
        auto ret = vsnprintf(buff_ptr.get(), size, msg, args_cp);
        
        // currently there is no error handling for failure, 
        // so this is hack
        ELIB_ASSERT(ret >= 0);
        
        // handle empty expansion 
        if (ret == 0) return std::string{};
            
        va_end(args_cp);
        
        // we did not provide a long enough buffer on our first attempt
        if (static_cast<std::size_t>(ret) >= size)
        {
            // account for null-byte in size
            // cast to prevent overflow
            size = static_cast<std::size_t>(ret) + 1;
            buff_ptr = std::make_unique<char[]>(size);
            ret = vsnprintf(buff_ptr.get(), size, msg, args);
            ELIB_ASSERT(ret > 0 && static_cast<std::size_t>(ret) < size);
        }
        
        return std::string{ buff_ptr.get() };
    }
# if defined(__clang__)
#   pragma clang diagnostic pop
# elif defined(__GNUG__)
#   pragma GCC diagnostic pop
# endif

    inline std::string fmt_varargs(const char *msg, ...) 
    {
        va_list args;
        va_start(args, msg);
        auto tmp = fmt_varargs(msg, args);
        va_end(args);
        return tmp;
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    template <class ...Ts>
    std::string fmt(const char *msg, Ts const &... ts)
    {
#   ifndef NDEBUG
        check_fmt(msg, fmt_detail::normalize_arg(ts)...);
#   endif
        return fmt_varargs(msg, fmt_detail::normalize_arg(ts)...);
    }
    
    template <class ...Ts>
    std::string checked_fmt(const char *msg, Ts const &... ts)
    {
        check_fmt(msg, fmt_detail::normalize_arg(ts)...);
        return fmt_varargs(msg, fmt_detail::normalize_arg(ts)...);
    }
   
# if defined(__GNUG__) && !defined(__clang__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wsuggest-attribute=format"
# endif
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class ...Ts>
    int eprintf(const char *msg, Ts const &... ts)
    {
#   ifndef NDEBUG
        check_fmt(msg, fmt_detail::normalize_arg(ts)...);
#   endif
        return std::printf(msg, fmt_detail::normalize_arg(ts)...);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class ...Ts>
    int eprintf_err(const char *msg, Ts const &... ts)
    {
#   ifndef NDEBUG
        check_fmt(msg, fmt_detail::normalize_arg(ts)...);
#   endif
        return std::fprintf(stderr, msg, fmt_detail::normalize_arg(ts)...);
    }
# if defined(__GNUG__) && !defined(__clang__)
#   pragma GCC diagnostic pop
# endif
}                                                            // namespace elib
#endif                                                  // ELIB_FMT_HPP