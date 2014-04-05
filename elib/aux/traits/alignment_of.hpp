#ifndef ELIB_AUX_TRAITS_ALIGNMENT_OF_HPP
#define ELIB_AUX_TRAITS_ALIGNMENT_OF_HPP

# include <elib/config.hpp>
# include <type_traits>
# include <cstddef>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::alignment_of;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr std::size_t alignment_of_v = alignment_of<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ALIGNMENT_OF_HPP */
