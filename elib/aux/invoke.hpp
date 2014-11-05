#ifndef ELIB_AUX_INVOKE_HPP
#define ELIB_AUX_INVOKE_HPP

# include <elib/aux/auto_return.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/forward.hpp>
# include <elib/aux/integer_sequence.hpp>
# include <elib/aux/traits/decay.hpp>
# include <elib/aux/traits/is_base_of.hpp>
# include <elib/aux/traits/is_unpackable.hpp>
# include <elib/aux/traits/invoke_of.hpp>
# include <elib/aux/traits/member_pointer_traits.hpp>
# include <elib/aux/traits/remove_reference.hpp>
# include <utility> /* for std::get */
# include <tuple>
# include <cstddef>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    constexpr struct invoke_unpack_t { constexpr invoke_unpack_t() {} } invoke_unpack {};
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Func, class First, class ...Rest
      , ELIB_ENABLE_IF(is_member_function_pointer<remove_ref_t<Func>>::value)
      , ELIB_ENABLE_IF(detail::is_invoke_base_of<Func, First>::value)
        >
    constexpr auto invoke(Func && fn, First && first, Rest &&... rest)
    ELIB_AUTO_RETURN_NOEXCEPT(
        (elib::forward<First>(first).*fn)(elib::forward<Rest>(rest)...)
    )
            
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Func, class First, class ...Rest
      , ELIB_ENABLE_IF(is_member_function_pointer<remove_ref_t<Func>>::value)
      , ELIB_ENABLE_IF(not detail::is_invoke_base_of<Func, First>::value)
      >
    constexpr auto invoke(Func && fn, First && first, Rest &&... rest)
    ELIB_AUTO_RETURN_NOEXCEPT(
        ((*elib::forward<First>(first)).*fn)(elib::forward<Rest>(rest)...)
    )
        
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Func, class First
      , ELIB_ENABLE_IF(is_member_object_pointer<remove_ref_t<Func>>::value)
      , ELIB_ENABLE_IF(detail::is_invoke_base_of<Func, First>::value)
      >
    constexpr auto invoke(Func && fn, First && first)
    ELIB_AUTO_RETURN_NOEXCEPT(
        elib::forward<First>(first).*fn
    )
            
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Func, class First
      , ELIB_ENABLE_IF(is_member_object_pointer<remove_ref_t<Func>>::value)
      , ELIB_ENABLE_IF(not detail::is_invoke_base_of<Func, First>::value)
      >
    constexpr auto invoke(Func && fn, First && first)
    ELIB_AUTO_RETURN_NOEXCEPT(
        (*elib::forward<First>(first)).*fn
    )
            
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Func, class ...Args
      , ELIB_ENABLE_IF(aux::is_invokable<Func, Args...>::value)
      >
    constexpr auto invoke(Func && fn, Args &&...args)
    ELIB_AUTO_RETURN_NOEXCEPT(
        elib::forward<Func>(fn)(elib::forward<Args>(args)...)
    )

    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <class Func, class Pack, std::size_t... I>
        auto invoke_unpack_impl(Func && f, Pack && p, index_sequence<I...>)
        ELIB_AUTO_RETURN_NOEXCEPT(
            ::elib::aux::invoke(elib::forward<Func>(f), std::get<I>(elib::forward<Pack>(p))...)
        )
        
        template <class Pack, std::size_t... I>
        auto invoke_unpack_impl(Pack && p, index_sequence<I...>)
        ELIB_AUTO_RETURN_NOEXCEPT(
            ::elib::aux::invoke(std::get<I>(elib::forward<Pack>(p))...)
        )
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Func, class Pack
      , ELIB_ENABLE_IF(aux::is_unpackable<Pack>::value)
      >
    auto invoke(invoke_unpack_t, Func && f, Pack && p)
    ELIB_AUTO_RETURN_NOEXCEPT(
        detail::invoke_unpack_impl(
            elib::forward<Func>(f), elib::forward<Pack>(p)
          , aux::make_index_sequence<std::tuple_size<aux::decay_t<Pack>>::value>{}
        )
    )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Pack
      , ELIB_ENABLE_IF(aux::is_unpackable<Pack>::value)
      >
    auto invoke(invoke_unpack_t, Pack && p)
    ELIB_AUTO_RETURN_NOEXCEPT(
        detail::invoke_unpack_impl(
            elib::forward<Pack>(p)
          , aux::make_index_sequence<std::tuple_size<aux::decay_t<Pack>>::value>{}
        )
    )
    
}}                                                          // namespace elib
namespace elib
{
    using aux::invoke_unpack_t;
    using aux::invoke_unpack;
    using aux::invoke;
}                                                           // namespace elib
#endif /* ELIB_AUX_INVOKE_HPP */