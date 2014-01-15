#ifndef ELIB_UTILITY_HPP
#define ELIB_UTILITY_HPP

# include <functional>
# include <tuple>
# include <type_traits>
# include <utility>
# include <cstddef>
# include <elib/config.hpp>

# /* used to suppress unused warnings */
# define ELIB_UNUSED(x) ((void)x)
# 
# /* used to clearly have exposition for code we don't want to compile */
# define ELIB_EXPO(...) 
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
# // Implementation taken from eric_niebler proto-0x
# // Workaround for GCC not excepting "this" in noexcept clauses 
# // (just remove the noexcept clause until GCC gets there shit together)
# define ELIB_AUTO_RETURN_NOEXCEPT(...)                            \
  noexcept(noexcept(                                               \
    decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                      \
  {                                                                \
    return (__VA_ARGS__);                                          \
  }
#   
#   
# define ELIB_RETURN_NOEXCEPT(...)                                   \
  noexcept(noexcept(                                                 \
      decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                        \
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
# if ELIB_WORKAROUND(ELIB_GNU, GCC_NOEXCEPT_THIS_BUG)
#   
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND(...) { return (__VA_ARGS__); }
#   
# else /* non-workaround support (same as AUTO_RETURN and RETURN) */
#   
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND ELIB_RETURN
#   
# endif

/* thanks to Matt Calabrese for new style enable if 
* and eric neibler for macro impl
*/
# define ELIB_ENABLE_IF(...)                                              \
  typename ::std::enable_if<static_cast<bool>(__VA_ARGS__)>::type* const& = \
    ::elib::utility::static_const<void*>::value
# 
# 
# define ELIB_ENABLE_IF_VALID_EXPR(...)              \
  decltype(static_cast<void>(__VA_ARGS__))* const& = \
    ::elib::utility::static_const<void*>::value
# 
# /* type deduction macro for std::integral_constant */
# define ELIB_AUTO_INTC(...) \
    ::std::integral_constant<decltype(__VA_ARGS__), __VA_ARGS__>

    
namespace elib
{
    namespace utility
    {
        
        template <bool V>
        using bool_ = std::integral_constant<bool, V>;
        
        using true_ = bool_<true>;
        using false_ = bool_<false>;
        
        template <char V>
        using char_ = std::integral_constant<char, V>;
        
        template <int V>
        using int_ = std::integral_constant<bool, V>;
        
        template <unsigned V>
        using uint_ = std::integral_constant<unsigned, V>;
        
        template <long V>
        using long_ = std::integral_constant<long, V>;
        
        template <unsigned long V>
        using ulong_ = std::integral_constant<unsigned long, V>;
        
        template <long long V>
        using llong_ = std::integral_constant<long long, V>;
        
        template <unsigned long long V>
        using ullong_ = std::integral_constant<unsigned long long, V>;
        
        template <std::size_t V>
        using size_type_ = std::integral_constant<std::size_t, V>;
        
        ////////////////////////////////////////////////////////////////////////
        //
        struct none {};
        
        template <class T>
        struct is_none 
          : false_
        {};
        
        template <>
        struct is_none< none >
          : true_
        {};
        
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            //
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
            
            ////////////////////////////////////////////////////////////////////
            //
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
        //
        template <class T>
        struct not_ 
          : bool_<!T::type::value>
        {};
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class A0, class A1, class ...As>
        struct or_ :
            detail::or_impl<static_cast<bool>(A0::type::value)>
              ::template apply<static_cast<bool>(A0::type::value), A0, A1, As...>
        {};
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class A0, class A1, class ...As>
        struct and_ :
            detail::and_impl< !static_cast<bool>(A0::type::value) >
              ::template apply<static_cast<bool>(A0::type::value), A0, A1, As...>
        {};
                
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using remove_const = typename std::remove_const<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using remove_volatile = typename std::remove_volatile<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using remove_cv = typename std::remove_cv<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using remove_ref = typename std::remove_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using remove_ptr = typename std::remove_pointer<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using remove_cvref = remove_cv< remove_ref<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using add_const = typename std::add_const<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using add_volatile = typename std::add_volatile<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using add_cv = add_volatile< add_const<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using add_lvalue_ref = typename std::add_lvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using add_rvalue_ref = typename std::add_rvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using add_ptr = typename std::add_pointer<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using make_signed = typename std::make_signed<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using make_unsigned = typename std::make_unsigned<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using decay = typename std::decay<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <bool Pred, class T = void>
        using enable_if = typename std::enable_if<Pred, T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <bool Pred, class T = void>
        using disable_if = typename std::enable_if<!Pred, T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <bool Pred, class Then, class Else>
        using conditional = typename std::conditional<Pred, Then, Else>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using result_of = typename std::result_of<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class ...T>
        using common_type = typename std::common_type<T...>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        using underlying_type = typename std::underlying_type<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        constexpr T&& forward(remove_ref<T>& t) noexcept
        { 
            return static_cast<T&&>(t);
        }

        template <class T>
        constexpr T&& forward(remove_ref<T>&& t) noexcept
        {
            return static_cast<T &&>(t);
        }
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        constexpr remove_ref<T> && move(T&& t) noexcept
        {
            return static_cast<remove_ref<T> &&>(t);
        }
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T> constexpr 
        conditional<
            !std::is_nothrow_move_constructible<T>::value 
            && std::is_copy_constructible<T>::value
          , const T&
          , T&&
        >
        move_if_noexcept(T& x) noexcept
        {
            return utility::move(x);
        }
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        add_rvalue_ref<T> declval();
        
        ////////////////////////////////////////////////////////////////////////
        //  
# if __cplusplus < 201300
        template <class ...T>
        inline void ignore(T &&...) noexcept
        {}
# else
        template <class ...T>
        constexpr void ignore(T &&...) noexcept
        {}
# endif
        
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            //
            template <class Always, class ...Ignored>
            struct _always
            {
                using type = Always;
            };
        }                                                   // namespace detail
        
        ////////////////////////////////////////////////////////////////////////
        // always
        template <class ...T>
        using always = typename detail::_always<true_, T...>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // never
        template <class ...T>
        using never = typename detail::_always<false_, T...>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class ...T>
        using always_void = typename detail::_always<void, T...>::type;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        struct no_decay
        {
            using type = T;
        };
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class ...Args>
        struct not_defined;
        
        ////////////////////////////////////////////////////////////////////////
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
            constexpr void *const &enabler = utility::static_const<void*>::value;
        }
        
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            //
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
        //
        using any = detail::any<>;
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class Ignored = decltype(nullptr)>
        struct any_pod
        {
            any_pod(...);
        };
        
        ////////////////////////////////////////////////////////////////////////
        //
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
        
        
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            // detail::apply_tuple_impl
            template <
                class F
              , class Tuple
              , std::size_t... I
              >
            auto apply_tuple_impl(F&& f, Tuple&& t, index_sequence<I...>)
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<F &&>(f)(
                    std::get<I>(static_cast<Tuple &&>(t))... 
                )
            )
        }                                                   // namespace detail

        ////////////////////////////////////////////////////////////////////////
        // apply_unpacked_tuple
        template <
            class F
          , class Tuple
          , class IndexSeq = make_index_sequence<std::tuple_size< decay<Tuple> >::value>
        >
        auto apply_unpacked_tuple(F&& f, Tuple&& t, IndexSeq())
        ELIB_AUTO_RETURN_NOEXCEPT(
            detail::apply_tuple_impl(
                static_cast<F &&>(f), static_cast<Tuple &&>(t), IndexSeq{}
            )
        )
        
        
        ////////////////////////////////////////////////////////////////////////
        // scoped_exit
        class scoped_exit
        {
        public:
            scoped_exit( std::function<void()> fn )
                : m_fn{fn}
            {}

            scoped_exit() = delete;
            scoped_exit(const scoped_exit&) = delete;
            scoped_exit(scoped_exit&&) = delete;

            scoped_exit& operator=(const scoped_exit&) = delete;
            scoped_exit& operator=(scoped_exit&&) = delete;

            ~scoped_exit()
                { if (m_fn) m_fn(); }

            void release()
                { m_fn = std::function<void()>{}; }

            operator bool() const
                { return static_cast<bool>(m_fn); }

        private:
            std::function<void()> m_fn;
        };     

    }                                                      // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_HPP */