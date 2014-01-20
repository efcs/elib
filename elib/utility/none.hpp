#ifndef ELIB_UTILITY_NONE_HPP
#define ELIB_UTILITY_NONE_HPP

# include <elib/utility/integral_constant.hpp>

namespace elib 
{
    namespace utility
    {
        struct none {};
        
        template <class T>
        struct is_none 
          : false_
        {};
        
        template <>
        struct is_none< none >
          : true_
        {};
    }                                                       // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_NONE_HPP */