#ifndef ELIB_MEMORY_MAKE_UNIQUE_HPP
#define ELIB_MEMORY_MAKE_UNIQUE_HPP

# include <elib/aux/always.hpp>
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
            static_assert(
                aux::never<T>::value
              , "make_unique forbids T[N]. please use T[]"
              );
        };
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, class... Args>
    typename detail::unique_if<T>::single_object
    make_unique(Args&&... args) 
    {
        return std::unique_ptr<T>(new T(elib::forward<Args>(args)...));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    typename detail::unique_if<T>::single_object
    make_unique_default_init() 
    {
        return std::unique_ptr<T>(new T);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    typename detail::unique_if<T>::unknown_bound
    make_unique(size_t n)
    {
        using U = typename aux::remove_extent<T>::type;
        return std::unique_ptr<T>(new U[n]());
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    typename detail::unique_if<T>::unknown_bound
    make_unique_default_init(size_t n)
    {
        using U = typename aux::remove_extent<T>::type;
        return std::unique_ptr<T>(new U[n]);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, class ...Args>
    typename detail::unique_if<T>::unknown_bound
    make_unique_value_init(size_t n, Args &&... args)
    {
        using U = typename aux::remove_extent<T>::type;
        return std::unique_ptr<T>(new U[n]{std::forward<Args>(args)...});
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, class ...Args>
    typename detail::unique_if<T>::unknown_bound
    make_unique_auto_size(Args &&... args)
    {
        using U = typename aux::remove_extent<T>::type;
        return std::unique_ptr<T>(
            new U[sizeof...(Args)]{ elib::forward<Args>(args)...}
          );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, class... Args>
    typename detail::unique_if<T>::known_bound
    make_unique(Args&&...) = delete;  
}}                                                           // namespace elib
namespace elib
{
    using memory::make_unique;
    using memory::make_unique_default_init;
    using memory::make_unique_value_init;
    using memory::make_unique_auto_size;
}                                                           // namespace elib
#endif /* ELIB_MEMORY_MAKE_UNIQUE_HPP */