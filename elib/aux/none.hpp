#ifndef ELIB_AUX_NONE_HPP
#define ELIB_AUX_NONE_HPP

# include <elib/aux/integral_constant.hpp>

namespace elib 
{
    namespace aux
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
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_NONE_HPP */