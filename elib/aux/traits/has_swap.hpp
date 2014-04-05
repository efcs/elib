#ifndef ELIB_AUX_TRAITS_HAS_SWAP_HPP
#define ELIB_AUX_TRAITS_HAS_SWAP_HPP

# include <elib/aux/integral_constant.hpp>
# include <utility>

namespace elib { namespace aux
{
    namespace traits
    {
        namespace traits_adl_barrier
        {
            using std::swap;
            
            template <
                class T
              , std::size_t = sizeof(
                    (swap(std::declval<T&>(), std::declval<T&>()), 0)
                )
              >
            elib::true_ has_swap_impl(int);
            
            template <class>
            elib::false_ has_swap_impl(long);
            
            
            template <class T, bool = decltype(has_swap_impl<T>(0))::value>
            struct has_noexcept_swap_impl
            {
                using type = false_;
            };
            
            template <class T>
            struct has_noexcept_swap_impl<T, true>
            {
                using type = elib::bool_<
                    noexcept( swap(std::declval<T&>(), std::declval<T&>()) )
                >;
            };
        }
        
        template <class T>
        using has_swap = decltype(traits_adl_barrier::has_swap_impl<T>(0));
        
        template <class T>
        using has_noexcept_swap = typename 
            traits_adl_barrier::has_noexcept_swap_impl<T>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_HAS_SWAP_HPP */
