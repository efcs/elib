#ifndef ELIB_AUX_TRAITS_SFINAE_COMMON_TYPE_HPP
#define ELIB_AUX_TRAITS_SFINAE_COMMON_TYPE_HPP

# include <elib/aux/always.hpp>
# include <elib/aux/declval.hpp>
# include <elib/aux/traits/conditional.hpp>
# include <elib/aux/traits/decay.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T, class U>
        using common_type_two = decltype(
            elib::declval<bool>() ? elib::declval<T>() : elib::declval<U>()
          );
        
        template <class First, class ...Rest>
        struct common_type_impl
        {
        };
        
        template <class T>
        struct common_type_impl<void, T>
        {
            using type = decay_t<T>;
        };
        
        template <class T, class U, class ...Rest>
        struct common_type_impl<always_void<common_type_two<T, U>>, T, U, Rest...>
          : common_type_impl<void, common_type_two<T, U>, Rest...>
        {
        };
    }                                                       // namespace detail

    template <class ...Types>
    struct sfinae_common_type
      : detail::common_type_impl<void, Types...>
    {};
        
    template <class ...Types>
    using sfinae_common_type_t = typename sfinae_common_type<Types...>::type;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_SFINAE_COMMON_TYPE_HPP */