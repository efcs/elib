#ifndef ELIB_AUX_PAIR_HPP
#define ELIB_AUX_PAIR_HPP

# include <elib/aux/pair_fwd.hpp>
# include <elib/aux/tuple_fwd.hpp>
# include <elib/aux/apply_tuple.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/piecewise_construct.hpp>
# include <elib/functional.hpp>
# include <functional>
# include <tuple>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple_size
    template <class T, class U>
    struct tuple_size< pair<T, U> >
      : size_type_<2>
    {};
    
    template <class T, class U>
    struct tuple_size< std::pair<T, U> >
      : size_type_<2>
    {};
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple_element
    template <class T, class U>
    struct tuple_element<0, pair<T, U>>
    {
        using type = T;
    };
    
    template <class T, class U>
    struct tuple_element<1, pair<T, U>>
    {
        using type = U;
    };
    
    template <std::size_t I, class T, class U>
    struct tuple_element<I, std::pair<T, U> >
      : std::tuple_element<I, std::pair<T, U>>
    {};
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::pair
    template <class First, class Second>
    struct pair
    {
        using first_type = First;
        using second_type = Second;
        
        First first;
        Second second;
        
        constexpr pair() 
                noexcept(is_nothrow_default_constructible<First>::value
                      && is_nothrow_default_constructible<Second>::value)
          : first(), second()
        {}
        
        constexpr pair(const First& f, const Second& s)
                noexcept(is_nothrow_copy_constructible<First>::value
                      && is_nothrow_copy_constructible<Second>::value)
            : first(f), second(s)
        {}
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value
                        && is_convertible<Second, U>::value)
        >
        constexpr pair(T && t, U && u) 
            : first(static_cast<T &&>(t))
            , second(static_cast<U &&>(u))
        {}
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value
                        && is_convertible<Second, U>::value)
        >
        constexpr pair( pair<T, U> const& p) 
            : first(p.first), second(p.second)
        {}
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value
                        && is_convertible<Second, U>::value)
        >
        constexpr pair( pair<T, U> && p )
            : first(aux::move(p.first)), second(aux::move(p.second))
        {}
        
        template <class ...Args1, class ...Args2>
        pair( piecewise_construct_t, 
              tuple<Args1...> first_args
            , tuple<Args2...> second_args )
          : first{ apply_tuple(functional::construct<First>{}, first_args) }
          , second{ apply_tuple(functional::construct<Second>{}, second_args) }
        {}
        
        template <class ...Args1, class ...Args2>
        pair( std::piecewise_construct_t
              , std::tuple<Args1...> first_args
              , std::tuple<Args2...> second_args)
          : first{ apply_tuple(functional::construct<First>{}, first_args) }
          , second{ apply_tuple(functional::construct<Second>{}, second_args) }
        {}
        
        pair( pair const& ) = default;
        pair( pair&& ) = default;
        
        pair& operator=( pair const& p ) 
                noexcept(is_nothrow_copy_assignable<First>::type
                      && is_nothrow_copy_assignable<Second>::type)
        {
            if (this != &p)
            {
                first = p.first;
                second = p.second;
            }
            return *this;
        }
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value
                        && is_convertible<Second, U>::value)
        >
        pair& operator=( pair<T, U> const& p)
        {
            first = p.first;
            second = p.second;
            return *this;
        }
        
        pair& operator=(pair && p)
                noexcept(is_nothrow_move_assignable<First>::value
                      && is_nothrow_move_assignable<Second>::value)
        
        {
            first = aux::move(p.first);
            second = aux::move(p.second);
            return *this;
        }
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value 
                        && is_convertible<Second, U>::value)
        >
        pair& operator=(pair<T, U> && p)
        {
            first = aux::move(p.first);
            second = aux::move(p.second);
        }
        
        void swap(pair& p) 
                noexcept(noexcept(std::swap(first, p.first))
                      && noexcept(std::swap(second, p.second)))
        {
            std::swap(first, p.first);
            std::swap(second, p.second);
        }
    };
    
    namespace detail
    {
        template <class T>
        struct strip_ref_wrapper
        {
            using type = T;
        };
        
        template <class T>
        struct strip_ref_wrapper<std::reference_wrapper<T>>
        {
            using type = T &;
        };
        
        template <class T>
        using decay_strip = typename strip_ref_wrapper< decay_t<T> >::type;
        
        template <class T, class U>
        using decay_strip_pair = pair<decay_strip<T>, decay_strip<U>>;
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::make_pair
    template <class T, class U>
    constexpr detail::decay_strip_pair<T, U> make_pair(T && t, U && u)
    {
        return detail::decay_strip_pair<T, U>(
                    static_cast<T &&>(t), static_cast<U &&>(u));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator==(pair, pair), aux::operator!=(pair, pair)
    template <class T, class U>
    constexpr bool operator==(pair<T, U> const& p1, pair<T, U> const& p2)
    {
        return (p1.first == p2.first && p1.second == p2.second);
    }
    
    template <class T, class U>
    constexpr bool operator !=(pair<T, U> const& p1, pair<T, U> const& p2)
    {
        return (p1.first != p2.first || p1.second != p2.second);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator<(pair, pair) aux::operator<=(pair, pair)
    template <class T, class U>
    constexpr bool operator<(pair<T, U> const& p1, pair<T, U> const& p2)
    {
        return (p1.first < p2.first) 
                ? true 
                : ((p2.first < p1.first) 
                    ? false
                    : (p1.second < p2.second)
                  );
    }
    
    template <class T, class U>
    constexpr bool operator<=(pair<T, U> const& p1, pair<T, U> const& p2)
    {
        return !(p2 < p1);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator>(pair, pair) aux::operator>=(pair, pair)
    template <class T, class U>
    constexpr bool operator>(pair<T, U> const& lhs, pair<T, U> const& rhs)
    {
        return rhs < lhs;
    }
    
    template <class T, class U>
    constexpr bool operator>=(pair<T, U> const& lhs, pair<T, U> const& rhs)
    {
        return !(lhs < rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::swap(pair, pair)
    template <class T, class U>
    inline void swap(pair<T, U> & lhs, pair<T, U> & rhs) noexcept(noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }
    
    namespace detail
    {
        template <std::size_t N>
        struct pair_get_impl;
        
        template <>
        struct pair_get_impl<0>
        {
            template <class T, class U>
            constexpr T& get(pair<T, U> & p) const noexcept
            {
                return p.first;
            }
            
            template <class T, class U>
            constexpr T const& get(pair<T, U> const& p) const noexcept
            {
                return p.first;
            }
            
            template <class T, class U>
            constexpr T&& get(pair<T, U> && p) const noexcept
            {
                return static_cast<T &&>(p.first);
            }
        };
        
        template <>
        struct pair_get_impl<1>
        {
            template <class T, class U>
            constexpr U& get(pair<T, U> & p) const noexcept
            {
                return p.second;
            }
            
            template <class T, class U>
            constexpr U const& get(pair<T, U> const& p) const noexcept
            {
                return p.second;
            }
            
            template <class T, class U>
            constexpr U&& get(pair<T, U> && p) const noexcept
            {
                return static_cast<U &&>(p.second);
            }
        };
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::get(pair)
    template <std::size_t N, class T, class U>
    constexpr auto get( pair<T, U>&& p ) noexcept
    ELIB_AUTO_RETURN( 
        detail::pair_get_impl<N>()(static_cast<pair<T, U> &&>(p))
    )
    
    template <class T, class U>
    constexpr auto get( pair<T, U>&& p ) noexcept
    ELIB_AUTO_RETURN(
        detail::pair_get_impl<0>()(static_cast<pair<T, U> &&>(p))
    )
    

}}                                                           // namespace elib
#endif /* ELIB_AUX_PAIR_HPP */