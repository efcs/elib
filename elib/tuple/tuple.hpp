#ifndef ELIB_TUPLE_TUPLE_HPP
#define ELIB_TUPLE_TUPLE_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/bits/tuple.hpp>
# include <elib/tuple/bits/tuple_impl.hpp>
# include <elib/tuple/support.hpp>
# include <elib/tuple/is_tuple_like.hpp>
# include <elib/tuple/tuple_element.hpp>
# include <elib/tuple/tuple_element_index.hpp>
# include <elib/tuple/bits/tuple_indexes.hpp>
# include <elib/tuple/bits/tuple_size.hpp>
# include <elib/tuple/bits/tuple_types.hpp>
# include <elib/aux.hpp>
# include <cstddef>

namespace elib { namespace tuples
{    
    ////////////////////////////////////////////////////////////////////////////
    // tuples::make_tuple    
    template <class ...Ts>
    constexpr detail::make_tuple_return_t<Ts...>
    make_tuple(Ts&&... t)
    {
        return detail::make_tuple_return_t<Ts...>(elib::forward<Ts>(t)...);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // tuples::forward_as_tuple
    template <class ...Ts>
    constexpr tuple<Ts&&...>
    forward_as_tuple(Ts&&... t)
    {
        return tuple<Ts&&...>(elib::forward<Ts>(t)...);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // tuples::tie(T...)
    template <class ...Ts>
    constexpr tuple<Ts&...> 
    tie(Ts&... t)
    {
        return tuple<Ts&...>(t...);
    }
      
    ////////////////////////////////////////////////////////////////////////////
    // aux::get(tuple)
    template <std::size_t I, class ...Ts>
    constexpr tuple_element_t<I, tuple<Ts...>>&
    get(tuple<Ts...> & t) noexcept
    {
        using Type = tuple_element_t<I, tuple<Ts...>>;
        return static_cast<detail::tuple_item_c<I, Type> &>(t.m_impl).get();
    }
    
    template <std::size_t I, class ...Ts>
    constexpr tuple_element_t<I, tuple<Ts...>> const &
    get(tuple<Ts...> const& t) noexcept
    {
        using Type = tuple_element_t<I, tuple<Ts...>>;
        return static_cast<detail::tuple_item_c<I, Type> const &>(t.m_impl).get();
    }
    
    template <std::size_t I, class ...Ts>
    constexpr tuple_element_t<I, tuple<Ts...>> &&
    get(tuple<Ts...> && t) noexcept
    {
        using Type = tuple_element_t<I, tuple<Ts...>>;
        return 
            static_cast<Type &&>(
                static_cast<detail::tuple_item_c<I, Type> &&>(t.m_impl).get()
            );
    }
    
    template <class Value, class ...Ts>
    constexpr Value & 
    get(tuple<Ts...> & t) noexcept
    {
        using AtVal = typename decltype(t.m_impl)::template item_at_value<Value>;
        return AtVal::call(t);
    }
    
    template <class Value, class ...Ts>
    constexpr Value const& 
    get(tuple<Ts...> const& t) noexcept
    {
        using AtVal = typename decltype(t.m_impl)::template item_at_value<Value>;
        return AtVal::call(t);
    }
    
    template <class Value, class ...Ts>
    constexpr Value && 
    get(tuple<Ts...> && t) noexcept
    {
        using AtVal = typename decltype(t.m_impl)::template item_at_value<Value>;
        return AtVal::call(std::move(t));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator==, aux::operator!=, aux::operator<
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator==(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return detail::tuple_equal<sizeof...(Ts1)>()(t1, t2); }
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator!=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return !(t1 == t2); }
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator<(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return detail::tuple_less<sizeof...(Ts1)>()(t1, t2); }
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator>(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return t2 < t1; }

    template <class ...Ts1, class ...Ts2>
    constexpr bool operator<=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return !(t2 < t1); }
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator>=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return !(t1 < t2); }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::swap
    template <class ...Ts>
    inline void swap(tuple<Ts...> & lhs, tuple<Ts...> & rhs)
    {
        lhs.swap(rhs);
    }
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_TUPLE_HPP */