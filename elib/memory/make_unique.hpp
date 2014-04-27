#ifndef ELIB_MEMORY_MAKE_UNIQUE_HPP
#define ELIB_MEMORY_MAKE_UNIQUE_HPP

# include <elib/aux/forward.hpp>
# include <memory>
# include <cstddef>

namespace elib { namespace memory
{
    namespace detail
    {
        template <class T> 
        struct unique_if 
        {
            using single_object = std::unique_ptr<T>;
        };
        
        template <class T>
        struct unique_if<T[]>
        {
            using unknown_bound = std::unique_ptr<T[]>;
        };
        
        template <class T, std::size_t N>
        struct unique_if<T[N]>
        {
            using known_bound = void;
        };
    }                                                       // namespace detail
    
    template <class T, class... Args>
    typename detail::unique_if<T>::single_object
    make_unique(Args&&... args) 
    {
        return std::unique_ptr<T>(new T(elib::forward<Args>(args)...));
    }
    
    template <class T>
    typename detail::unique_if<T>::unknown_bound
    make_unique(size_t n)
    {
        using U = typename aux::remove_extent<T>::type;
        return std::unique_ptr<T>(new U[n]());
    }
    
    template <class T, class... Args>
    typename detail::unique_if<T>::known_bound
    make_unique(Args&&...) = delete;  
}}                                                           // namespace elib
namespace elib
{
    using memory::make_unique;
}                                                           // namespace elib
#endif /* ELIB_MEMORY_MAKE_UNIQUE_HPP */