#ifndef ELIB_AUX_TRAITS_IS_STREAMABLE_HPP
#define ELIB_AUX_TRAITS_IS_STREAMABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/is_input_streamable.hpp>
# include <elib/aux/traits/is_output_streamable.hpp>

namespace elib { namespace aux
{
    namespace traits
    {
        template <class T>
        using is_streamable = elib::bool_<
            is_input_streamable<T>::value
            && is_output_streamable<T>::value
          >;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_streamable_v = is_streamable<T>::value;
# endif /* ELIB_CONFIG_HAS_VARIABLE_TEMPLATES */
    }
    
    using namespace traits;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_STREAMABLE_HPP */