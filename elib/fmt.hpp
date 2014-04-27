#ifndef ELIB_FMT_HPP
#define ELIB_FMT_HPP

# include <elib/aux.hpp>
# include <elib/config.hpp>
# include <elib/memory/make_unique.hpp> /* for std::make_unique */

# include <stdexcept>
# include <sstream>
# include <string>
# include <utility>  /* for std::forward */
# include <cstdio>
# include <cstdarg>

namespace elib 
{
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
    namespace fmt_detail
    {
        struct implicit_cast_conversion_tag       {};
        struct explicit_cast_conversion_tag       {};
        struct stream_insertion_conversion_tag    {};
        struct to_string_function_conversion_tag  {};
        struct bad_conversion_tag                 {};
        
        ////////////////////////////////////////////////////////////////////////////
        template <
            class T
          , ELIB_ENABLE_IF_VALID_EXPR(to_string( elib::declval<T>() ))
          >
        elib::true_ 
        has_to_string_function_impl(int);
        
        template <class>
        elib::false_ 
        has_to_string_function_impl(long);
    }                                                       // namespace fmt_detail
    
    ///////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_explicit_string_cast = 
        aux::is_explicitly_convertible<T, std::string>;
        
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_implicit_string_cast = 
        typename aux::is_convertible<T, std::string>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_string_cast = 
        elib::or_<
            has_implicit_string_cast<T>
          , has_explicit_string_cast<T>
          >;
        
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_stream_insertion = aux::is_output_streamable<T>;
        
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_to_string = decltype(
        fmt_detail::has_to_string_function_impl<T>(0)
      );
    
    namespace fmt_detail
    {
        
        ////////////////////////////////////////////////////////////////////////////
        template <class T>
        using conversion_tag = typename
        if_<
            has_implicit_string_cast<T>
          , implicit_cast_conversion_tag
        >::template
        else_if<
            has_explicit_string_cast<T>
          , explicit_cast_conversion_tag
        >::template
        else_if<
            has_stream_insertion<T>
          , stream_insertion_conversion_tag
        >::template
        else_if<
            has_to_string<T>
          , to_string_function_conversion_tag
        >::template
        else_<
            bad_conversion_tag
        >::type;
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        std::string convert_str_impl(T const & t, implicit_cast_conversion_tag)
        {
            return t;
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        std::string convert_str_impl(T && t, explicit_cast_conversion_tag)
        {
            return static_cast<std::string>(elib::forward<T>(t));
        }
        
        ///////////////////////////////////////////////////////////////////////
        template <class T>
        std::string convert_str_impl(T const & t, stream_insertion_conversion_tag)
        {
            std::ostringstream ss;
            ss << std::boolalpha << t;
            return ss.str();
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        std::string convert_str_impl(T const & t, to_string_function_conversion_tag)
        {
            return to_string(t);
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        std::string convert_str_impl(T const &, bad_conversion_tag)
        {
            static_assert(
                aux::never<T>::value
              , "Cannot convert type T to string"
            );
            return "";
        }
    }                                                   // namespace fmt_detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_string_conversion = 
        elib::not_<aux::is_same<
            fmt_detail::bad_conversion_tag
          , fmt_detail::conversion_tag<T>
        >>;

    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    std::string mkstr(T && t)
    {
        static_assert(
            has_string_conversion<T>::value
          , "Cannot use mkstr with type T. It is not string convertible"
        );
        
        return fmt_detail::convert_str_impl(
            elib::forward<T>(t)
          , fmt_detail::conversion_tag<T>{}
        );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline std::ostream & 
    build_str(std::ostream & out) noexcept 
    { 
        return out; 
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class ...Rest>
    inline std::ostream & 
    build_str(std::ostream & out, First && f, Rest &&... rest)
    {
        out << mkstr(elib::forward<First>(f));
        return build_str(out, elib::forward<Rest>(rest)...);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template<class ...Args>
    inline std::string cat_str(Args &&... args)
    {
        std::ostringstream ss;
        build_str(ss, elib::forward<Args>(args)...);
        return ss.str();
    }
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
    namespace fmt_detail
    {
        template <class T>
        using is_cfmt_type_impl = 
            elib::or_<
                aux::is_integral<T>
              , aux::is_floating_point<T>
              , aux::is_pointer<T>
            >;
        
        template <class T>
        using is_fmt_type_impl =
            elib::or_<
                is_cfmt_type_impl<T>
              , aux::is_same<T, std::string>
              >;
    }                                                       // namespace fmt_detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using is_cfmt_type = fmt_detail::is_cfmt_type_impl<aux::uncvref<T>>;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using is_fmt_type = fmt_detail::is_fmt_type_impl<aux::uncvref<T>>;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using is_ext_fmt_type = 
        elib::or_<
            is_fmt_type<T>
          , has_string_conversion<T>
          >;
    
    namespace fmt_detail
    {
   
        
        template <
            class T
          , ELIB_ENABLE_IF(is_fmt_type<T>::value)
          >
        auto convert_arg(T && t) 
        ELIB_AUTO_RETURN_NOEXCEPT( elib::forward<T>(t) )
        
        template <
            class T
          , ELIB_ENABLE_IF(is_ext_fmt_type<T>::value)
          , ELIB_ENABLE_IF(!is_fmt_type<T>::value)
          >
        std::string convert_arg(T && t)
        {
            return mkstr(elib::forward<T>(t));
        }
        
        //////////////////////////////////////////////////////////////////////////
        template <class T, ELIB_ENABLE_IF(aux::is_integral<T>::value)>
        constexpr long normalize_arg(T v) noexcept
        { return static_cast<long>(v); }
        
        template <class T, ELIB_ENABLE_IF(aux::is_floating_point<T>::value)>
        constexpr double normalize_arg(T v) noexcept
        { return static_cast<double>(v); }
        
        template <class T, ELIB_ENABLE_IF(aux::is_pointer<T>::value)>
        constexpr T normalize_arg(T v) noexcept
        { return v; }
        
        inline void* normalize_arg(std::nullptr_t) noexcept
        { return static_cast<void*>(nullptr); }
        
        inline const char* normalize_arg(std::string const & s) noexcept
        { return s.c_str(); }
        
        // TODO: Other transformations as well? 
        // - unwrap std::reference_wrapper
        // - explicitly convertible to std::string
        // - implicitly convertible to const char*
    }                                                       // namespace fmt_detail
      
    //////////////////////////////////////////////////////////////////////////
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
     
    ////////////////////////////////////////////////////////////////////////////
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
                    if (!aux::is_c_string<T>::value)
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
#   if ELIB_COMPILER_VERSION >= 40800
#     pragma GCC diagnostic ignored "-Wsuggest-attribute=format"
#   else
#     pragma GCC diagnostic ignored "-Wmissing-format-attribute"
#   endif
# endif
    inline std::string fmt_varargs(const char *msg, va_list args)
    {
        // we might need a second shot at this, so pre-emptivly make a copy
        va_list args_cp;
        va_copy(args_cp, args);
        
        //TODO, use std::array for first attempt to avoid one memory allocation
        // guess what the size might be
        std::size_t size = 256;
        auto buff_ptr = elib::make_unique<char[]>(size);
        auto ret = std::vsnprintf(buff_ptr.get(), size, msg, args_cp);
        
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
            buff_ptr = elib::make_unique<char[]>(size);
            ret = std::vsnprintf(buff_ptr.get(), size, msg, args);
            ELIB_ASSERT(ret > 0 && static_cast<std::size_t>(ret) < size);
        }
        
        return std::string{ buff_ptr.get() };
    }
# if defined(__clang__)
#   pragma clang diagnostic pop
# elif defined(__GNUG__)
#   pragma GCC diagnostic pop
# endif

    ////////////////////////////////////////////////////////////////////////////
    inline std::string fmt_varargs(const char *msg, ...) 
    {
        va_list args;
        va_start(args, msg);
        auto tmp = fmt_varargs(msg, args);
        va_end(args);
        return tmp;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ...Ts>
    std::string cfmt(const char *msg, Ts const &... ts)
    {
#   ifndef NDEBUG
        check_fmt(msg, ts...);
#   endif
        return fmt_varargs(msg, ts...);
    }

    ////////////////////////////////////////////////////////////////////////////
    template <class ...Ts>
    std::string checked_cfmt(const char *msg, Ts const &... ts)
    {
        check_fmt(msg, ts...);
        return fmt_varargs(msg, ts...);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ...Ts>
    std::string fmt(const char *msg, Ts const &... ts)
    {
        return cfmt(
            msg, fmt_detail::normalize_arg(ts)...
        );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ...Ts>
    std::string checked_fmt(const char *msg, Ts const &... ts)
    {
        return checked_cfmt(
            msg, fmt_detail::normalize_arg(ts)...
        );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ...Ts>
    std::string ext_fmt(const char *msg, Ts &&... ts)
    {
        return fmt(
            msg, fmt_detail::convert_arg(elib::forward<Ts>(ts))...
        );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ...Ts>
    std::string checked_ext_fmt(const char *msg, Ts &&... ts)
    {
        return checked_fmt(
            msg, fmt_detail::convert_arg(elib::forward<Ts>(ts))...
        );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ...Ts>
    void eprintf(const char *msg, Ts &&... ts)
    {
        std::cout << fmt(msg, elib::forward<Ts>(ts)...);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ...Ts>
    void eprintf_err(const char *msg, Ts &&... ts)
    {
        std::cerr << fmt(msg, elib::forward<Ts>(ts)...);
    }
}                                                            // namespace elib
#endif                                                  // ELIB_FMT_HPP