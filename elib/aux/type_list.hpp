#ifndef ELIB_AUX_TYPE_LIST_HPP
#define ELIB_AUX_TYPE_LIST_HPP

# include <elib/aux/integral_constant.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    template <class ...Args>
    struct type_list
    {
        using type = type_list;
        using size = elib::integral_constant<std::size_t, sizeof...(Args)>;
    };
    
    template <class T>
    struct is_type_list : elib::false_ {};
    
    template <class ...Args>
    struct is_type_list<type_list<Args...>> : elib::true_ {};
}}                                                          // namespace elib
#endif /* ELIB_AUX_TYPE_VECTOR_HPP */