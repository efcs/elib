#ifndef ELIB_AUX_TUPLE_FWD_HPP
#define ELIB_AUX_TUPLE_FWD_HPP

# include <elib/aux/type_traits.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    template <class ...T>
    struct tuple;
    
    template <class T>
    struct tuple_size;
    
    template <class T>
    using tuple_size_t = typename tuple_size<T>::type;
    
    template <std::size_t I, class T>
    struct tuple_element;
    
    template <std::size_t I, class T>
    using tuple_element_t = typename tuple_element<I, T>::type;
    
    template <std::size_t I, class T>
    constexpr tuple_element_t<I, T>& get(T && t) noexcept;
    
    namespace tuple_detail
    {
        template <
            std::size_t I, class T
          , bool IsEmpty = is_empty<T>::value
# if defined(__clang__)
#   if __has_feature(is_final)
                           && !__is_final(T)
#   endif
# endif
        >
        struct tuple_item;
    
    }                                                       // namespace tuple_detail
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_FWD_HPP */