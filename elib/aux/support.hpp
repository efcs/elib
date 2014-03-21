#ifndef ELIB_AUX_SUPPORT_HPP
#define ELIB_AUX_SUPPORT_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits.hpp>

////////////////////////////////////////////////////////////////////////////////
// 
# define ELIB_UNUSED(x) ((void)x)

////////////////////////////////////////////////////////////////////////////////
// 
# define ELIB_DEFAULT_CLASS(Class)          \
  Class() = default;                        \
                                            \
  Class(const Class&) = default;            \
  Class(Class&&) = default;                 \
                                            \
  Class& operator=(const Class&) = default; \
  Class& operator=(Class&&) = default
# 

# define ELIB_DEFAULT_COPY(Class)   \
    Class(Class const &) = default; \
    Class & operator=(Class const &) = default
# 

# define ELIB_DEFAULT_MOVE(Class) \
    Class(Class &&) = default;    \
    Class & operator=(Class &&) = default
# 
    
# define ELIB_DEFAULT_COPY_MOVE(Class) \
    ELIB_DEFAULT_COPY(Class);          \
    ELIB_DEFAULT_MOVE(Class)
# 
    
# define ELIB_DELETE_COPY(Class)   \
    Class(Class const &) = delete; \
    Class & operator=(Class const &) = delete
# 
    
# define ELIB_DELETE_MOVE(Class) \
    Class(Class &&) = delete;    \
    Class & operator=(Class &&) = delete
# 
    
# define ELIB_DELETE_COPY_MOVE(Class) \
    ELIB_DELETE_COPY(Class);          \
    ELIB_DELETE_MOVE(Class)
# 
    
////////////////////////////////////////////////////////////////////////////////
// 
# /* used to clearly have exposition for code we don't want to compile */
# define ELIB_EXPO(...) 

# // noexcept copy clause 
# define ELIB_NOEXCEPT(...)                                             \
    noexcept((                                                          \
        decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
    ))
# 

////////////////////////////////////////////////////////////////////////////////
// 
// Implementation taken from eric_niebler proto-0x
// Workaround for GCC not excepting "this" in noexcept clauses 
// (just remove the noexcept clause until GCC gets their shit together)
# define ELIB_AUTO_RETURN_NOEXCEPT(...)                             \
  noexcept(noexcept(                                                \
    decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                       \
  {                                                                 \
    return (__VA_ARGS__);                                           \
  }
#   
#   
# define ELIB_RETURN_NOEXCEPT(...)                                    \
  noexcept(noexcept(                                                  \
      decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
  ))                                                                  \
  {                                                                   \
    return (__VA_ARGS__);                                             \
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
# if ELIB_WORKAROUND(ELIB_CONFIG_GCC, GCC_NOEXCEPT_THIS_BUG)
#
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND(...) { return (__VA_ARGS__); }
#   
# else /* non-workaround support (same as AUTO_RETURN and RETURN) */
#   
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND ELIB_RETURN
# endif
# 
////////////////////////////////////////////////////////////////////////////////
// 
// for use with ELIB_ENABLE_IF and ELIB_ENABLE_IF_VALID_EXPR 
# define ELIB_ENABLER_TYPE void* const&
# define ELIB_ENABLER ::elib::aux::enabler

////////////////////////////////////////////////////////////////////////////////
//
# if __cplusplus <= 201303L
#   define ELIB_CXX14_CONSTEXPR inline
# else
#   define ELIB_CXX14_CONSTEXPR constexpr
# endif

namespace elib 
{ 
    namespace aux
    {
        ////////////////////////////////////////////////////////////////////////
        // forward
        template <class T>
        constexpr T&& 
        forward(typename aux::remove_reference<T>::type& t) noexcept
        { 
            return static_cast<T&&>(t);
        }

        template <class T>
        constexpr T&& 
        forward(typename aux::remove_reference<T>::type&& t) noexcept
        {
            return static_cast<T &&>(t);
            static_assert(
                !aux::is_lvalue_reference<T>::value
              , "elib::forward called with lvalue reference"
              );
        }
            
        ////////////////////////////////////////////////////////////////////////
        // move
        template <class T>
        constexpr typename aux::remove_reference<T>::type&& 
        move(T&& t) noexcept
        {
            return static_cast<typename aux::remove_reference<T>::type &&>(t);
        }
            
        /////////////////////////////////////////////////////////////////////////
        // move_if_noexcept
        template <class T> 
        constexpr 
            typename aux::conditional<
                ! aux::is_nothrow_move_constructible<T>::value 
                && aux::is_copy_constructible<T>::value
            , const T&
            , T&&
            >::type
        move_if_noexcept(T& x) noexcept
        {
            return aux::move(x);
        }
            
        ////////////////////////////////////////////////////////////////////////
        // declval. NOTE: use of add_rvalue_reference ensures handling of void.
        template <class T>
        typename aux::add_rvalue_reference<T>::type 
        declval() noexcept;
        
        namespace detail
        {
            template <class T>
            struct has_overload_addressof
            {
                template <
                    class U
                  , std::size_t = sizeof(::elib::aux::declval<U &>().operator&())
                >
                static constexpr bool test(int) { return true; }
                
                template <class U>
                static constexpr bool test(...) { return false; }
                
                using type = integral_constant<bool, test<T>(0)>;
            };
            
            template <bool HasOverload>
            struct addressof_impl
            {
                template <class T>
                static constexpr T* addressof(T & t) noexcept
                {
                    return &t;
                }
            };
            
            template <>
            struct addressof_impl<true>
            {
                template <class T>
                static T* addressof(T & t) noexcept
                {
                    return reinterpret_cast<T*>(
                    & const_cast<char &>(
                        reinterpret_cast<const volatile char &>(t)
                    ));
                }
            };
        }                                                   // namespace detail
        
        ////////////////////////////////////////////////////////////////////////
        // aux::addressof
        template <class T>
        constexpr T* addressof(T & t) noexcept
        {
            using HasOverload = typename detail::has_overload_addressof<T>::type;
            return detail::addressof_impl<HasOverload::value>::addressof(t);
        }
    }                                                       // namespace aux
    
    using aux::forward;
    using aux::move;
    using aux::move_if_noexcept;
    using aux::declval;
    using aux::addressof;
    
    namespace aux 
    {
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            // detail::anything
            template <class Ignored = decltype(nullptr)>
            struct anything
            {
                anything() = default;

                template <typename T>
                constexpr anything(T const &) noexcept
                {}

                template <class T>
                operator T &&() const noexcept;
            };
        }                                                   // namespace detail

        ////////////////////////////////////////////////////////////////////////
        // any
        using anything = detail::anything<>;

        ////////////////////////////////////////////////////////////////////////
        // any_pod
        template <class Ignored = decltype(nullptr)>
        struct any_pod
        {
            any_pod(...);
        };

        ////////////////////////////////////////////////////////////////////////
        //
# if __cplusplus <= 201303L
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
}                                                           // namespace elib
#endif /* ELIB_AUX_SUPPORT_HPP */