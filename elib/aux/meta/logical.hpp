#ifndef ELIB_AUX_META_LOGICAL_HPP
#define ELIB_AUX_META_LOGICAL_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/meta/if.hpp>

namespace elib { namespace aux
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
}}                                                          // namespace elib
namespace elib
{
    using aux::not_;
    using aux::not_c;
    using aux::and_;
    using aux::and_c;
    using aux::or_;
    using aux::or_c;
}                                                           // namespace elib
#endif /* ELIB_AUX_META_LOGICAL_HPP */