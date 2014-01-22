#ifndef ELIB_AUX_TUPLE_FWD_HPP
#define ELIB_AUX_TUPLE_FWD_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/type_traits.hpp>
# include <elib/aux/no_decay.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    // tuple
    template <class ...T>
    struct tuple;
    
    ////////////////////////////////////////////////////////////////////////////
    // pair
    template <class First, class Second>
    struct pair;
    
    ////////////////////////////////////////////////////////////////////////////
    // piecewise_construct_t
    struct piecewise_construct_t;
    
    ////////////////////////////////////////////////////////////////////////////
    // tuple_size
    template <class T>
    struct tuple_size;
    
    template <class T>
    using tuple_size_t = typename tuple_size<T>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <std::size_t I, class T>
    struct tuple_element;
    
    template <std::size_t I, class T>
    using tuple_element_t = typename tuple_element<I, T>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    // tuple_index_of
    template <class Key, class T>
    struct tuple_element_index;
    
    template <class Key, class T>
    using tuple_element_index_t = typename tuple_element_index<Key, T>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    // tuple_indexes
    template <std::size_t ...>
    struct tuple_indexes;
    
    ////////////////////////////////////////////////////////////////////////////
    // tuple_types
    template <class ...>
    struct tuple_types;
        
    ////////////////////////////////////////////////////////////////////////////
    // aux::get(pair)
    template <std::size_t I, class First, class Second>
    constexpr tuple_element_t<I, pair<First, Second>>&
    get(pair<First, Second> & t) noexcept;
    
    template <std::size_t I, class First, class Second>
    constexpr tuple_element_t<I, pair<First, Second>> const &
    get(pair<First, Second> const& t) noexcept;
    
    template <std::size_t I, class First, class Second>
    constexpr tuple_element_t<I, pair<First, Second>>&&
    get(pair<First, Second> && t) noexcept;
    
    template <class First, class Second>
    constexpr First &
    get(pair<First, Second> & t) noexcept;
    
    template <class First, class Second>
    constexpr First const &
    get(pair<First, Second> const& t) noexcept;
    
    template <class First, class Second>
    constexpr First&&
    get(pair<First, Second> && t) noexcept;
    
    template <class Second, class First>
    constexpr Second &
    get(pair<First, Second> & p) noexcept;
    
    template <class Second, class First>
    constexpr Second const &
    get(pair<First, Second> const& p) noexcept;
    
    template <class Second, class First>
    constexpr Second &&
    get(pair<First, Second> && p) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    // Comparison Operations (pair)
    template <class T, class U>
    constexpr bool operator==(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first == rhs.first) && noexcept(lhs.second == rhs.second));
        
    template <class T, class U>
    constexpr bool operator!=(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first != rhs.first) && noexcept(lhs.second != rhs.second));
        
    template <class T, class U>
    constexpr bool operator<(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first < rhs.first) && noexcept(lhs.second < rhs.second));
        
    template <class T, class U>
    constexpr bool operator>(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first < rhs.first) && noexcept(lhs.second < rhs.second));
        
    template <class T, class U>
    constexpr bool operator<=(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first < rhs.first) && noexcept(lhs.second < rhs.second));
        
    template <class T, class U>
    constexpr bool operator>=(pair<T, U> const& lhs, pair<T, U> const& rhs)
        noexcept(noexcept(lhs.first < rhs.first) && noexcept(lhs.second < rhs.second));
        
    ////////////////////////////////////////////////////////////////////////////
    // Swap
    template <class T, class U>
    void swap(pair<T, U> const& lhs, pair<T, U> const& rhs) 
        noexcept(noexcept(lhs.swap(rhs)));
        
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::get(tuple)
    template <std::size_t I, class ...Ts>
    constexpr tuple_element_t<I, tuple<Ts...>> &
    get(tuple<Ts...> & t) noexcept;
        
    template <std::size_t I, class ...Ts>
    constexpr tuple_element_t<I, tuple<Ts...>> const &
    get(tuple<Ts...> const& t) noexcept;
        
    template <std::size_t I, class ...Ts>
    constexpr tuple_element_t<I, tuple<Ts...>>&&
    get(tuple<Ts...> && t) noexcept;
    
    template <class Key, class ...Ts>
    constexpr Key & 
    get(tuple<Ts...> & t) noexcept;
    
    template <class Key, class ...Ts>
    constexpr Key const& 
    get(tuple<Ts...> const& t) noexcept;
    
    template <class Key, class ...Ts>
    constexpr Key && 
    get(tuple<Ts...> && t) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator==(tuple), aux::operator!=(tuple), aux::operator<(tuple)
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator==(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2);
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator!=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2);
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator< (tuple<Ts1...> const& t1, tuple<Ts2...> const& t2);
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator> (tuple<Ts1...> const& t1, tuple<Ts2...> const& t2);

    template <class ...Ts1, class ...Ts2>
    constexpr bool operator<=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2);
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator>=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2);
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::swap(tuple)
    template <class ...Ts>
    void swap(tuple<Ts...> & lhs, tuple<Ts...> & rhs);
    
    
    namespace tuple_detail
    {

# define ELIB_AUX_TUPLE_IS_FINAL(v) false
# if defined(__clang__)
#   if __has_feature(is_final)
#       undef  ELIB_AUX_TUPLE_IS_FINAL
#       define ELIB_AUX_TUPLE_IS_FINAL(v) __is_final(v)
#   endif
# endif
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_item
        template <
            class Index, class T
          , bool IsEmpty = is_empty<T>::value && ! ELIB_AUX_TUPLE_IS_FINAL(T)
        >
        struct tuple_item;
        
        template <std::size_t Index, class T>
        using tuple_item_c = tuple_item<size_type_<Index>, T>;
        
# undef ELIB_AUX_TUPLE_IS_FINAL
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_size_impl
        template <class T>
        struct tuple_size_impl;
        
        template <class T>
        using tuple_size_uncvref = tuple_size_impl< uncvref<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_element_impl
        template <std::size_t I, class T>
        struct tuple_element_impl;
        
        template <std::size_t I, class T>
        using tuple_element_impl_t = typename tuple_element_impl<I, T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_index_of_impl
        template <class Key, class T>
        struct tuple_element_index_impl;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::make_tuple_indexes
        template <std::size_t Start, class Indexes, std::size_t End>
        struct make_tuple_indexes_impl;
        
    }                                                       // namespace tuple_detail
    
    template <std::size_t End, std::size_t Start = 0>
    struct make_tuple_indexes;
    
    template <std::size_t End, std::size_t Start = 0>
    using make_tuple_indexes_t = typename make_tuple_indexes<End, Start>::type;
        
    namespace tuple_detail
    {
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::make_tuple_types
        template <
            class TupleTypes, class Tuple
          , std::size_t Start, std::size_t End
        >
        struct make_tuple_types_impl;
        
    }                                                       // namespace tuple_detail
    
    template <
        class Tuple
      , std::size_t End = tuple_detail::tuple_size_impl<remove_ref_t<Tuple>>::value
      , std::size_t Start = 0
    >
    struct make_tuple_types;
        
    template <
        class Tuple
      , std::size_t End = tuple_detail::tuple_size_impl<remove_ref_t<Tuple>>::value
      , std::size_t Start = 0
    >
    using make_tuple_types_t = typename make_tuple_types<Tuple, End, Start>::type;
    
    namespace tuple_detail
    {
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_impl
        template <class Indexes, class ...Types>
        struct tuple_impl;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_same_size
        template <class T, class U>
        using is_tuple_same_size = 
            bool_<
                tuple_size_impl<remove_ref_t<T>>::value
                  == tuple_size_impl<remove_ref_t<U>>::value
            >;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_like_impl
        template <class T>
        struct tuple_like_impl;        
    }                                                       // namespace tuple_detail
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::is_tuple_like
    template <class T>
    using is_tuple_like = tuple_detail::tuple_like_impl< uncvref<T> >;
            
    namespace tuple_detail
    {
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_convertible
        template <bool SameSize, class From, class To>
        struct tuple_convertible_impl;
        
        template <
            class From, class To
          , bool = is_tuple_like< From >::value
          , bool = is_tuple_like< To   >::value
        >
        struct tuple_convertible;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_assignable
        template <bool SameSize, class Target, class From>
        struct tuple_assignable_impl;
        
        template <
            class Target, class From
          , bool = is_tuple_like< Target >::value
          , bool = is_tuple_like< From   >::value
        >
        struct tuple_assignable;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_equal
        template <std::size_t I>
        struct tuple_equal;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_less
        template <std::size_t I>
        struct tuple_less;
    }                                                       // namespace tuple_detail
    
    template <class From, class To>
    using is_tuple_convertible = tuple_detail::tuple_convertible<From, To>;
    
    template <class Target, class From>
    using is_tuple_assignable = tuple_detail::tuple_assignable<Target, From>;
    
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_FWD_HPP */