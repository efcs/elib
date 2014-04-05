#ifndef ELIB_AUX_TRAITS_IS_SWAPPABLE_HPP
#define ELIB_AUX_TRAITS_IS_SWAPPABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/declval.hpp>
# include <elib/aux/enable_if.hpp>
# include <utility>

namespace elib { namespace aux
{
    namespace traits
    {
        namespace traits_adl_barrier
        {
            using std::swap;
            
            template <
                class T, class U
              , ELIB_ENABLE_IF_VALID_EXPR(
                  swap(declval<T &>(), declval<U &>())
                )
              >
            elib::true_ is_swappable_impl(int);
            
            template <class, class>
            elib::false_ is_swappable_impl(long);
            
            
            template <
                class T, class U
              , bool = decltype(is_swappable_impl<T, U>(0))::value
            >
            struct is_noexcept_swappable_impl
            {
                using type = false_;
            };
            
            template <class T, class U>
            struct is_noexcept_swappable_impl<T, U, true>
            {
                using type = elib::bool_<
                    noexcept( swap(declval< T&>(), declval<U &>()) )
                >;
            };
        }                                       // namespace traits_adl_barrier
        
        template <class T, class U = T>
        using is_swappable = decltype(
            traits_adl_barrier::is_swappable_impl<T, U>(0)
          );
        
        template <class T, class U = T>
        using is_noexcept_swappable = typename 
            traits_adl_barrier::is_noexcept_swappable_impl<T, U>::type;
            
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T, class U = T>
        using is_swappable_v = is_swappable<T, U>::value;
        
        template <class T, class U = T>
        using is_noexcept_swappable_v = is_noexcept_swappable<T, U>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_SWAPPABLE_HPP */
