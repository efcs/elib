#ifndef ELIB_PARAMS_HPP
#define ELIB_PARAMS_HPP

# include <elib/aux.hpp>
# include <cstddef>


namespace elib 
{
    namespace params
    {
        ////////////////////////////////////////////////////////////////////////
        //
        template <class ...Args>
        struct param_pack
        {
            using type = param_pack;
            static constexpr std::size_t size = sizeof...(Args);
        };

        template <class ...Args>
        constexpr std::size_t param_pack<Args...>::size;
    }                                                       // namespace params
    
    using params::param_pack;
    
    namespace params 
    {
        ////////////////////////////////////////////////////////////////////
        //
        template <class P>
        struct _size;

        template <template <class...> class Pack, class ...As>
        struct _size< Pack<As...> > 
            : aux::size_type_<sizeof...(As)>
        {};

        template <class Pack, class ...As>
        struct _size< Pack(As...) >
            : aux::size_type_<sizeof...(As)>
        {};

        template <template <class Tv, Tv...> class Pack, class T, T ...Values>
        struct _size< Pack<T, Values...> > 
            : aux::size_type_<sizeof...(Values)>
        {};

        ////////////////////////////////////////////////////////////////////
        // size
        template <class P>
        using size = typename _size<P>::type;

        ////////////////////////////////////////////////////////////////////
        //
        template <class P>
        struct _empty;

        template <template <class...> class Pack, class ...As>
        struct _empty< Pack<As...> > 
            : aux::bool_<sizeof...(As) == 0>
        {};

        template <class Pack, class ...As>
        struct _empty< Pack(As...) >
            : aux::bool_<sizeof...(As) == 0>
        {};

        template <template <class Tv, Tv...> class Pack, class T, T ...Values>
        struct _empty< Pack<T, Values...> > 
            : aux::bool_<sizeof...(Values) == 0>
        {};

        ////////////////////////////////////////////////////////////////////
        // empty
        template <class P>
        using empty = typename _empty<P>::type;

        ////////////////////////////////////////////////////////////////////
        //
        template <class P, class U>
        struct _concat;

        template <
            template <class...> class Pack0, class ...As0
          , template <class...> class Pack1, class ...As1
          >
        struct _concat< Pack0<As0...>, Pack1<As1...> >
        {
            using type = Pack0<As0..., As1...>;
        };

        template <
            template <class...> class Pack0, class ...As0
          , class Pack1, class ...As1
          >
        struct _concat< Pack0<As0...>, Pack1(As1...) >
        {
            using type = Pack0<As0..., As1...>;
        };

        template <
            class Pack0, class ...As0
          , template <class...> class Pack1, class ...As1
          >
        struct _concat< Pack0(As0...), Pack1<As1...> >
        {
            using type = Pack0(As0..., As1...);
        };

        template <
            class Pack0, class ...As0
          , class Pack1, class ...As1
          >
        struct _concat< Pack0(As0...), Pack1(As1...) >
        {
            using type = Pack0(As0..., As1...);
        };

        template <
            template <class Tv, Tv...> class Pack0
          , template <class Tv, Tv...> class Pack1
          , class T, T ...As0, T ...As1
          >
        struct _concat< Pack0<T, As0...>, Pack1<T, As1...> >
        {
            using type = Pack0<T, As0..., As1...>;
        };

        ////////////////////////////////////////////////////////////////////
        // concat
        template <class LHS, class RHS>
        using concat = typename _concat<LHS, RHS>::type;

        ////////////////////////////////////////////////////////////////////
        //
        template <class P, class ...As>
        struct _append;

        template <
            template <class...> class Pack, class ...As
          , class ...Args
          >
        struct _append< Pack<As...>, Args... >
        {
            using type = Pack<As..., Args...>;
        };

        template <class Pack, class ...As, class ...Args>
        struct _append< Pack(As...), Args... >
        {
            using type = Pack(As..., Args...);
        };

        ////////////////////////////////////////////////////////////////////
        // append
        template <class Pack, class ...Args>
        using append = typename _append<Pack, Args...>::type;

        ////////////////////////////////////////////////////////////////////
        // _append_c(lazy)
        template <class Pack, class T, T ...Values>
        struct _append_c;

        template <
            template <class Tv, Tv...> class Pack 
          , class T, T ...As, T ...Args
          >
        struct _append_c< Pack<T, As...>, T, Args... >
        {
            using type = Pack<T, As..., Args...>;
        };

        ////////////////////////////////////////////////////////////////////
        // append_c
        template <class Pack, class T, T ...Values>
        using append_c = typename _append_c<Pack, T, Values...>::type;

        ////////////////////////////////////////////////////////////////////
        // _prepend (lazy)
        template <class P, class ...As>
        struct _prepend;

        template <
            template <class...> class Pack, class ...As
          , class ...Args
          >
        struct _prepend< Pack<As...>, Args... >
        {
            using type = Pack<Args..., As...>;
        };

        template <class Pack, class ...As, class ...Args>
        struct _prepend< Pack(As...), Args... >
        {
            using type = Pack(Args..., As...);
        };

        ////////////////////////////////////////////////////////////////////
        // prepend
        template <class Pack, class ...Args>
        using prepend = typename _prepend<Pack, Args...>::type;

        ////////////////////////////////////////////////////////////////////
        // _prepend_c (lazy)
        template <class P, class T, T ...Values>
        struct _prepend_c;

        template <
            template <class Tv, Tv...> class Pack
          , class T, T ...As, T ...Args
          >
        struct _prepend_c< Pack<T, As...>, T, Args... >
        {
            using type = Pack<T, Args..., As...>;
        };

        ////////////////////////////////////////////////////////////////////
        // prepend_c
        template <class Pack, class T, T ...Values>
        using prepend_c = typename _prepend_c<Pack, T, Values...>::type;

        ////////////////////////////////////////////////////////////////////
        //
        template <class P, class A>
        using _push_back = _append<P, A>;

        ////////////////////////////////////////////////////////////////////
        //
        template <class P, class A>
        using push_back = append<P, A>;

        ////////////////////////////////////////////////////////////////////
        //
        template <class P, class A>
        using _push_front = _prepend<P, A>;

        ////////////////////////////////////////////////////////////////////
        //
        template <class P, class A>
        using push_front = prepend<P, A>;

        ////////////////////////////////////////////////////////////////////
        // _fill (lazy)
        template <std::size_t N, class T, class Pack = param_pack<>>
        struct _fill
          : _concat<
                typename _fill<(N/2), T, Pack>::type
              , typename _fill<(N-(N/2)), T, Pack>::type
            >
        {};

        template <class T, template <class...> class Pack>
        struct _fill< 0, T, Pack<> >
        {
            using type = Pack<>;
        };

        template <class T, template <class...> class Pack>
        struct _fill< 1, T, Pack<> >
        {
            using type = Pack<T>;
        };

        template <class T, class Pack>
        struct _fill< 0, T, Pack() >
        {
            using type = Pack();
        };

        template <class T, class Pack>
        struct _fill< 1, T, Pack() >
        {
            using type = Pack(T);
        };

        ////////////////////////////////////////////////////////////////////
        // fill
        template <std::size_t N, class T, class Pack = param_pack<>>
        using fill = typename _fill<N, T, Pack>::type;

        namespace detail
        {
            template <class Ignored>
            struct at_impl_1_;

            template <class ...Ignored>
            struct at_impl_1_< param_pack<Ignored...> >
            {
                template <class T, class ...Rest>
                static typename T::type 
                eval(aux::any_pod<Ignored>..., T*, Rest*...); 
            };

            template <std::size_t N, class ...Args>
            using at_impl = 
                decltype(
                    at_impl_1_< typename fill<N, decltype(nullptr)>::type >
                        ::eval( (aux::no_decay<Args>*)nullptr... )
                );

        }                                               // namespace detail

        ////////////////////////////////////////////////////////////////////
        // _at (lazy)
        template <class P, std::size_t N>
        struct _at;

        template <
            template <class...> class Pack, class ...As
          , std::size_t N
          >
        struct _at< Pack<As...>, N >
        {
            using type = detail::at_impl<N, As...>;

            static_assert( 
                N < sizeof...(As)
              , "Index out of bounds"
              );
        };

        template <class Pack, class ...As, std::size_t N>
        struct _at< Pack(As...), N >
        {
            using type = detail::at_impl<N, As...>;

            static_assert(
                N < sizeof...(As)
              , "Index out of bounds"
              );
        };

        template <
            template <class Tv, Tv...> class Pack
          , class T, T ...Values
          , std::size_t N
          >
        struct _at< Pack<T, Values...>, N >
            : detail::at_impl<N, std::integral_constant<T, Values>...>::type
        {
            static_assert( 
                N < sizeof...(Values)
              , "Index out of bounds"
              );
        };

        ////////////////////////////////////////////////////////////////////
        // at
        template <class Pack, std::size_t N>
        using at = typename _at<Pack, N>::type;

        ////////////////////////////////////////////////////////////////////
        // _front (lazy)
        template <class P>
        using _front = _at<P, 0>;

        ////////////////////////////////////////////////////////////////////
        // front
        template <class P>
        using front = at<P, 0>;

        ////////////////////////////////////////////////////////////////////
        // _back (lazy)
        template <class P>
        using _back = _at<P, params::size<P>::value - 1>;

        ////////////////////////////////////////////////////////////////////
        // back
        template <class P>
        using back = at<P, params::size<P>::value - 1>;

        namespace detail
        {
            ////////////////////////////////////////////////////////////////
            //
            template <std::size_t N>
            struct take_impl;

            template <>
            struct take_impl<0>
            {
                template <class Pack, class ...Args>
                using apply = aux::no_decay< Pack >;
            };

            template <>
            struct take_impl<1>
            {
                template <class Pack, class A0, class ...Args>
                using type = append<Pack, A0>;
            };

            template <>
            struct take_impl<2>
            {
                template <class Pack, class A0, class A1, class ...Args>
                using type = append<Pack, A0, A1>;
            };

            template <>
            struct take_impl<3>
            {
                template <class Pack, class A0, class A1, class A2, class ...Args>
                using apply = append<Pack, A0, A1, A2>;
            };

            template <std::size_t N>
            struct take_impl
            {
                template <
                    class Pack
                  , class A0, class A1, class A2, class A3
                  , class ...Args
                  >
                using apply = typename take_impl<N-4>::template
                    apply< 
                        typename append<Pack, A0, A1, A2, A3>::type
                      , Args...
                    >;
            };
        }                                               // namespace detail

        ////////////////////////////////////////////////////////////////////
        // _take (lazy)
        template <class P, std::size_t N>
        struct _take;

        template <
            template <class...> class Pack, class ...As
          , std::size_t N
          >
        struct _take< Pack<As...>, N >
            : detail::take_impl<N>::template apply<Pack<>, As...>
        {};

        template <class Pack, class ...As, std::size_t N>
        struct _take< Pack(As...), N >
            : detail::take_impl<N>::template apply<Pack(), As...>
        {};

        ////////////////////////////////////////////////////////////////////
        // take
        template <class Pack, std::size_t N>
        using take = typename _take<Pack, N>::type;

        namespace detail
        {
            ////////////////////////////////////////////////////////////////
            //
            template <class Pack, class Ignored>
            struct drop_impl_1_;

            template <class Pack, class ...Ignored>
            struct drop_impl_1_< Pack, param_pack<Ignored...> >
            {
                template <class ...Back>
                static append< Pack, typename Back::type... > 
                eval(aux::any_pod<Ignored...>, Back*...);
            };

            ////////////////////////////////////////////////////////////////
            //
            template <std::size_t N, class Pack, class ...Args>
            using drop_impl = 
                decltype(
                    drop_impl_1_< Pack, typename fill<N, decltype(nullptr)>::type >
                        ::eval((aux::no_decay<Args>*)nullptr...)
                );
        }                                               // namespace detail

        ////////////////////////////////////////////////////////////////////
        // _drop (lazy)
        template <class P, std::size_t N>
        struct _drop;

        template <
            template <class...> class Pack, class ...As
          , std::size_t N
          >
        struct _drop< Pack<As...>, N >
            : detail::drop_impl<N, Pack<>, As...>
        {
            static_assert(
                N <= sizeof...(As)
              , "Index out of range"
            );
        };

        template <class Pack, class ...As, std::size_t N>
        struct _drop< Pack(As...), N >
            : detail::drop_impl<N, Pack(), As...>
        {
            static_assert(
                N <= sizeof...(As)
              , "Index out of range"
            );
        };

        ////////////////////////////////////////////////////////////////////
        // drop
        template <class Pack, std::size_t N>
        using drop = typename _drop<Pack, N>::type;

        ////////////////////////////////////////////////////////////////////
        // _pop_front (lazy)
        template <class P>
        using _pop_front = _drop<P, 1>;

        ////////////////////////////////////////////////////////////////////
        // pop_front
        template <class P>
        using pop_front = drop<P, 1>;

        ////////////////////////////////////////////////////////////////////
        // _pop_back (lazy)
        template <class P>
        using _pop_back = _take<P, params::size<P>::value - 1>;

        ////////////////////////////////////////////////////////////////////
        // pop_back
        template <class P>
        using pop_back = take<P, params::size<P>::value - 1>;

        ////////////////////////////////////////////////////////////////////
        // _slice (lazy)
        template <class P, std::size_t First, std::size_t Last>
        struct _slice
            : _take< drop<P, First>, (Last - First) >
        {};

        ////////////////////////////////////////////////////////////////////
        // slice
        template <class P, std::size_t First, std::size_t Second>
        using slice = typename _slice<P, First, Second>::type;
        
    }                                                       // namespace params
}                                                           // namespace elib
#endif /* ELIB_PARAMS_HPP */