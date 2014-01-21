#ifndef ELIB_AUX_TUPLE_PAIR_HPP
#define ELIB_AUX_TUPLE_PAIR_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/helper.hpp>
# include <elib/aux/tuple/is_tuple_like.hpp>
# include <elib/aux/tuple/piecewise_construct.hpp>
# include <elib/aux/tuple/tuple_element.hpp>
# include <elib/aux/tuple/tuple_size.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>
# include <elib/functional.hpp>
# include <functional>
# include <tuple>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    
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
    
    namespace tuple_detail
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
    }                                                       // namespace tuple_detail
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::make_pair
    template <class T, class U>
    constexpr tuple_detail::decay_strip_pair<T, U> make_pair(T && t, U && u)
    {
        return tuple_detail::decay_strip_pair<T, U>(
                    static_cast<T &&>(t), static_cast<U &&>(u));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator==(pair, pair), aux::operator!=(pair, pair)
    template <class T, class U>
    constexpr bool operator==(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first == rhs.first) && noexcept(lhs.second == rhs.second))
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }
    
    template <class T, class U>
    constexpr bool operator !=(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first != rhs.first) && noexcept(lhs.second != rhs.second))
    {
        return (lhs.first != rhs.first || lhs.second != rhs.second);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator<(pair, pair) aux::operator<=(pair, pair)
    template <class T, class U>
    constexpr bool operator<(pair<T, U> const& lhs, pair<T, U> const& rhs)
            noexcept(noexcept(lhs.first < rhs.first) && noexcept(lhs.second < rhs.second))
    {
        return (lhs.first < rhs.first) 
                ? true 
                : ((rhs.first < lhs.first) 
                    ? false
                    : (lhs.second < rhs.second)
                  );
    }
    
    template <class T, class U>
    constexpr bool operator<=(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first < rhs.first) && noexcept(lhs.second < rhs.second))
    {
        return !(rhs < lhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator>(pair, pair) aux::operator>=(pair, pair)
    template <class T, class U>
    constexpr bool operator>(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first < rhs.first) && noexcept(lhs.second < rhs.second))
    {
        return rhs < lhs;
    }
    
    template <class T, class U>
    constexpr bool operator>=(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first < rhs.first) && noexcept(lhs.second < rhs.second))
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
    
    namespace tuple_detail
    {
        template <std::size_t N>
        struct pair_get_impl;
        
        template <>
        struct pair_get_impl<0>
        {
            template <class T, class U>
            static constexpr T& get_ref(pair<T, U> & p) noexcept
            {
                return p.first;
            }
            
            template <class T, class U>
            static constexpr T const& get_cref(pair<T, U> const& p) noexcept
            {
                return p.first;
            }
            
            template <class T, class U>
            static constexpr T&& get_move(pair<T, U> && p) noexcept
            {
                return aux::move(p.first);
            }
        };
        
        template <>
        struct pair_get_impl<1>
        {
            template <class T, class U>
            static constexpr U& get_ref(pair<T, U> & p) noexcept
            {
                return p.second;
            }
            
            template <class T, class U>
            static constexpr U const& get_cref(pair<T, U> const& p) noexcept
            {
                return p.second;
            }
            
            template <class T, class U>
            static constexpr U&& get_move(pair<T, U> && p) noexcept
            {
                return aux::move(p.second);
            }
        };
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::get(pair)
    template <std::size_t I, class First, class Second>
    constexpr tuple_element_t<I, pair<First, Second>>&
    get(pair<First, Second> & t) noexcept
    {
        return tuple_detail::pair_get_impl<I>::get_ref(t);
    }
    
    template <std::size_t I, class First, class Second>
    constexpr tuple_element_t<I, pair<First, Second>> const &
    get(pair<First, Second> const& t) noexcept
    {
        return tuple_detail::pair_get_impl<I>::get_cref(t);
    }
    
    template <std::size_t I, class First, class Second>
    constexpr tuple_element_t<I, pair<First, Second>>&&
    get(pair<First, Second> && t) noexcept
    {
        return tuple_detail::pair_get_impl<I>::get_move(aux::move(t)); 
    }
    
    template <class First, class Second>
    constexpr First &
    get(pair<First, Second> & t) noexcept
    {
        return t.first;
    }
    
    template <class First, class Second>
    constexpr First const &
    get(pair<First, Second> const& t) noexcept
    {
        return t.first;
    }
    
    template <class First, class Second>
    constexpr First&&
    get(pair<First, Second> && t) noexcept
    {
        return aux::move(t.first);
    }
    
    template <class Second, class First>
    constexpr Second &
    get(pair<First, Second> & t) noexcept
    {
        return t.second;
    }
    
    template <class Second, class First>
    constexpr Second const &
    get(pair<First, Second> const& t) noexcept
    {
        return t.second;
    }
    
    template <class Second, class First>
    constexpr Second &&
    get(pair<First, Second> && t) noexcept
    {
        return aux::move(t.second);
    }
    

}}                                                           // namespace elib
#endif /* ELIB_AUX_TUPLE_PAIR_HPP */