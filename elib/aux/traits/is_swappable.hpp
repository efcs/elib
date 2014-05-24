#ifndef ELIB_AUX_TRAITS_IS_SWAPPABLE_HPP
#define ELIB_AUX_TRAITS_IS_SWAPPABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/declval.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/traits/is_array.hpp>
# include <elib/aux/traits/is_same.hpp>
# include <elib/aux/traits/is_move_assignable.hpp>
# include <elib/aux/traits/is_move_constructible.hpp>
# include <elib/aux/traits/uncvref.hpp>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    namespace traits
    {
        namespace traits_adl_barrier
        {
            template <
                class T, std::size_t N
              , ELIB_ENABLE_IF(is_move_assignable<T>::value)
              , ELIB_ENABLE_IF(is_move_constructible<T>::value)
              >
            elib::true_ try_array_swap(T (&)[N], T (&)[N]);
            
            template <class T, class U>
            elib::false_ try_array_swap(T &&, U &&);
            
            template <class T, class U>
            using is_array_swappable = decltype(
                traits_adl_barrier::try_array_swap(
                    elib::declval<T>(), elib::declval<U>()
                  )
              );
            
            template <
                class T, class U
              , ELIB_ENABLE_IF_VALID_EXPR(
                  swap(declval<T &>(), declval<U &>())
                )
              >
            elib::true_ is_swappable_impl(int);
            
            template <
                class T, class U
              , ELIB_ENABLE_IF(not aux::is_array<uncvref<T>>::value)
              , ELIB_ENABLE_IF(aux::is_same<T, U>::value)
              , ELIB_ENABLE_IF(aux::is_move_assignable<T>::value)
              , ELIB_ENABLE_IF(aux::is_move_constructible<T>::value)
              >
            elib::true_ is_swappable_impl(long);
            
            template <
                class T, class U
              , ELIB_ENABLE_IF(aux::is_array<uncvref<T>>::value)
              , ELIB_ENABLE_IF(is_array_swappable<T, U>::value)
              >
            elib::true_ is_swappable_impl(long);
            
            template <class, class>
            elib::false_ is_swappable_impl(...);
            
            namespace swap_barrier
            {
                using std::swap;
                
                template <
                    class T, class U
                , bool = decltype(is_swappable_impl<T, U>(0))::value
                >
                struct is_nothrow_swappable_impl
                {
                    using type = false_;
                };
                
                template <class T, class U>
                struct is_nothrow_swappable_impl<T, U, true>
                {
                    using type = elib::bool_<
                        noexcept( swap(declval< T&>(), declval<U &>()) )
                    >;
                };
            }                                         // namespace swap_barrier
            
            using swap_barrier::is_nothrow_swappable_impl;
        }                                       // namespace traits_adl_barrier
        
        template <class T, class U = T>
        using is_swappable = decltype(
            traits_adl_barrier::is_swappable_impl<T, U>(0)
          );
        
        template <class T, class U = T>
        using is_nothrow_swappable = typename 
            traits_adl_barrier::is_nothrow_swappable_impl<T, U>::type;
            
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T, class U = T>
        constexpr bool is_swappable_v = is_swappable<T, U>::value;
        
        template <class T, class U = T>
        constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T, U>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_SWAPPABLE_HPP */
