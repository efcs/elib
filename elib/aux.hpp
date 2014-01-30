#ifndef ELIB_AUX_HPP
#define ELIB_AUX_HPP
# 
# include <elib/config.hpp>
# include <elib/assert.hpp>
# include <type_traits>
# include <cstddef>
# 
# 
# /* ELIB_TODO can be used to locate TODO 's in code */
# if defined( ELIB_STATIC_ASSERT_TODO )
#   define ELIB_TODO(str) static_assert(! "ELIB TODO FOUND: ", str)
# elif defined( ELIB_ASSERT_TODO )
#   define ELIB_TODO(msg) ELIB_ASSERT(! "ELIB TODO", msg)
# elif defined( ELIB_WARN_TODO )
#   define ELIB_TODO(msg) ELIB_WARN(! "ELIB TODO", msg)
# elif defined( ELIB_THROW_TODO )
#   define ELIB_TODO(msg) throw "ELIB TODO " msg
# else
#   define ELIB_TODO(msg) ((void)0)
# endif
# 
# /* used to suppress unused warnings */
# define ELIB_UNUSED(x) ((void)x)
# 
# 
#  /* default constructor macro */
# define ELIB_DEFAULT_CLASS(Class)          \
  Class() = default;                        \
                                            \
  Class(const Class&) = default;            \
  Class(Class&&) = default;                 \
                                            \
  Class& operator=(const Class&) = default; \
  Class& operator=(Class&&) = default
# 
# 
# /* used to clearly have exposition for code we don't want to compile */
# define ELIB_EXPO(...) 
# 
# 
# /* type deduction macro for integral_constant */
# define ELIB_AUTO_INTC(...) \
    ::elib::integral_constant<decltype(__VA_ARGS__), __VA_ARGS__>
# 
# 
# // noexcept copy clause
# define ELIB_NOEXCEPT(...)                                            \
    noexcept(                                                          \
        decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
    )
# 
# 
# define ELIB_NOEXCEPT_2(...)                                          \
    noexcept((                                                         \
        decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
    ))
# 
# 
# // Implementation taken from eric_niebler proto-0x
# // Workaround for GCC not excepting "this" in noexcept clauses 
# // (just remove the noexcept clause until GCC gets their shit together)
# define ELIB_AUTO_RETURN_NOEXCEPT(...)                            \
  noexcept(noexcept(                                               \
    decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                      \
  {                                                                \
    return (__VA_ARGS__);                                          \
  }
#   
#   
# define ELIB_RETURN_NOEXCEPT(...)                                   \
  noexcept(noexcept(                                                 \
      decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
  ))                                                                 \
  {                                                                  \
    return (__VA_ARGS__);                                            \
  }
# 
# 
# define ELIB_AUTO_RETURN(...) \
    -> decltype(__VA_ARGS__)   \
    {                          \
        return (__VA_ARGS__);  \
    }                          
# 
# /* noexcept workaround for when "this" is used with GCC */
# if ELIB_WORKAROUND(ELIB_CONFIG_GNU, GCC_NOEXCEPT_THIS_BUG)
#   
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND(...) { return (__VA_ARGS__); }
#   
# else /* non-workaround support (same as AUTO_RETURN and RETURN) */
#   
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND ELIB_RETURN
# endif
/* thanks to Matt Calabrese for new style enable if 
* and eric neibler for macro impl
*/
# define ELIB_ENABLE_IF(...)                                              \
  typename ::std::enable_if<static_cast<bool>(__VA_ARGS__)>::type* const& = \
    ::elib::aux::static_const<void*>::value
# 
# 
# define ELIB_ENABLE_IF_VALID_EXPR(...)              \
  decltype(static_cast<void>(__VA_ARGS__))* const& = \
    ::elib::aux::static_const<void*>::value
#
/* for use with ELIB_ENABLE_IF and ELIB_ENABLE_IF_VALID_EXPR in
 * <elib/aux/type_traits.hpp>
 */
# define ELIB_ENABLER_TYPE void* const&
# define ELIB_ENABLER ::elib::aux::enabler
# 
# 
# define ELIB_AUX_LEFT_ASSOC_EXPR(Entry, Impl, Op)                        \
    template <bool Done, class ValType, ValType Val>                      \
    struct Impl                                                           \
    {                                                                     \
        template <class ...Empty>                                         \
        struct apply : ::elib::integral_constant<ValType, Val> {};   \
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

        
namespace elib
{
    ////////////////////////////////////////////////////////////////////////
    // forward
    template <class T>
    constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept
    { 
        return static_cast<T&&>(t);
    }

    template <class T>
    constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept
    {
        return static_cast<T &&>(t);
    }
        
    ////////////////////////////////////////////////////////////////////////
    // move
    template <class T>
    constexpr typename std::remove_reference<T>::type&& move(T&& t) noexcept
    {
        return static_cast<typename std::remove_reference<T>::type &&>(t);
    }
        
    ////////////////////////////////////////////////////////////////////////
    // move_if_noexcept
    template <class T> 
    constexpr 
        typename std::conditional<
            ! std::is_nothrow_move_constructible<T>::value 
            && std::is_copy_constructible<T>::value
          , const T&
          , T&&
        >::type
    move_if_noexcept(T& x) noexcept
    {
        return elib::move(x);
    }
        
    ////////////////////////////////////////////////////////////////////////
    // declval
    template <class T>
    typename std::add_rvalue_reference<T>::type 
    declval();
    
    ////////////////////////////////////////////////////////////////////////////
    // addressof
    template <class T>
    constexpr T* addressof(T& arg) noexcept
    {
        return reinterpret_cast<T*>(
                & const_cast<char &>(
                    reinterpret_cast<const volatile char &>(arg)
                ));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // integral_constant
    template <class T, T Val>
    struct integral_constant
    {
        using type = integral_constant;
        using value_type = T;
            
        static constexpr T value = Val;
            
        constexpr operator value_type() const noexcept
        { return Val; }
            
            constexpr T operator()() const noexcept
        { return Val; }
    };
    
    template <class T, T Val>
    constexpr T integral_constant<T, Val>::value;
    
    namespace aux
    {
        template <bool V>
        using bool_ = integral_constant<bool, V>;

        using true_ = bool_<true>;
        using false_ = bool_<false>;

        template <char V>
        using char_ = integral_constant<char, V>;
        
        template <short V>
        using short_ = integral_constant<short, V>;
        
        template <unsigned short V>
        using ushort_ = integral_constant<unsigned short, V>;

        template <int V>
        using int_ = integral_constant<int, V>;

        template <unsigned V>
        using uint_ = integral_constant<unsigned, V>;

        template <long V>
        using long_ = integral_constant<long, V>;

        template <unsigned long V>
        using ulong_ = integral_constant< unsigned long, V>;
        
        template <long long V>
        using llong_ = integral_constant<long long, V>;
        
        template <unsigned long long V>
        using ullong_ = integral_constant<unsigned long long, V>;
        
        template <std::size_t V>
        using size_type_ = integral_constant<std::size_t, V>;

        template <class To, class From>
        using intc_cast = integral_constant<To, static_cast<To>(From::type::value)>;

        template <class From>
        using bool_cast = integral_constant<bool, static_cast<bool>(From::type::value)>;
        
    }                                                       // namespace aux
    
    using aux::bool_;
    using aux::true_;
    using aux::false_;
    using aux::int_;
    using aux::size_type_;
    
    namespace aux
    {
        ////////////////////////////////////////////////////////////////////////
        //
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
        
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            // detail::any
            template <class Ignored = decltype(nullptr)>
            struct any
            {
                any() = default;

                template <typename T>
                constexpr any(T const &) noexcept
                {}

                template <class T>
                operator T &&() const noexcept;
            };
        }                                                   // namespace detail

        ////////////////////////////////////////////////////////////////////////
        // any
        using any = detail::any<>;

        ////////////////////////////////////////////////////////////////////////
        // any_pod
        template <class Ignored = decltype(nullptr)>
        struct any_pod
        {
            any_pod(...);
        };
        
        ////////////////////////////////////////////////////////////////////////
        //
# if __cplusplus < 201300
        template <class ...T>
        inline void swallow(T &&...) noexcept {}
# else
        template <class ...T>
        constexpr void swallow(T &&...) noexcept {}
# endif
        
        /////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        struct static_const
        { 
            static constexpr T value{}; 
        };
        
        template <class T>
        constexpr T static_const<T>::value;

        namespace 
        {
            constexpr void *const &enabler = static_const<void*>::value;
        }
        
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////////
            //
            template <class T>
            constexpr auto by_val_impl(T & t, int)
            ELIB_AUTO_RETURN_NOEXCEPT( T(t) )
            
            template <class T>
            constexpr auto by_val_impl(T const& t, int)
            ELIB_AUTO_RETURN_NOEXCEPT( T(t) )
            
            template <class T>
            constexpr auto by_val_impl(T && t, int)
            ELIB_AUTO_RETURN_NOEXCEPT( T(static_cast<T &&>(t)) )
            
            // TODO
            // does it make sense to have this? 
            template <class T>
            constexpr auto by_val_impl(T const& t, long)
            ELIB_AUTO_RETURN_NOEXCEPT(t)
        }                                                   // namespace detail
    
        ////////////////////////////////////////////////////////////////////////
        //
        struct by_val_
        {
            template <class T>
            constexpr auto operator()(T && t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                detail::by_val_impl(static_cast<T &&>(t), 1)
            )
        };
        
        constexpr const by_val_ by_val{};
        
        ////////////////////////////////////////////////////////////////////////
        //
        struct by_ref_
        {
            template <class T>
            constexpr T const& operator()(T && t) const noexcept
            { return t;}
        };
        
        constexpr const by_ref_ by_ref{};
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
        // aux::enable_if, aux::enable_if_c
        template <class Pred, class T = void>
        using enable_if = typename 
            std::enable_if<
                static_cast<bool>(Pred::type::value), T
            >::type;
            
        template <class Pred, class T = void>
        using enable_if_t = typename enable_if<Pred, T>::type;
        
        template <bool Pred, class T = void>
        using enable_if_c = std::enable_if<Pred, T>;
        
        template <bool Pred, class T = void>
        using enable_if_c_t = typename std::enable_if<Pred, T>::type;
        
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
        using disable_if = std::enable_if<!static_cast<bool>(Pred::type::value), T>;
        
        template <class Pred, class T = void>
        using disable_if_t = typename 
            std::enable_if<!static_cast<bool>(Pred::type::value), T>::type;
        
        template <bool Pred, class T = void>
        using disable_if_c = std::enable_if<!Pred, T>;
        
        template <bool Pred, class T = void>
        using disable_if_c_t = typename std::enable_if<!Pred, T>::type;
        
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
        
        ////////////////////////////////////////////////////////////////////////
        // aux::conditional
        using std::conditional;
        
        template <bool Pred, class Then, class Else>
        using conditional_t = typename conditional<Pred, Then, Else>::type;
        
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

        template <long V>
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
    
    namespace aux
    {
        
        template<class T, T ...Seq> 
        struct integer_sequence
        {
            using type = integer_sequence;
            
            using value_type = T;
            
            static constexpr T size = sizeof...(Seq);

            using next = integer_sequence<T, Seq..., sizeof...(Seq)>;
        };

        template<int... I>
        using int_sequence = integer_sequence<int, I...>;
        
        template<size_t... I>
        using index_sequence = integer_sequence<std::size_t, I...>;

        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            //
            template <class LHS, class RHS>
            struct integer_seq_join;
           
            template <class T, T ...Vs0, T ...Vs1>
            struct integer_seq_join<
                integer_sequence<T, Vs0...>
              , integer_sequence<T, Vs1...>
            >
            {
                using type = integer_sequence<T, Vs0..., (Vs1 + sizeof...(Vs0))...>;
            };
           
            //////////////////////////////////////////////////////////////////////
            //
            template <class T, std::size_t N>
            struct integer_seq_impl
              : integer_seq_join<
                    typename integer_seq_impl<T, (N / 2)>::type
                  , typename integer_seq_impl<T, (N - (N/2))>::type
                >
            {};
            
            template <class T>
            struct integer_seq_impl<T, 0>
            {
                using type = integer_sequence<T>;
            };
            
            template <class T>
            struct integer_seq_impl<T, 1>
            {
                using type = integer_sequence<T, 0>;
            };
        }                                                   // namespace detail
        
        ////////////////////////////////////////////////////////////////////////
        //
        template<class T, T N>
        using make_integer_sequence = typename 
            detail::integer_seq_impl<
                T
              , static_cast<std::size_t>(N)
            >::type;

        template<int N>
        using make_int_sequence = make_integer_sequence<int, N>;

        template<size_t N>
        using make_index_sequence = make_integer_sequence<std::size_t, N>;

        ////////////////////////////////////////////////////////////////////////
        //
        template<class... T>
        using to_int_sequence = make_int_sequence<sizeof...(T)>;

        template<class... T>
        using to_index_sequence = make_index_sequence<sizeof...(T)>;
        
    }                                                       // namespace aux
    
    namespace aux { namespace traits
    { 
        ////////////////////////////////////////////////////////////////////////
        // Primary Type Categories
        using std::is_void;
        using std::is_integral;
        using std::is_floating_point;
        using std::is_array;
        using std::is_enum;
        using std::is_union;
        using std::is_class;
        using std::is_function;
        using std::is_pointer;
        using std::is_lvalue_reference;
        using std::is_rvalue_reference;
        using std::is_member_object_pointer;
        using std::is_member_function_pointer;
        
        template <class T>
        using is_ptr = std::is_pointer<T>;
        
        template <class T>
        using is_lvalue_ref = std::is_lvalue_reference<T>;
        
        template <class T>
        using is_rvalue_ref = std::is_rvalue_reference<T>;
        
        template <class T>
        using is_mem_obj_ptr = std::is_member_object_pointer<T>;
        
        template <class T>
        using is_mem_fn_ptr = std::is_member_function_pointer<T>;
        
# if ELIB_CONFIG_CXX1Y || ELIB_CONFIG_CXX14
        using std::is_null_pointer;
        
        template <class T>
        using is_null_ptr = std::is_null_pointer<T>;
# endif
        
        ////////////////////////////////////////////////////////////////////////
        // Composite Type Categories
        using std::is_fundamental;
        using std::is_arithmetic;
        using std::is_scalar;
        using std::is_object;
        using std::is_compound;
        using std::is_reference;
        using std::is_member_pointer;
        
        template <class T>
        using is_ref = std::is_reference<T>;
        
        template <class T>
        using is_mem_ptr = std::is_member_pointer<T>;
        
        ////////////////////////////////////////////////////////////////////////
        // Type Information
        using std::is_const;
        using std::is_volatile;
        using std::is_trivial;
        
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        using std::is_trivially_copyable;
# endif
   
        using std::is_standard_layout;
        using std::is_pod;
        using std::is_literal_type;
        using std::is_empty;
        
        using std::is_polymorphic;
        using std::is_abstract;
        
        using std::is_signed;
        using std::is_unsigned;

        using std::is_constructible;
        using std::is_default_constructible;
        using std::is_copy_constructible;
        using std::is_move_constructible;
    
        using std::is_assignable;
        using std::is_copy_assignable;
        using std::is_move_assignable;
        
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        using std::is_trivially_constructible;
        using std::is_trivially_default_constructible;
        using std::is_trivially_copy_constructible;
        using std::is_trivially_move_constructible;
        
        using std::is_trivially_copy_assignable;
        using std::is_trivially_move_assignable;
# endif
        using std::is_nothrow_constructible;
        using std::is_nothrow_default_constructible;
        using std::is_nothrow_copy_constructible;
        using std::is_nothrow_move_constructible;
     
        using std::is_nothrow_copy_assignable;
        using std::is_nothrow_move_assignable;
        
        using std::is_destructible;
        using std::is_trivially_destructible;
        using std::is_nothrow_destructible;

        using std::has_virtual_destructor;
    
        using std::alignment_of;
        using std::rank;
        using std::extent;
        
        using std::is_same;
        using std::is_base_of;
        using std::is_convertible;

        ////////////////////////////////////////////////////////////////////////
        // aux::remove_const, aux::remove_volatile, aux::remove_cv
        using std::remove_const;
        using std::remove_volatile;
        using std::remove_cv;
        
        template <class T>
        using remove_const_t = typename remove_const<T>::type;
      
        template <class T>
        using remove_volatile_t = typename remove_volatile<T>::type;
       
        template <class T>
        using remove_cv_t = typename remove_cv<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const, aux::add_volatile, aux::add_cv
        using std::add_const;
        using std::add_volatile;
        using std::add_cv;

        template <class T>
        using add_const_t = typename add_const<T>::type;
        
        template <class T>
        using add_volatile_t = typename add_volatile<T>::type;
        
        template <class T>
        using add_cv_t = typename add_cv<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_reference
        using std::remove_reference;
        
        template <class T>
        using remove_reference_t = typename remove_reference<T>::type;
        
        template <class T>
        using remove_ref = remove_reference<T>;
        
        template <class T>
        using remove_ref_t = typename remove_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_const_ref, aux::remove_volatile_ref, aux::remove_cv_ref
        template <class T>
        using remove_const_ref = remove_const< remove_ref_t<T> >;
        
        template <class T>
        using remove_const_ref_t = remove_const_t< remove_ref_t<T> >;
        
        template <class T>
        using remove_volatile_ref = remove_volatile< remove_ref_t<T> >;
        
        template <class T>
        using remove_volatile_ref_t = remove_volatile_t< remove_ref_t<T> >;
        
        template <class T>
        using remove_cv_ref = remove_cv< remove_ref_t<T> >;
        
        template <class T>
        using remove_cv_ref_t = remove_cv_t< remove_ref_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::uncvref
        template <class T>
        using uncvref = remove_cv_t< remove_ref_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_lvalue_reference, aux::add_lvalue_ref
        using std::add_lvalue_reference;
        
        template <class T>
        using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
        
        template <class T>
        using add_lvalue_ref = add_lvalue_reference<T>;
        
        template <class T>
        using add_lvalue_ref_t = typename add_lvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_lvalue_ref, aux::add_volatile_lvalue_ref, aux::add_cv_lvalue_ref
        template <class T>
        using add_const_lvalue_ref = add_const< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_const_lvalue_ref_t = add_const_t< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_volatile_lvalue_ref = add_volatile< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_volatile_lvalue_ref_t = add_volatile_t< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_cv_lvalue_ref = add_cv< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_cv_lvalue_ref_t = add_cv_t< add_lvalue_ref_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_ref
        template <class T>
        using add_ref = add_lvalue_reference<T>;
        
        template <class T>
        using add_ref_t = typename add_lvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_ref, aux::add_volatile_ref, aux::add_cv_ref
        template <class T>
        using add_const_ref = add_const< add_ref_t<T> >;
        
        template <class T>
        using add_const_ref_t = add_const_t< add_ref_t<T> >;
        
        template <class T>
        using add_volatile_ref = add_volatile< add_ref_t<T> >;
        
        template <class T>
        using add_cv_ref = add_cv< add_ref_t<T> >;
        
        template <class T>
        using add_cv_ref_t = add_cv_t< add_ref_t<T> >;

        ////////////////////////////////////////////////////////////////////////
        // aux::add_rvalue_reference, aux::add_rvalue_ref
        using std::add_rvalue_reference;
        
        template <class T>
        using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
        
        template <class T>
        using add_rvalue_ref = add_rvalue_reference<T>;
        
        template <class T>
        using add_rvalue_ref_t = typename add_rvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_rvalue_ref, aux::add_volatile_rvalue_ref, aux::add_cv_rvalue_ref
        template <class T>
        using add_const_rvalue_ref = add_const< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_const_rvalue_ref_t = add_const_t< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_volatile_rvalue_ref = add_volatile< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_volatile_rvalue_ref_t = add_volatile_t< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_cv_rvalue_ref = add_cv< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_cv_rvalue_ref_t = add_cv_t< add_rvalue_ref_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_pointer, aux::remove_ptr
        using std::remove_pointer;
        
        template <class T>
        using remove_pointer_t = typename remove_pointer<T>::type;
        
        template <class T>
        using remove_ptr = remove_pointer<T>;
        
        template <class T>
        using remove_ptr_t = typename remove_pointer<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_const_ptr, aux::remove_volatile_ptr, aux::remove_cv_ptr
        template <class T>
        using remove_const_ptr = remove_const< remove_ptr_t<T> >;
        
        template <class T>
        using remove_const_ptr_t = remove_const_t< remove_ptr_t<T> >;
        
        template <class T>
        using remove_volatile_ptr = remove_volatile< remove_ptr_t<T> >;
        
        template <class T>
        using remove_volatile_ptr_t = remove_volatile_t< remove_ptr_t<T> >;
        
        template <class T>
        using remove_cv_ptr = remove_cv< remove_ptr_t<T> >;
        
        template <class T>
        using remove_cv_ptr_t = remove_cv_t< remove_ptr_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_pointer, aux::add_ptr
        using std::add_pointer;
        
        template <class T>
        using add_pointer_t = typename add_pointer<T>::type;
        
        template <class T>
        using add_ptr = add_pointer<T>;
        
        template <class T>
        using add_ptr_t = typename add_pointer<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_ptr, aux::add_volatile_ptr, aux::add_cv_ptr
        template <class T>
        using add_const_ptr = add_const< add_ptr_t<T> >;
        
        template <class T>
        using add_const_ptr_t = add_const_t< add_ptr_t<T> >;
        
        template <class T>
        using add_volatile_ptr = add_volatile< add_ptr_t<T> >;
        
        template <class T>
        using add_volatile_ptr_t = add_volatile_t< add_ptr_t<T> >;
        
        template <class T>
        using add_cv_ptr = add_cv< add_ptr_t<T> >;
        
        template <class T>
        using add_cv_ptr_t = add_cv_t< add_ptr_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::make_signed, aux::make_unsigned
        using std::make_signed;
        
        template <class T>
        using make_signed_t = typename make_signed<T>::type;
        
        using std::make_unsigned;
        
        template <class T>
        using make_unsigned_t = typename make_unsigned<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_extent, aux::remove_all_extents
        using std::remove_extent;
        
        template <class T>
        using remove_extent_t = typename remove_extent<T>::type;
        
        using std::remove_all_extents;
        
        template <class T>
        using remove_all_extents_t = typename remove_all_extents<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::aligned_storage, aux::aligned_union
        template <
            std::size_t Len
          , std::size_t Align = static_cast<std::size_t>(-1)
        >
        struct aligned_storage;
            
        template <std::size_t Len, std::size_t Align>
        struct aligned_storage
            : std::aligned_storage<Len, Align>
        {};
            
        template <std::size_t Len>
        struct aligned_storage<Len, static_cast<std::size_t>(-1)>
            : std::aligned_storage<Len>
        {};
        
        template <
            std::size_t Len
          , std::size_t Align = static_cast<std::size_t>(-1)
        >
        using aligned_storage_t = typename aligned_storage<Len, Align>::type;
        
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        using std::aligned_union;
        
        template <std::size_t Len, class ...T>
        using aligned_union_t = typename aligned_union<Len, T...>::type;
# endif

        ///////////////////////////////////////////////////////////////////////
        // aux::decay
        using std::decay;
        
        template <class T>
        using decay_t = typename decay<T>::type;

        ////////////////////////////////////////////////////////////////////////
        // aux::common_type
        using std::common_type;
        
        template <class ...T>
        using common_type_t = typename common_type<T...>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::underlying_type
        using std::underlying_type;
        
        template <class T>
        using underlying_type_t = typename underlying_type<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::result_of
        using std::result_of;
        
        template <class T>
        using result_of_t = typename result_of<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // same_type
        namespace detail
        {
            template <class T, class U>
            struct same_type_impl : false_ {};
            
            template <class T>
            struct same_type_impl<T, T> : true_ {};
        }                                                   // namespace detail
        
        template <class T, class U>
        struct same_type 
          : detail::same_type_impl< uncvref<T>, uncvref<U> >
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // same_intc
        namespace detail
        {
            template <class T0, T0 V0, class T1, T1 V1>
            struct same_intc_impl : false_ {};
            
            template <class T, T V>
            struct same_intc_impl<T, V, T, V> : true_ {};
        }                                                   // namespace detail
        
        template <class T, class U>
        struct same_inc 
          : detail::same_intc_impl<
              typename T::value_type, T::value
            , typename U::value_type, U::value
            >
        {};
    }}                                                      // namespace aux::traits
    
    namespace aux
    {
        using namespace ::elib::aux::traits;
    }                                                       // namespace aux
    
}                                                            // namespace elib
#endif /* ELIB_AUX_HPP */