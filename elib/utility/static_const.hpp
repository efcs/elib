#ifndef ELIB_UTILITY_STATIC_CONST_HPP
#define ELIB_UTILITY_STATIC_CONST_HPP

/* for use with ELIB_ENABLE_IF and ELIB_ENABLE_IF_VALID_EXPR in
 * <elib/utility/type_traits.hpp>
 */
# define ELIB_ENABLER_TYPE void* const&
# define ELIB_ENABLER ::elib::utility::enabler

namespace elib 
{
    namespace utility
    {
        template <class T>
        struct static_const
        {
            static constexpr T value{};
        };
        
        template <class T>
        constexpr T static_const<T>::value;
        
        namespace 
        {
            constexpr void *const &enabler = utility::static_const<void*>::value;
        }
    }                                                       // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_STATIC_CONST_HPP */