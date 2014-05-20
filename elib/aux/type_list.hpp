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

}}                                                          // namespace elib
#endif /* ELIB_AUX_TYPE_VECTOR_HPP */