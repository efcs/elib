#ifndef ELIB_AUX_META_HPP
#define ELIB_AUX_META_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/support.hpp>

# define ELIB_ENABLE_IF(...)                                                \
  typename ::elib::aux::enable_if_c<static_cast<bool>(__VA_ARGS__)>::type* const& = \
    ::elib::aux::static_const<void*>::value
# 
# 
# define ELIB_ENABLE_IF_VALID_EXPR(...)              \
  decltype(static_cast<void>(__VA_ARGS__))* const& = \
    ::elib::aux::static_const<void*>::value
# 
# 
# define ELIB_AUX_LEFT_ASSOC_EXPR(Entry, Impl, Op)                        \
    template <bool Done, class ValType, ValType Val>                      \
    struct Impl                                                           \
    {                                                                     \
        template <class ...Empty>                                         \
        struct apply : ::elib::integral_constant<ValType, Val> {};        \
                                                                          \
        template <class A1>                                               \
        struct apply<A1> : ELIB_AUTO_INTC(Val Op A1::type::value) {};     \
                                                                          \
        template <class A1, class A2>                                     \
        struct apply<A1, A2>                                              \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value) {}; \
                                                                          \
        template <class A1, class A2, class A3>                           \
        struct apply<A1, A2, A3>                                          \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value) {};                    \
                                                                          \
        template <class A1, class A2, class A3, class A4>                 \
        struct apply<A1, A2, A3, A4>                                      \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value) {}; \
                                                                          \
        template <class A1, class A2, class A3, class A4, class A5>       \
        struct apply<A1, A2, A3, A4, A5>                                  \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value) {};                    \
                                                                          \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5, class A6    \
        >                                                                 \
        struct apply<A1, A2, A3, A4, A5, A6>                              \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value Op A6::type::value) {}; \
                                                                          \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5              \
          , class A6, class A7                                            \
        >                                                                 \
        struct apply<A1, A2, A3, A4, A5, A6, A7>                          \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value Op A6::type::value      \
                               Op A7::type::value) {};                    \
                                                                          \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5              \
          , class A6, class A7, class A8                                  \
        >                                                                 \
        struct apply<A1, A2, A3, A4, A5, A6, A7, A8>                      \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value Op A6::type::value      \
                               Op A7::type::value Op A8::type::value) {}; \
                                                                          \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5              \
          , class A6, class A7, class A8, class A9                        \
        >                                                                 \
        struct apply<A1, A2, A3, A4, A5, A6, A7, A8, A9>                  \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value Op A6::type::value      \
                               Op A7::type::value Op A8::type::value      \
                               Op A9::type::value)  {};                   \
    };                                                                    \
                                                                          \
    template <class ValType, ValType Val>                                 \
    struct Impl<false, ValType, Val>                                      \
    {                                                                     \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5              \
          , class A6, class A7, class A8, class A9, class A10             \
          , class ...Rest                                                 \
        >                                                                 \
        using apply = typename                                            \
            Impl<                                                         \
                sizeof...(Rest) < 10                                      \
              , decltype(Val Op A1::type::value Op A2::type::value        \
                             Op A3::type::value Op A4::type::value        \
                             Op A5::type::value Op A6::type::value        \
                             Op A7::type::value Op A8::type::value        \
                             Op A9::type::value Op A10::type::value)      \
              , Val Op A1::type::value Op A2::type::value                 \
                    Op A3::type::value Op A4::type::value                 \
                    Op A5::type::value Op A6::type::value                 \
                    Op A7::type::value Op A8::type::value                 \
                    Op A9::type::value Op A10::type::value                \
            >::template apply<Rest...>;                                   \
    };                                                                    \
                                                                          \
    template <class T, class ...Rest>                                     \
    using Entry = typename                                                \
        Impl<                                                             \
            sizeof...(Rest) < 10                                          \
          , typename T::type::value_type                                  \
          , T::type::value                                                \
        >::template apply<Rest...>::type
# 

namespace elib 
{ 
    namespace aux
    {
        ///////////////////////////////////////////////////////////////////////
        // apply
        template <class T, class ...Args>
        using apply_ = typename T::template apply<Args...>;

        template <class T, class ...Args>
        using apply_t = typename T::template apply<Args...>::type;

        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using type_t = typename T::type;

        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        struct no_decay { using type = T; };

        ////////////////////////////////////////////////////////////////////////
        //
        struct none {};

        template <class T>
        struct is_none : false_ {};

        template <>
        struct is_none< none > : true_ {};
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class ...Args>
        struct not_defined;

        
        ////////////////////////////////////////////////////////////////////////
        //
        namespace detail
        {
            template <class Always, class ...Ignored>
            struct _always
            {
                using type = Always;
            };
        }                                                   // namespace detail

        template <class ...T>
        using always = typename aux::detail::_always<true_, T...>::type;

        template <class ...T>
        using never = typename aux::detail::_always<false_, T...>::type;

        template <class ...T>
        using always_void = typename aux::detail::_always<void, T...>::type;
    }                                                       // namespace aux
    
    namespace aux 
    {
        ////////////////////////////////////////////////////////////////////////////
        // aux::if_c
        template <bool Pred, class Then, class Else>
        struct if_c;
        
        template <class Then, class Else>
        struct if_c<true, Then, Else>
        {
            using type = Then;
        };
        
        template <class Then, class Else>
        struct if_c<false, Then, Else>
        {
            using type = Else;
        };
        
        ////////////////////////////////////////////////////////////////////////////
        // aux::if_c_t
        template <bool Pred, class Then, class Else>
        using if_c_t = typename if_c<Pred, Then, Else>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // aux::if_
        template <class Pred, class Then, class Else>
        struct if_ : if_c<static_cast<bool>(Pred::type::value), Then, Else> {};
        
        ////////////////////////////////////////////////////////////////////////////
        // aux::if_t
        template <class Pred, class Then, class Else>
        using if_t = typename if_c<static_cast<bool>(Pred::type::value), Then, Else>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // aux::eval_if
        template <class Pred, class Then, class Else>
        struct eval_if
        {
            using type = typename if_t<Pred, Then, Else>::type;
        };
        
        ////////////////////////////////////////////////////////////////////////////
        // aux::eval_if_t
        template <class Pred, class Then, class Else>
        using eval_if_t = typename if_t<Pred, Then, Else>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // aux::eval_if_c
        template <bool Pred, class Then, class Else>
        struct eval_if_c
        {
            using type = typename if_c_t<Pred, Then, Else>::type;
        };
        
        ////////////////////////////////////////////////////////////////////////////
        // aux::eval_if_c_t
        template <bool Pred, class Then, class Else>
        using eval_if_c_t = typename if_c_t<Pred, Then, Else>::type;
        
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
        
    }                                                       // namespace aux
    
    using aux::if_;
    using aux::if_t;
    using aux::if_c;
    using aux::if_c_t;
    
    using aux::eval_if;
    using aux::eval_if_t;
    using aux::eval_if_c;
    using aux::eval_if_c_t;
    
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
    
    namespace aux
    {
        namespace detail
        {
            template <class ...Args>
            true_ fast_and_impl(Args*...);
        
            false_ fast_and_impl(...);
        
            template <class ...Args>
            false_ fast_or_impl(Args*...);
        
            true_ fast_or_impl(...);
        }                                                       // namespace detail

        ////////////////////////////////////////////////////////////////////////////
        // fast_and
        template <class ...Preds>
        using fast_and = decltype( 
            detail::fast_and_impl(if_t<Preds, int*, int>{}...) 
        );

        template <bool ...Preds>
        using fast_and_c = decltype(
            detail::fast_and_impl(if_c_t<Preds, int*, int>{}...)
        );

        ////////////////////////////////////////////////////////////////////////////
        // fast_or
        template <class ...Preds>
        using fast_or = decltype(
            detail::fast_or_impl(if_t<Preds, int, int*>{}...)
        );

        template <bool ...Preds>
        using fast_or_c = decltype(
            detail::fast_or_impl(if_c_t<Preds, int, int*>{}...)
        );
        
        ////////////////////////////////////////////////////////////////////////
        // not_
        template <class T>
        struct not_ : bool_<!T::type::value> {};

        //TODO
        // Should I allow narrowing conversions? 
        template <long long V>
        struct not_c : bool_<!V> {};
        
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            // and_impl
            template <bool Done>
            struct and_impl;

            template <>
            struct and_impl<true>
            {
                template <bool Last, class Head, class ...Tail>
                struct apply;

                template <class Head, class ...Tail>
                struct apply<true, Head, Tail...>
                {
                    using type = true_;
                    using which = none;
                };

                template <class Head, class ...Tail>
                struct apply<false, Head, Tail...>
                {
                    using type = false_;
                    using which = Head;
                };
            };

            template <>
            struct and_impl<false>
            {
                template <bool Last, class Head, class Next, class ...Tail>
                using apply = typename 
                    and_impl<sizeof...(Tail) == 0 || !Next::type::value>
                    ::template apply<
                        static_cast<bool>(Next::type::value)
                        , Next, Tail...
                    >;
            };
        }                                                       // namespace detail
        
        ///////////////////////////////////////////////////////////////////////
        // and_
        template <class A0, class A1, class ...As>
        struct and_ 
        : detail::and_impl< !static_cast<bool>(A0::type::value) >
            ::template apply<static_cast<bool>(A0::type::value), A0, A1, As...>::type
        {
            using type = and_;

            using result = typename
                detail::and_impl< !static_cast<bool>(A0::type::value) >
                ::template apply<static_cast<bool>(A0::type::value), A0, A1, As...>;

            using which = typename result::which;
        };
        
        ////////////////////////////////////////////////////////////////////////////
        // and_c
        template <bool B1, bool B2, bool ...Rest>
        using and_c = fast_and_c<B1, B2, Rest...>;
        
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            // or_impl
            template <bool Done>
            struct or_impl;

            template <>
            struct or_impl<true>
            {
                template <bool Last, class Head, class ...Tail>
                struct apply;

                template <class Head, class ...Tail>
                struct apply<true, Head, Tail...>
                {
                    using type = true_;
                    using which = none;
                };

                template <class Head, class ...Tail>
                struct apply<false, Head, Tail...>
                {
                    using type = false_;
                    using which = Head;
                };
            };

            template <>
            struct or_impl<false>
            {
                template <bool Last, class Head, class Next, class ...Tail>
                using apply = typename
                    or_impl< sizeof...(Tail) == 0 || Next::type::value >
                    ::template apply< 
                        static_cast<bool>(Next::type::value)
                    , Next, Tail...
                    >;
            };
        }                                                   // namespace detail

        ////////////////////////////////////////////////////////////////////////
        // or_
        template <class A0, class A1, class ...As>
        struct or_ 
        : detail::or_impl<static_cast<bool>(A0::type::value)>
            ::template apply<static_cast<bool>(A0::type::value), A0, A1, As...>::type
        {
            using type = or_;

            using result = typename
                detail::or_impl<static_cast<bool>(A0::type::value)>
                ::template apply<static_cast<bool>(A0::type::value), A0, A1, As...>;

            using which = typename result::which;
        };
        
        ////////////////////////////////////////////////////////////////////////////
        // or_c
        template <bool B0, bool B1, bool ...Rest>
        using or_c = fast_or_c<B0, B1, Rest...>;
    }                                                       // namespace aux
    
    using aux::not_;
    using aux::not_c;
    using aux::and_;
    using aux::and_c;
    using aux::or_;
    using aux::or_c;
    
    namespace aux
    {
        namespace detail
        {
            ELIB_AUX_LEFT_ASSOC_EXPR(add_apply, add_impl, +);
            ELIB_AUX_LEFT_ASSOC_EXPR(subtract_apply, subtract_impl, -);
            ELIB_AUX_LEFT_ASSOC_EXPR(multiply_apply, multiply_impl, *);
            ELIB_AUX_LEFT_ASSOC_EXPR(divide_apply, divide_impl, /);
        }                                                       // namespace detail
        
        ////////////////////////////////////////////////////////////////////////////
        template <class T>
        struct negate : ELIB_AUTO_INTC(- T::type::value ) {};
        
        template <class T>
        using negate_t = ELIB_AUTO_INTC( - T::type::value );

        ////////////////////////////////////////////////////////////////////////////
        template <class A0, class A1, class ...Args>
        struct add : detail::add_apply<A0, A1, Args...> {};
        
        template <class A0, class A1, class ...Args>
        using add_t = typename detail::add_apply<A0, A1, Args...>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // subtract
        template <class A0, class A1, class ...Args>
        struct subtract : detail::subtract_apply<A0, A1, Args...> {};
        
        template <class A0, class A1, class ...Args>
        using subtract_t = typename detail::subtract_apply<A0, A1, Args...>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // multiply
        template <class A0, class A1, class ...Args>
        struct multiply : detail::multiply_apply<A0, A1, Args...> {};
        
        template <class A0, class A1, class ...Args>
        using multiply_t = typename detail::multiply_apply<A0, A1, Args...>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // divide
        template <class A0, class A1, class ...Args>
        struct divide : detail::divide_apply<A0, A1, Args...> {};
        
        template <class A0, class A1, class ...Args>
        using divide_t = typename detail::divide_apply<A0, A1, Args...>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // modulus
        template <class T, class U>
        struct modulus : ELIB_AUTO_INTC( T::type::value % U::type::value ) {};
        
        template <class T, class U>
        using modulus_t = ELIB_AUTO_INTC( T::type::value % U::type::value );
    
        ////////////////////////////////////////////////////////////////////////////
        // increment
        template <class T>
        using increment = integral_constant< typename T::value_type, T::value + 1 >;
        
        template <class T>
        using increment_t = increment<T>;
        
        template <class T>
        using decrement = integral_constant< typename T::value_type, T::value - 1 >;
        
        template <class T>
        using decrement_t = decrement<T>;
    }                                                       // namespace aux
    
    namespace aux
    {
        namespace detail
        {
            ELIB_AUX_LEFT_ASSOC_EXPR(bitand_apply, bitand_impl, &);
            ELIB_AUX_LEFT_ASSOC_EXPR(bitor_apply, bitor_impl, |);
            ELIB_AUX_LEFT_ASSOC_EXPR(bitxor_apply, bitxor_impl, ^);
        }                                                       // namespace detail

        ////////////////////////////////////////////////////////////////////////////
        // bitnegate_
        template <class T>
        struct bitnegate_ : ELIB_AUTO_INTC( ~ T::type::value ) {};
        
        template <class T>
        using bitnegate_t = ELIB_AUTO_INTC( ~ T::type::value );
        
        ////////////////////////////////////////////////////////////////////////////
        // bitand_
        template <class A0, class A1, class ...Args>
        struct bitand_ : detail::bitand_apply<A0, A1, Args...> {};
        
        template <class A0, class A1, class ...Args>
        using bitand_t = typename detail::bitand_apply<A0, A1, Args...>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // bitor_
        template <class A0, class A1, class ...Args>
        struct bitor_ : detail::bitor_apply<A0, A1, Args...> {};
        
        template <class A0, class A1, class ...Args>
        using bitor_t = typename detail::bitor_apply<A0, A1, Args...>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // bitxor_
        template <class A0, class A1, class ...Args>
        struct bitxor_ : detail::bitxor_apply<A0, A1, Args...> {};
        
        template <class A0, class A1, class ...Args>
        using bitxor_t = typename detail::bitxor_apply<A0, A1, Args...>::type;
        
        ////////////////////////////////////////////////////////////////////////////
        // shift_left
        template <class T, class U>
        struct shift_left : ELIB_AUTO_INTC(T::type::value << U::type::value) {};
        
        template <class T, class U>
        using shift_left_t = ELIB_AUTO_INTC( T::type::value << U::type::value );
        
        ////////////////////////////////////////////////////////////////////////////
        // shift_right
        template <class T, class U>
        struct shift_right : ELIB_AUTO_INTC(( T::type::value >> U::type::value )) {};
        
        template <class T, class U>
        using shift_right_t = ELIB_AUTO_INTC(( T::type::value >> U::type::value ));
        
    }                                                     // namespace aux
    
    namespace aux
    {
        template <class LHS, class RHS>
        struct equal_to : bool_<LHS::type::value == RHS::type::value> {};
        
        template <class LHS, class RHS>
        struct not_equal_to : bool_<LHS::type::value != RHS::type::value> {};
        
        template <class LHS, class RHS>
        struct less : bool_<(LHS::type::value < RHS::type::value)> {};
        
        template <class LHS, class RHS>
        struct less_equal : bool_<(LHS::type::value <= RHS::type::value)> {};
        
        template <class LHS, class RHS>
        struct greater : bool_<(LHS::type::value > RHS::type::value)> {};
        
        template <class LHS, class RHS>
        struct greater_equal : bool_<(LHS::type::value >= RHS::type::value)> {};
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_META_HPP */