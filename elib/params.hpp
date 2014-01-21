#ifndef ELIB_PARAMS_HPP
#define ELIB_PARAMS_HPP

# include <elib/aux/any.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/no_decay.hpp>
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
        // params::size
        template <class P>
        struct size;

        template <template <class...> class Pack, class ...As>
        struct size< Pack<As...> > 
            : aux::size_type_<sizeof...(As)>
        {};

        template <class Pack, class ...As>
        struct size< Pack(As...) >
            : aux::size_type_<sizeof...(As)>
        {};

        template <template <class Tv, Tv...> class Pack, class T, T ...Values>
        struct size< Pack<T, Values...> > 
            : aux::size_type_<sizeof...(Values)>
        {};

        ////////////////////////////////////////////////////////////////////
        // params::size_
        template <class P>
        using size_t = typename size<P>::type;

        ////////////////////////////////////////////////////////////////////
        // params::empty
        template <class P>
        struct empty;

        template <template <class...> class Pack, class ...As>
        struct empty< Pack<As...> > 
            : aux::bool_<sizeof...(As) == 0>
        {};

        template <class Pack, class ...As>
        struct empty< Pack(As...) >
            : aux::bool_<sizeof...(As) == 0>
        {};

        template <template <class Tv, Tv...> class Pack, class T, T ...Values>
        struct empty< Pack<T, Values...> > 
            : aux::bool_<sizeof...(Values) == 0>
        {};

        ////////////////////////////////////////////////////////////////////
        // params::empty
        template <class P>
        using empty_t = typename empty<P>::type;

        ////////////////////////////////////////////////////////////////////
        // params::concat
        template <class P, class U>
        struct concat;

        template <
            template <class...> class Pack0, class ...As0
          , template <class...> class Pack1, class ...As1
          >
        struct concat< Pack0<As0...>, Pack1<As1...> >
        {
            using type = Pack0<As0..., As1...>;
        };

        template <
            template <class...> class Pack0, class ...As0
          , class Pack1, class ...As1
          >
        struct concat< Pack0<As0...>, Pack1(As1...) >
        {
            using type = Pack0<As0..., As1...>;
        };

        template <
            class Pack0, class ...As0
          , template <class...> class Pack1, class ...As1
          >
        struct concat< Pack0(As0...), Pack1<As1...> >
        {
            using type = Pack0(As0..., As1...);
        };

        template <
            class Pack0, class ...As0
          , class Pack1, class ...As1
          >
        struct concat< Pack0(As0...), Pack1(As1...) >
        {
            using type = Pack0(As0..., As1...);
        };

        template <
            template <class Tv, Tv...> class Pack0
          , template <class Tv, Tv...> class Pack1
          , class T, T ...As0, T ...As1
          >
        struct concat< Pack0<T, As0...>, Pack1<T, As1...> >
        {
            using type = Pack0<T, As0..., As1...>;
        };

        ////////////////////////////////////////////////////////////////////
        // params::concat_
        template <class LHS, class RHS>
        using concat_t = typename concat<LHS, RHS>::type;

        ////////////////////////////////////////////////////////////////////
        // params::append
        template <class P, class ...As>
        struct append;

        template <
            template <class...> class Pack, class ...As
          , class ...Args
          >
        struct append< Pack<As...>, Args... >
        {
            using type = Pack<As..., Args...>;
        };

        template <class Pack, class ...As, class ...Args>
        struct append< Pack(As...), Args... >
        {
            using type = Pack(As..., Args...);
        };

        ////////////////////////////////////////////////////////////////////
        // params::append_
        template <class Pack, class ...Args>
        using append_t = typename append<Pack, Args...>::type;

        ////////////////////////////////////////////////////////////////////
        // params::append_c
        template <class Pack, class T, T ...Values>
        struct append_c;

        template <
            template <class Tv, Tv...> class Pack 
          , class T, T ...As, T ...Args
          >
        struct append_c< Pack<T, As...>, T, Args... >
        {
            using type = Pack<T, As..., Args...>;
        };

        ////////////////////////////////////////////////////////////////////
        // params::append_c_
        template <class Pack, class T, T ...Values>
        using append_c_t = typename append_c<Pack, T, Values...>::type;

        ////////////////////////////////////////////////////////////////////
        // params::prepend
        template <class P, class ...As>
        struct prepend;

        template <
            template <class...> class Pack, class ...As
          , class ...Args
          >
        struct prepend< Pack<As...>, Args... >
        {
            using type = Pack<Args..., As...>;
        };

        template <class Pack, class ...As, class ...Args>
        struct prepend< Pack(As...), Args... >
        {
            using type = Pack(Args..., As...);
        };

        ////////////////////////////////////////////////////////////////////
        // params::prepend
        template <class Pack, class ...Args>
        using prepend_t = typename prepend<Pack, Args...>::type;

        ////////////////////////////////////////////////////////////////////
        // params::prepend_c
        template <class P, class T, T ...Values>
        struct prepend_c;

        template <
            template <class Tv, Tv...> class Pack
          , class T, T ...As, T ...Args
          >
        struct prepend_c< Pack<T, As...>, T, Args... >
        {
            using type = Pack<T, Args..., As...>;
        };

        ////////////////////////////////////////////////////////////////////
        // params::prepend_c_
        template <class Pack, class T, T ...Values>
        using prepend_c_t = typename prepend_c<Pack, T, Values...>::type;

        ////////////////////////////////////////////////////////////////////
        // params::push_back
        template <class P, class A>
        using push_back = append<P, A>;

        ////////////////////////////////////////////////////////////////////
        // params::push_back_
        template <class P, class A>
        using push_back_t = append_t<P, A>;

        ////////////////////////////////////////////////////////////////////
        // params::push_front
        template <class P, class A>
        using push_front = prepend<P, A>;

        ////////////////////////////////////////////////////////////////////
        // params::push_front_
        template <class P, class A>
        using push_front_t = prepend_t<P, A>;

        ////////////////////////////////////////////////////////////////////
        // params::fill
        template <std::size_t N, class T, class Pack = param_pack<>>
        struct fill
          : concat<
                typename fill<(N/2), T, Pack>::type
              , typename fill<(N-(N/2)), T, Pack>::type
            >
        {};

        template <class T, template <class...> class Pack>
        struct fill< 0, T, Pack<> >
        {
            using type = Pack<>;
        };

        template <class T, template <class...> class Pack>
        struct fill< 1, T, Pack<> >
        {
            using type = Pack<T>;
        };

        template <class T, class Pack>
        struct fill< 0, T, Pack() >
        {
            using type = Pack();
        };

        template <class T, class Pack>
        struct fill< 1, T, Pack() >
        {
            using type = Pack(T);
        };

        ////////////////////////////////////////////////////////////////////
        // params::fill_
        template <std::size_t N, class T, class Pack = param_pack<>>
        using fill_t = typename fill<N, T, Pack>::type;

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
        // params::at
        template <class P, std::size_t N>
        struct at;

        template <
            template <class...> class Pack, class ...As
          , std::size_t N
          >
        struct at< Pack<As...>, N >
        {
            using type = detail::at_impl<N, As...>;

            static_assert( 
                N < sizeof...(As)
              , "Index out of bounds"
              );
        };

        template <class Pack, class ...As, std::size_t N>
        struct at< Pack(As...), N >
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
        struct at< Pack<T, Values...>, N >
            : detail::at_impl<N, aux::integral_constant<T, Values>...>::type
        {
            static_assert( 
                N < sizeof...(Values)
              , "Index out of bounds"
              );
        };

        ////////////////////////////////////////////////////////////////////
        // params::at_
        template <class Pack, std::size_t N>
        using at_t = typename at<Pack, N>::type;

        ////////////////////////////////////////////////////////////////////
        // params::front
        template <class P>
        using front = at<P, 0>;

        ////////////////////////////////////////////////////////////////////
        // params::front_
        template <class P>
        using front_t = at_t<P, 0>;

        ////////////////////////////////////////////////////////////////////
        // params::back
        template <class P>
        using back = at<P, params::size<P>::value - 1>;

        ////////////////////////////////////////////////////////////////////
        // params::back_
        template <class P>
        using back_t = at_t<P, params::size<P>::value - 1>;

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
                using type = append_t<Pack, A0>;
            };

            template <>
            struct take_impl<2>
            {
                template <class Pack, class A0, class A1, class ...Args>
                using type = append_t<Pack, A0, A1>;
            };

            template <>
            struct take_impl<3>
            {
                template <class Pack, class A0, class A1, class A2, class ...Args>
                using apply = append_t<Pack, A0, A1, A2>;
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
                        append_t<Pack, A0, A1, A2, A3>
                      , Args...
                    >;
            };
        }                                               // namespace detail

        ////////////////////////////////////////////////////////////////////
        // params::take
        template <class P, std::size_t N>
        struct take;

        template <
            template <class...> class Pack, class ...As
          , std::size_t N
          >
        struct take< Pack<As...>, N >
            : detail::take_impl<N>::template apply<Pack<>, As...>
        {};

        template <class Pack, class ...As, std::size_t N>
        struct take< Pack(As...), N >
            : detail::take_impl<N>::template apply<Pack(), As...>
        {};

        ////////////////////////////////////////////////////////////////////
        // params::take_
        template <class Pack, std::size_t N>
        using take_t = typename take<Pack, N>::type;

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
                static append_t< Pack, typename Back::type... > 
                eval(aux::any_pod<Ignored...>, Back*...);
            };

            ////////////////////////////////////////////////////////////////
            //
            template <std::size_t N, class Pack, class ...Args>
            using drop_impl = 
                decltype(
                    drop_impl_1_< Pack, fill_t<N, decltype(nullptr)>>
                        ::eval((aux::no_decay<Args>*)nullptr...)
                );
        }                                               // namespace detail

        ////////////////////////////////////////////////////////////////////
        // params::drop
        template <class P, std::size_t N>
        struct drop;

        template <
            template <class...> class Pack, class ...As
          , std::size_t N
          >
        struct drop< Pack<As...>, N >
            : detail::drop_impl<N, Pack<>, As...>
        {
            static_assert(
                N <= sizeof...(As)
              , "Index out of range"
            );
        };

        template <class Pack, class ...As, std::size_t N>
        struct drop< Pack(As...), N >
            : detail::drop_impl<N, Pack(), As...>
        {
            static_assert(
                N <= sizeof...(As)
              , "Index out of range"
            );
        };

        ////////////////////////////////////////////////////////////////////
        // params::drop
        template <class Pack, std::size_t N>
        using drop_t = typename drop<Pack, N>::type;

        ////////////////////////////////////////////////////////////////////
        // params::pop_front
        template <class P>
        using pop_front = drop<P, 1>;

        ////////////////////////////////////////////////////////////////////
        // params::pop_front_
        template <class P>
        using pop_front_t = drop_t<P, 1>;

        ////////////////////////////////////////////////////////////////////
        // params::pop_back
        template <class P>
        using pop_back = take<P, params::size<P>::value - 1>;

        ////////////////////////////////////////////////////////////////////
        // params::pop_back_
        template <class P>
        using pop_back_t = take_t<P, params::size<P>::value - 1>;

        ////////////////////////////////////////////////////////////////////
        // params::slice
        template <class P, std::size_t First, std::size_t Last>
        struct slice
            : take< drop_t<P, First>, (Last - First) >
        {};

        ////////////////////////////////////////////////////////////////////
        // params::slice_
        template <class P, std::size_t First, std::size_t Second>
        using slice_t = typename slice<P, First, Second>::type;
        
    }                                                       // namespace params
}                                                           // namespace elib
#endif /* ELIB_PARAMS_HPP */