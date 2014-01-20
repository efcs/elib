#ifndef ELIB_AUX_GET_POINTER_HPP
#define ELIB_AUX_GET_POINTER_HPP

# include <elib/aux/move.hpp>
# include <memory>

namespace elib 
{
    namespace aux
    {
        template <class T>
        constexpr T* get_pointer(T* ptr) noexcept
        {
            return ptr;
        }
        
        template <class T>
        constexpr T* get_pointer(std::shared_ptr<T> const& ptr) 
            noexcept(noexcept(ptr.get()))
        {
            return ptr.get();
        }
        
        template <class T>
        constexpr T* get_pointer(std::unique_ptr<T> const& ptr)
            noexcept(noexcept(ptr.get()))
        {
            return ptr.get();
        }
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_GET_POINTER_HPP */