#ifndef ELIB_AUX_LOGICAL_HPP
#define ELIB_AUX_LOGICAL_HPP

# include <elib/aux/if.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/none.hpp>

namespace elib 
{
    namespace aux
    {
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
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class A0, class A1, class ...As>
        struct and_ :
            detail::and_impl< !static_cast<bool>(A0::type::value) >
              ::template apply<static_cast<bool>(A0::type::value), A0, A1, As...>::type
        {
            using type = and_;
            
            using result = typename
                detail::and_impl< !static_cast<bool>(A0::type::value) >
              ::template apply<static_cast<bool>(A0::type::value), A0, A1, As...>;
              
            using which = typename result::which;
        };
        
        namespace detail
        {
            template <class ...Args>
            true_ all_pointers_test(Args*...);
        
            false_ all_pointers_test(...);
        
            template <class ...Args>
            false_ not_all_pointers_test(Args*...);
        
            true_ not_all_pointers_test(...);
        }                                                   // namespace detail

        ////////////////////////////////////////////////////////////////////////////
        // fast_not
        template <class Pred>
        using fast_not = bool_< static_cast<bool>(Pred::type::value) >;

        template <bool Pred>
        using fast_not_c = bool_< ! Pred >;

        ////////////////////////////////////////////////////////////////////////////
        // fast_and
        template <class ...Preds>
        using fast_and = decltype( 
            detail::all_pointers_test(if_t<Preds, int*, int>{}...) 
        );

        template <bool ...Preds>
        using fast_and_c = decltype(
            detail::all_pointers_test(if_c_t<Preds, int*, int>{}...)
        );

        ////////////////////////////////////////////////////////////////////////////
        // fast_or
        template <class ...Preds>
        using fast_or = decltype(
            detail::not_all_pointers_test(if_t<Preds, int, int*>{}...)
        );

        template <bool ...Preds>
        using fast_or_c = decltype(
            detail::not_all_pointers_test(if_c_t<Preds, int, int*>{}...)
        );
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_LOGICAL_HPP */