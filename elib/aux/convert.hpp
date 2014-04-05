#ifndef ELIB_AUX_CONVERT_HPP
#define ELIB_AUX_CONVERT_HPP

# include <elib/aux/declval.hpp>
# include <elib/aux/forward.hpp>
# include <elib/aux/enable_if.hpp>

namespace elib { namespace aux
{
    template <class T>
    struct converter
    {
        explicit constexpr converter(T v)
          : m_value(v)
        {}
        
        template <
            class U, 
            ELIB_ENABLE_IF_VALID_EXPR(
                static_cast<U>( elib::forward<T>(elib::declval<T>()) )
              )
          >
        operator U() 
        {
            return static_cast<U>(elib::forward<T>(m_value));
        }
        
    private:
        T m_value;
    };
    
    template <class T>
    converter<T> convert(T && v)
    {
        return converter<T>(elib::forward<T>(v));
    }
}}                                                          // namespace elib
namespace elib
{
    using aux::convert;
}                                                           // namespace elib
#endif /* ELIB_AUX_CONVERT_HPP */