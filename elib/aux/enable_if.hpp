#ifndef ELIB_AUX_ENABLE_IF_HPP
#define ELIB_AUX_ENABLE_IF_HPP

# include <elib/aux/static_const.hpp>
# include <elib/aux/no_decay.hpp>

# define ELIB_ENABLE_IF(...)                                                \
  typename ::elib::aux::enable_if_c<static_cast<bool>(__VA_ARGS__)>::type* const& = \
    ::elib::aux::static_const<void*>::value
# 

# define ELIB_ENABLE_IF_VALID_EXPR(...)              \
  decltype(static_cast<void>(__VA_ARGS__))* const& = \
    ::elib::aux::static_const<void*>::value

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////
    // aux::enable_if_c
    template <bool Pred, class T = void>
    struct enable_if_c
    {
        using type = T;
    };

    template <class T>
    struct enable_if_c<false, T>
    {};

    template <bool Pred, class T = void>
    using enable_if_c_t = typename enable_if_c<Pred, T>::type;

    ////////////////////////////////////////////////////////////////////////
    // aux::enable_if, aux::enable_if_c
    template <class Pred, class T = void>
    using enable_if = enable_if_c<static_cast<bool>(Pred::type::value), T>;

    template <class Pred, class T = void>
    using enable_if_t = typename enable_if<Pred, T>::type;

    ////////////////////////////////////////////////////////////////////////
    // aux::lazy_enable_if, aux::lazy_enable_if_c
    template <class Pred, class T = no_decay<void>>
    using lazy_enable_if = enable_if_t<Pred, T>;

    template <class Pred, class T = no_decay<void>>
    using lazy_enable_if_t = typename enable_if_t<Pred, T>::type;

    template <bool Pred, class T = no_decay<void>>
    using lazy_enable_if_c = enable_if_c_t<Pred, T>;

    template <bool Pred, class T = no_decay<void>>
    using lazy_enable_if_c_t = typename enable_if_c_t<Pred, T>::type;

    ////////////////////////////////////////////////////////////////////////
    // aux::disable_if, aux::disable_if_c
    template <class Pred, class T = void>
    using disable_if = enable_if_c<!static_cast<bool>(Pred::type::value), T>;

    template <class Pred, class T = void>
    using disable_if_t = typename 
        enable_if_c<!static_cast<bool>(Pred::type::value), T>::type;

    template <bool Pred, class T = void>
    using disable_if_c = enable_if_c<!Pred, T>;

    template <bool Pred, class T = void>
    using disable_if_c_t = typename enable_if_c<!Pred, T>::type;

    ////////////////////////////////////////////////////////////////////////
    // aux::lazy_disable_if, aux::lazy_disable_if_c
    template <class Pred, class T = no_decay<void>>
    using lazy_disable_if = disable_if_t<Pred, T>;

    template <class Pred, class T = no_decay<void>>
    using lazy_disable_if_t = typename disable_if_t<Pred, T>::type;

    template<bool Pred, class T = no_decay<void>>
    using lazy_disable_if_c = disable_if_c_t<Pred, T>;

    template <bool Pred, class T = no_decay<void>>
    using lazy_disable_if_c_t = typename disable_if_c_t<Pred, T>::type;
}}                                                          // namespace elib
namespace elib
{
    using aux::enable_if;
    using aux::enable_if_t;
    using aux::enable_if_c;
    using aux::enable_if_c_t;
    
    using aux::disable_if;
    using aux::disable_if_t;
    using aux::disable_if_c;
    using aux::disable_if_c_t;
    
    using aux::lazy_enable_if;
    using aux::lazy_enable_if_t;
    using aux::lazy_enable_if_c;
    using aux::lazy_enable_if_c_t;
    
    using aux::lazy_disable_if;
    using aux::lazy_disable_if_t;
    using aux::lazy_disable_if_c;
    using aux::lazy_disable_if_c_t;
}                                                           // namespace elib
#endif /* ELIB_AUX_ENABLE_IF_HPP */