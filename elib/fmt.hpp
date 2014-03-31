#ifndef ELIB_FMT_HPP
#define ELIB_FMT_HPP

# include <elib/aux.hpp>
# include <elib/convert.hpp>
# include <elib/lexical_cast.hpp>
# include <elib/CXX14/memory.hpp> /* for std::make_unique */

# include <stdexcept>
# include <string>
# include <utility>  /* for std::forward */
# include <cstdio>
# include <cstdarg>

namespace elib 
{
    template <class T>
    using is_raw_fmt_type = 
        elib::or_<
            aux::is_integral<T>
          , aux::is_floating_point<T>
          , aux::is_pointer<T>
        >;
    
    template <class T>
    using is_fmt_type =
        elib::or_<
            is_raw_fmt_type<T>
          , is_string_convertible<T>
        >;
        
    
    namespace fmt_detail
    {
        
        template <
            class T
          , ELIB_ENABLE_IF(is_raw_fmt_type<T>::value)
        >
        T && convert_arg(T && t) noexcept
        {
            return elib::forward<T>(t);
        }
        
        template <
            class T
          , ELIB_ENABLE_IF(not is_raw_fmt_type<T>::value)
          , ELIB_ENABLE_IF(is_fmt_type<T>::value)
          >
        std::string convert_arg(T && t)
        {
            return convert_to_string(elib::forward<T>(t));
        }
        
        //////////////////////////////////////////////////////////////////////////
        //
        template <class T, ELIB_ENABLE_IF(aux::is_integral<T>::value)>
        constexpr long normalize_arg(T v) noexcept
        { return static_cast<long>(v); }
        
        template <class T, ELIB_ENABLE_IF(aux::is_floating_point<T>::value)>
        constexpr double normalize_arg(T v) noexcept
        { return static_cast<double>(v); }
        
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
                    if (!is_string_convertible<T>::value)
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
        
        va_end(args_cp);
        
        // currently there is no error handling for failure, 
        // so this is hack
        ELIB_ASSERT(ret >= 0);
        
        // handle empty expansion 
        if (ret == 0) return std::string{};
        
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
    
    namespace fmt_detail
    {
        template <class ...Args>
        std::string fmt_variadic_impl(const char *msg, Args &&... args)
        {
            return fmt_varargs(msg, normalize_arg(elib::forward<Args>(args))...);
        }
    }                                                       // namespace fmt_detail

    template <class ...Args>
    std::string fmt_variadic(const char *msg, Args &&... args)
    {
        return fmt_detail::fmt_variadic_impl(
            msg, fmt_detail::convert_arg(elib::forward<Args>(args))...
        );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class ...Ts>
    std::string fmt(const char *msg, Ts &&... ts)
    {
#   ifndef NDEBUG
        check_fmt(msg, ts...);
#   endif
        return fmt_variadic(msg, elib::forward<Ts>(ts)...);
    }
    
    template <class ...Ts>
    std::string checked_fmt(const char *msg, Ts const &... ts)
    {
        check_fmt(msg, ts...);
        return fmt_variadic(msg, elib::forward<Ts>(ts)...);
    }
   
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wformat-security"
# elif defined(__GNUG__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wsuggest-attribute=format"
#   pragma GCC diagnostic ignored "-Wformat-security"
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
# if defined(__clang__)
#   pragma clang diagnostic pop
# elif defined(__GNUG__)
#   pragma GCC diagnostic pop
# endif

    inline std::ostream & build_str(std::ostream & out) noexcept 
    { 
        return out; 
    }
    
    template <class First, class ...Rest>
    inline std::ostream & 
    build_str(std::ostream & out, First && f, Rest &&... rest)
    {
        static_assert(
            is_string_convertible<First>::value
          , "Type First IS NOT string convertible"
        );
        
        out << to_str(elib::forward<First>(f));
        return build_str(out, elib::forward<Rest>(rest)...);
    }
    
    template<class ...Args>
    inline std::string cat_str(Args &&... args)
    {
        std::ostringstream ss;
        build_str(ss, elib::forward<Args>(args)...);
        return ss.str();
    }
}                                                            // namespace elib
#endif                                                  // ELIB_FMT_HPP