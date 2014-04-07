#ifndef ELIB_AUX_TYPE_VECTOR_HPP
#define ELIB_AUX_TYPE_VECTOR_HPP

# include <elib/aux/integral_constant.hpp>

namespace elib { namespace aux
{
    template <class ...Args>
    struct type_vector
    {
        using type = type_vector;
    };
    
    template <class T>
    struct is_type_vector : elib::false_ {};
    
    template <class ...Args>
    struct is_type_vector<type_vector<Args...>> : elib::true_ {};
}}                                                          // namespace elib
#endif /* ELIB_AUX_TYPE_VECTOR_HPP */