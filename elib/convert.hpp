#ifndef ELIB_CONVERT_HPP
#define ELIB_CONVERT_HPP

# include <elib/aux.hpp>
# include <iostream>
# include <sstream>
# include <string>

namespace elib { namespace converts
{
    
    constexpr struct string_convert_tag_t
    {
        using type = string_convert_tag_t;
    } 
    string_convert_tag {};
    
    constexpr struct stream_tag_t 
    {
        using type = stream_tag_t;
    } 
    stream_tag {};
    
    constexpr struct to_string_tag_t 
    {
        using type = to_string_tag_t;
    } 
    to_string_tag {};
    
    
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////////
        template <
            class From, class To
        , ELIB_ENABLE_IF_VALID_EXPR( static_cast<To>(elib::declval<From>()) )
        >
        constexpr bool has_conversion_impl(int) noexcept
        {
            return true;
        }
        
        template <class From, class To>
        constexpr bool has_conversion_impl(long) noexcept
        {
            return false;
        }
        
        
        ////////////////////////////////////////////////////////////////////////////
        template <
            class T
        , ELIB_ENABLE_IF_VALID_EXPR( to_string(elib::declval<T>()) )
        >
        constexpr bool has_to_string_impl(int) noexcept
        { 
            return true; 
        }
        
        template <class T>
        constexpr bool has_to_string_impl(long) noexcept
        { 
            return false; 
        }
        
        ////////////////////////////////////////////////////////////////////////////
        template <
            class T
        , ELIB_ENABLE_IF_VALID_EXPR(
            operator<<( elib::declval<std::ostream>(), elib::declval<T>() ) 
            )
        >
        constexpr bool has_stream_insertion_impl(int) noexcept
        { 
            return true; 
        }
        
        template <class T>
        constexpr bool has_stream_insertion_impl(long) noexcept
        { 
            return false;
        }
    }                                                       // namespace detail
    
    template <class From, class To>
    using has_conversion = elib::bool_<detail::has_conversion_impl<From, To>(0)>;
    
    template <class T>
    using has_string_conversion = elib::bool_<detail::has_conversion_impl<T, std::string>(0)>;
    
    template <class T>
    using has_stream_insertion = elib::bool_<detail::has_stream_insertion_impl<T>(0)>;
    
    template <class T>
    using has_to_string = elib::bool_<detail::has_to_string_impl<T>(0)>;
    
   
    
}}                                                           // namespace elib
#endif /* ELIB_CONVERT_HPP */