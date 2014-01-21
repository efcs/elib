#ifndef ELIB_AUX_TUPLE_ELIB_TUPLE_HPP
#define ELIB_AUX_TUPLE_ELIB_TUPLE_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/helper.hpp>
# include <elib/aux/tuple/tuple_impl.hpp>
# include <elib/aux/tuple/tuple_indexes.hpp>
# include <elib/aux/tuple/tuple_types.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>
# include <cstddef>


namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple
    template <class ...Types>
    struct tuple
    {
    private:
        using Impl = 
            tuple_detail::tuple_impl<
                make_tuple_indexes_t<sizeof...(Types)>
              , Types...
            >;
        
        Impl m_impl;
        
        template <class Key, class T>
        friend struct tuple_detail::tuple_index_of_impl;
        
        template<std::size_t I, class T>
        friend struct tuple_detail::tuple_element_impl;
        
        template <std::size_t I, class ...Ts>
        friend constexpr tuple_element_t<I, tuple<Ts...>>&
        get(tuple<Ts...> & t) noexcept;
        
        template <std::size_t I, class ...Ts>
        friend constexpr tuple_element_t<I, tuple<Ts...>> const &
        get(tuple<Ts...> const& t) noexcept;
        
        template <std::size_t I, class ...Ts>
        friend constexpr tuple_element_t<I, tuple<Ts...>>&&
        get_tuple(tuple<Ts...> && t);
        
        template <class Key, class ...Ts>
        friend constexpr Key & 
        get(tuple<Ts...> & t) noexcept;
    
        template <class Key, class ...Ts>
        friend constexpr Key const& 
        get(tuple<Ts...> const& t) noexcept;
    
        template <class Key, class ...Ts>
        friend constexpr Key && 
        get(tuple<Ts...> && t) noexcept;
        
    public:
        
        explicit tuple(Types const&... t)
          : m_impl(
                make_tuple_indexes_t<sizeof...(Types)>()
              , make_tuple_types_t<tuple, sizeof...(Types)>()
              , make_tuple_indexes_t<0>()
              , make_tuple_types_t<tuple, 0>()
              , t...
            )
        {}
        
        template <
            class ...Us
          , ELIB_ENABLE_IF(
                sizeof...(Us) <= sizeof...(Types) 
                && is_tuple_convertible<
                        make_tuple_types_t<tuple<Us...>>
                      , make_tuple_types_t<tuple, 
                            sizeof...(Us) < sizeof...(Types)
                                ? sizeof...(Us)
                                : sizeof...(Types)
                        >
                    >::value
            )
        >
        explicit tuple(Us &&... t)
          : m_impl(
                make_tuple_indexes_t<sizeof...(Us)>()
              , make_tuple_types_t<tuple, sizeof...(Us)>()
              , make_tuple_indexes_t<sizeof...(Types), sizeof...(Us)>()
              , make_tuple_types_t<tuple, sizeof...(Types), sizeof...(Us)>()
              , static_cast<Us &&>(t)...
              )
            {}
        
        template <
            class OtherT
          , ELIB_ENABLE_IF(is_tuple_convertible<OtherT, tuple>::value)
        >
        tuple(OtherT && t)
          : m_impl(static_cast<OtherT &&>(t))
        {}
        
        template <
            class OtherT
          , ELIB_ENABLE_IF(is_tuple_assignable<OtherT, tuple>::value)
        >
        tuple& operator=(OtherT && t)
        {
            m_impl.operator=(static_cast<OtherT &&>(t));
            return *this;
        }
        
        void swap(tuple& t) noexcept(noexcept(m_impl.swap(t)))
        {
            m_impl.swap(t);
        }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple<> (Empty)
    template <>
    struct tuple<>
    {
        tuple() noexcept {}
        
        template <
            class Other
          , ELIB_ENABLE_IF(is_tuple_convertible<Other, tuple>::value)
        >
        tuple(Other &&)
        {}
        
        template <
            class Other
          , ELIB_ENABLE_IF(is_tuple_assignable<Other, tuple>::value)
        >
        tuple& operator=(Other &&) noexcept
        { return *this; }
        
        void swap(tuple &)
        {}
    };                                                    
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_ELIB_TUPLE_HPP */