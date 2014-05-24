#ifndef ELIB_AUX_TRAITS_INVOKE_OF_HPP
#define ELIB_AUX_TRAITS_INVOKE_OF_HPP

# include <elib/config.hpp>
# include <elib/aux/any_pod.hpp>
# include <elib/aux/declval.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/forward.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/none.hpp>
# include <elib/aux/traits/is_base_of.hpp>
# include <elib/aux/traits/is_same.hpp>
# include <elib/aux/traits/member_pointer_traits.hpp>
# include <elib/aux/traits/remove_reference.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class Func, class Obj>
        using is_invoke_base_of = is_base_of<
            typename member_pointer_traits<remove_ref_t<Func>>::class_type
          , remove_ref_t<Obj>
          >;
        
        ////////////////////////////////////////////////////////////////////////
        template <class ...Args>
        auto try_invoke(any_pod<>, Args&&...) -> none;
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class Func, class First, class ...Rest
          , ELIB_ENABLE_IF(is_member_function_pointer<remove_ref_t<Func>>::value)
          , ELIB_ENABLE_IF(is_invoke_base_of<Func, First>::value)
          >
        auto try_invoke(Func && fn, First && first, Rest &&... rest)
            -> decltype((elib::forward<First>(first).*fn)(elib::forward<Rest>(rest)...));
            
        ////////////////////////////////////////////////////////////////////////
        template <
            class Func, class First, class ...Rest
          , ELIB_ENABLE_IF(is_member_function_pointer<remove_ref_t<Func>>::value)
          , ELIB_ENABLE_IF(not is_invoke_base_of<Func, First>::value)
          >
        auto try_invoke(Func && fn, First && first, Rest &&... rest)
            -> decltype(((*elib::forward<First>(first)).*fn)(elib::forward<Rest>(rest)...));
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class Func, class First
          , ELIB_ENABLE_IF(is_member_object_pointer<remove_ref_t<Func>>::value)
          , ELIB_ENABLE_IF(is_invoke_base_of<Func, First>::value)
          >
        auto try_invoke(Func && fn, First && first)
            -> decltype(elib::forward<First>(first).*fn);
            
        ////////////////////////////////////////////////////////////////////////
        template <
            class Func, class First
          , ELIB_ENABLE_IF(is_member_object_pointer<remove_ref_t<Func>>::value)
          , ELIB_ENABLE_IF(is_invoke_base_of<Func, First>::value)
          >
        auto try_invoke(Func && fn, First && first)
            -> decltype((*elib::forward<First>(first)).*fn);
            
        ////////////////////////////////////////////////////////////////////////
        template <class Func, class ...Args>
        auto try_invoke(Func && fn, Args &&...args)
            -> decltype(elib::forward<Func>(fn)(elib::forward<Args>(args)...));
            
        
        template <class Func, class ...Args>
        struct invoke_impl
        {
            using type = decltype(
                try_invoke(elib::declval<Func>(), elib::declval<Args>()...)
              );
            
            using good = bool_<not is_same<type, none>::value>;
        };
        
        template <bool IsInvokeable, class Fn, class ...Args>
        struct invoke_of_impl
        {
            // false
        };
        
        template <class Fn, class ...Args>
        struct invoke_of_impl<true, Fn, Args...>
        {
            using type = typename invoke_impl<Fn, Args...>::type;
        };
    }                                                       // namespace detail

    template <class Fn, class ...Args>
    using is_invokable = typename detail::invoke_impl<Fn, Args...>::good;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class Fn, class ...Args>
    constexpr bool is_invokable_v = is_invokable<Fn, Args...>::value;
#   endif
        
    template <class Fn, class ...Args>
    struct invoke_of 
      : detail::invoke_of_impl<
            is_invokable<Fn, Args...>::value
          , Fn, Args...
          >
    {
    };
        
    template <class Fn, class ...Args>
    using invoke_of_t = typename invoke_of<Fn, Args...>::type;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_INVOKE_OF_HPP */