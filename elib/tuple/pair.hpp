#ifndef ELIB_TUPLE_PAIR_HPP
#define ELIB_TUPLE_PAIR_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/elib_pair.hpp>
# include <elib/tuple/helper.hpp>
# include <elib/tuple/is_tuple_like.hpp>
# include <elib/tuple/tuple_element.hpp>
# include <elib/tuple/tuple_element_index.hpp>
# include <elib/tuple/tuple_size.hpp>
# include <elib/aux.hpp>
# include <elib/functional.hpp>
# include <functional>
# include <tuple>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
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
            static constexpr T& get(pair<T, U> & p) noexcept
            {
                return p.first;
            }
            
            template <class T, class U>
            static constexpr T const& get(pair<T, U> const& p) noexcept
            {
                return p.first;
            }
            
            template <class T, class U>
            static constexpr T&& get(pair<T, U> && p) noexcept
            {
                return elib::move(p.first);
            }
        };
        
        template <>
        struct pair_get_impl<1>
        {
            template <class T, class U>
            static constexpr U& get(pair<T, U> & p) noexcept
            {
                return p.second;
            }
            
            template <class T, class U>
            static constexpr U const& get(pair<T, U> const& p) noexcept
            {
                return p.second;
            }
            
            template <class T, class U>
            static constexpr U&& get(pair<T, U> && p) noexcept
            {
                return elib::move(p.second);
            }
        };
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::get(pair)
    template <std::size_t I, class First, class Second>
    constexpr tuple_element_t<I, pair<First, Second>>&
    get(pair<First, Second> & t) noexcept
    {
        static_assert(
            !is_const<tuple_element_t<I, pair<First, Second>>>::value
          , "Shit");
        return tuple_detail::pair_get_impl<I>::get(t);
    }
    
    template <std::size_t I, class First, class Second>
    constexpr tuple_element_t<I, pair<First, Second>> const&
    get(pair<First, Second> const& t) noexcept
    {
        return tuple_detail::pair_get_impl<I>::get(t);
    }
    
    template <std::size_t I, class First, class Second>
    constexpr tuple_element_t<I, pair<First, Second>>&&
    get(pair<First, Second> && t) noexcept
    {
        return tuple_detail::pair_get_impl<I>::get(elib::move(t)); 
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
        return elib::move(t.first);
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
        return elib::move(t.second);
    }
    

}}                                                           // namespace elib
#endif /* ELIB_TUPLE_PAIR_HPP */