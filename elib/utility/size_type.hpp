#ifndef ELIB_SIZE_TYPE_HPP
#define ELIB_SIZE_TYPE_HPP


#include <cstddef>


namespace elib {
    

template <typename T, T NPOS = -1>
struct size_type_traits {
    typedef T type;
    typedef T size_type;
    static constexpr size_type npos = NPOS;
};


typedef size_type_traits<std::size_t> elib_size_type;
typedef typename elib_size_type::size_type elib_size_t;
    
    
} /* namespace elib */
#endif /* ELIB_SIZE_TYPE_HPP */