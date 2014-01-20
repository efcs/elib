#ifndef ELIB_AUX_TUPLE_FWD_HPP
#define ELIB_AUX_TUPLE_FWD_HPP

# include <cstddef>

namespace elib { namespace aux
{
    template <class ...T>
    struct tuple;
    
    template <class T>
    struct tuple_size;
    
    template <class T>
    using tuple_size_ = typename tuple_size<T>::type;
    
    template <std::size_t I, class T>
    struct tuple_element;
    
    template <std::size_t I, class T>
    using tuple_element_ = typename tuple_element<I, T>::type;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_FWD_HPP */