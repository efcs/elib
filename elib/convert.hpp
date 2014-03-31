#ifndef ELIB_CONVERT_HPP
#define ELIB_CONVERT_HPP

# include <elib/aux.hpp>
# include <iostream>
# include <sstream>
# include <string>

namespace elib { namespace converts
{
    constexpr struct implicit_conversion_tag_t
    {} implicit_conversion_tag {};
    
    constexpr struct explicit_conversion_tag_t
    {} explicit_conversion_tag {};
    
    constexpr struct stream_insertion_tag_t 
    {} stream_insertion_tag {};
    
    constexpr struct to_string_function_tag_t 
    {} to_string_function_tag {};
    
    constexpr struct bad_conversion_tag_t
    {} bad_conversion_tag {};
    
    namespace detail
    {        
        ////////////////////////////////////////////////////////////////////////////
        template <
            class From, class To
        , ELIB_ENABLE_IF_VALID_EXPR( static_cast<To>(elib::declval<From>()) )
        , ELIB_ENABLE_IF( !aux::is_convertible<From, To>::value )
        >
        true_ has_explicit_conversion_impl(int) noexcept;
        
        template <class From, class To>
        false_ has_explicit_conversion_impl(long) noexcept;
        
        ////////////////////////////////////////////////////////////////////////////
        template <
            class T
        , ELIB_ENABLE_IF_VALID_EXPR( to_string(elib::declval<T>()) )
        >
        true_ has_to_string_function_impl(int) noexcept;
        
        template <class T>
        false_ has_to_string_function_impl(long) noexcept;
        
        ////////////////////////////////////////////////////////////////////////////
        template <
            class T
        , ELIB_ENABLE_IF_VALID_EXPR(
            operator<<( elib::declval<std::ostream>(), elib::declval<T>() ) 
            )
        >
        true_ has_stream_insertion_impl(int) noexcept;
        
        template <class T>
        false_ has_stream_insertion_impl(long) noexcept;
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using is_string_constructible = typename 
        aux::is_constructible<
            std::string, T
        >::type;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class From, class To>
    using has_explicit_conversion = decltype(
        detail::has_explicit_conversion_impl<From, To>(0)
    );
    
    ////////////////////////////////////////////////////////////////////////////
    template <class From, class To>
    using has_implicit_conversion = typename aux::is_convertible<From, To>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class From, class To>
    using has_conversion = or_<
        has_explicit_conversion<From, To>
      , has_implicit_conversion<From, To>
    >;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_explicit_string_conversion = 
        has_explicit_conversion<T, std::string>;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_implicit_string_conversion = 
        has_implicit_conversion<T, std::string>;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_string_conversion = 
        has_conversion<T, std::string>;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_stream_insertion = decltype(
        detail::has_stream_insertion_impl<T>(0)
    );
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_to_string = decltype(
        detail::has_to_string_function_impl<T>(0)
    );
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using conversion_tag = typename
        if_<
            has_implicit_string_conversion<T>
          , implicit_conversion_tag_t
        >::template
        else_if<
            has_explicit_string_conversion<T>
          , explicit_conversion_tag_t
        >::template
        else_if<
            has_stream_insertion<T>
          , stream_insertion_tag_t
        >::template
        else_if<
            has_to_string<T>
          , to_string_function_tag_t
        >::template
        else_<
            bad_conversion_tag_t
        >::type;

    template <class T>
    using is_string_convertible = 
        elib::not_<
            aux::is_same<bad_conversion_tag_t, conversion_tag<T>>
          >;
       
    namespace detail
    {
        template <class T>
        std::string convert_str_impl(T const & t, implicit_conversion_tag_t)
        {
            return t;
        }
        
        template <class T>
        std::string convert_str_impl(T const & t, explicit_conversion_tag_t)
        {
            return static_cast<std::string>(t);
        }
        
        template <class T>
        std::string convert_str_impl(T const & t, stream_insertion_tag_t)
        {
            std::stringstream ss;
            ss << t;
            return ss.str();
        }
        
        template <class T>
        std::string convert_str_impl(T const & t, to_string_function_tag_t)
        {
            return to_string(t);
        }
        
        template <class T>
        std::string convert_str_impl(T const &, bad_conversion_tag_t)
        {
            static_assert(
                aux::never<T>::value
              , "Cannot convert type T to string"
            );
            return "";
        }
    }                                                       // namespace detail
    
    template <class T>
    std::string convert_to_string(T && t)
    {
        return detail::convert_str_impl(elib::forward<T>(t), conversion_tag<T>{});
    }
    
    template <class T>
    std::string to_str(T && t)
    {
        return detail::convert_str_impl(elib::forward<T>(t), conversion_tag<T>{});
    }
}}                                                           // namespace elib

namespace elib
{
    using converts::is_string_convertible;
    using converts::convert_to_string;
    using converts::to_str;
}                                                           // namespace elib

#endif /* ELIB_CONVERT_HPP */