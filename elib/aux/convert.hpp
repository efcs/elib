#ifndef ELIB_AUX_CONVERT_HPP
#define ELIB_AUX_CONVERT_HPP

# include <elib/aux/declval.hpp>
# include <elib/aux/forward.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/traits/decay.hpp>
# include <elib/aux/traits/is_reference.hpp>

namespace elib { namespace aux
{
    template <class T>
    struct converter
    {
        static_assert(
            not aux::is_reference<T>::value
          , "T cannot be a reference"
          );
        
        explicit constexpr converter(T v)
          : m_value(elib::move(v))
        {}
        
        template <
            class U 
          , ELIB_ENABLE_IF_VALID_EXPR(static_cast<U>(elib::move(elib::declval<T>()) ))
          >
        operator U() 
        {
            return static_cast<U>(elib::move(m_value));
        }
        
        converter & operator=(converter const &) {}
        
    private:
        T m_value;
    };
    
    template <class T>
    converter<aux::decay_t<T>>
    convert(T && v)
    {
        return converter<aux::decay_t<T>>(elib::forward<T>(v));
    }
}}                                                          // namespace elib
namespace elib
{
    using aux::convert;
}                                                           // namespace elib
#endif /* ELIB_AUX_CONVERT_HPP */