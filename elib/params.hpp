#ifndef ELIB_PARAMS_HPP
#define ELIB_PARAMS_HPP

# include <elib/aux/always.hpp> /* for never<...> */
# include <elib/aux/any_pod.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/no_decay.hpp>
# include <cstddef>

namespace elib { namespace params { inline namespace v1
{
    ////////////////////////////////////////////////////////////////////////////
    template <class ...Args>
    struct param_pack
    {
        using type = param_pack;
        static constexpr std::size_t size = sizeof...(Args);
    };
    
    template <class ...Args>
    constexpr std::size_t param_pack<Args...>::size;
        
    template <class T, T ...Values>
    using param_pack_c = param_pack<integral_constant<T, Values>...>;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, T ...Values>
    struct value_pack
    {
        using type = value_pack;
        static constexpr std::size_t size = sizeof...(Values);
    };
    
    template <class T, T ...Values>
    constexpr std::size_t value_pack<T, Values...>::size;

    
    ////////////////////////////////////////////////////////////////////////////
    template<
        template <class Tv, Tv...> class ToPack
      , class T
      , class FromPack
      >
    struct convert_to_value_pack;
    
    template <
        template <class Tv, Tv ...> class ToPack
      , class To
      , template <class ...> class FromPack
      , class ...FromArgs
      >
    struct convert_to_value_pack<ToPack, To, FromPack<FromArgs...>>
    {
        using type = ToPack<To, FromArgs::type::value...>;
    };
    
    template <
        template <class Tv, Tv ...> class ToPack
      , class To
      , class FromTag, class ...FromArgs
      >
    struct convert_to_value_pack<ToPack, To, FromTag(FromArgs...)>
    {
        using type = ToPack<To, FromArgs::type::value...>;
    };
    
    template <
        template <class Tv, Tv ...> class ToPack
      , class To
      , template <class Tx, Tx ...> class FromPack
      , class FromT, FromT ...FromVals
      >
    struct convert_to_value_pack<ToPack, To, FromPack<FromT, FromVals...>>
    {
        using type = ToPack<To, FromVals...>;
    };
    
    template <
        template <class Tv, Tv ...> class ToPack
      , class ToType
      , class FromPack
      >
    using convert_to_value_pack_t = typename 
        convert_to_value_pack<ToPack, ToType, FromPack>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class Tag, class FromPack>
    struct convert_to_tag_pack;
    
    template <
        class Tag
      , template <class ...> class FromPack
      , class ...FromArgs
      >
    struct convert_to_tag_pack<Tag, FromPack<FromArgs...>>
    {
        using type = Tag(FromArgs...);
    };
    
    template <
        class Tag
      , class FromTag, class ...FromArgs
      >
    struct convert_to_tag_pack<Tag, FromTag(FromArgs...)>
    {
        using type = Tag(FromArgs...);
    };
    
    template <class Tag, class FromPack>
    using convert_to_tag_pack_t = typename convert_to_tag_pack<Tag, FromPack>::type;
    
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // params::size
    template <class P>
    struct size;

    template <template <class...> class Pack, class ...As>
    struct size< Pack<As...> > 
      : size_type_<sizeof...(As)>
    {};

    template <class Pack, class ...As>
    struct size< Pack(As...) >
      : size_type_<sizeof...(As)>
    {};

    template <template <class Tv, Tv...> class Pack, class T, T ...Values>
    struct size< Pack<T, Values...> > 
      : size_type_<sizeof...(Values)>
    {};

    ////////////////////////////////////////////////////////////////////////////
    // params::size_
    template <class P>
    using size_t = typename size<P>::type;

    ////////////////////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////////////////////
    // params::empty
    template <class P>
    using empty_t = typename empty<P>::type;

    ////////////////////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////////////////////
    // params::concat_
    template <class LHS, class RHS>
    using concat_t = typename concat<LHS, RHS>::type;

    ////////////////////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////////////////////
    // params::append_
    template <class Pack, class ...Args>
    using append_t = typename append<Pack, Args...>::type;

    ////////////////////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////////////////////
    // params::append_c_
    template <class Pack, class T, T ...Values>
    using append_c_t = typename append_c<Pack, T, Values...>::type;

    ////////////////////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////////////////////
    // params::prepend
    template <class Pack, class ...Args>
    using prepend_t = typename prepend<Pack, Args...>::type;

    ////////////////////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////////////////////
    // params::prepend_c_
    template <class Pack, class T, T ...Values>
    using prepend_c_t = typename prepend_c<Pack, T, Values...>::type;

    ////////////////////////////////////////////////////////////////////////////
    // params::push_back
    template <class P, class A>
    using push_back = append<P, A>;

    ////////////////////////////////////////////////////////////////////////////
    // params::push_back_
    template <class P, class A>
    using push_back_t = append_t<P, A>;

    ////////////////////////////////////////////////////////////////////////////
    // params::push_front
    template <class P, class A>
    using push_front = prepend<P, A>;

    ////////////////////////////////////////////////////////////////////////////
    // params::push_front_
    template <class P, class A>
    using push_front_t = prepend_t<P, A>;

    ////////////////////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////////////////////
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
                    ::eval( static_cast<aux::no_decay<Args>*>(nullptr)... )
            );

    }                                               // namespace detail

    ////////////////////////////////////////////////////////////////////////////
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
      : detail::at_impl<N, integral_constant<T, Values>...>::type
    {
        static_assert( 
            N < sizeof...(Values)
          , "Index out of bounds"
          );
    };

    ////////////////////////////////////////////////////////////////////////////
    // params::at_
    template <class Pack, std::size_t N>
    using at_t = typename at<Pack, N>::type;

    ////////////////////////////////////////////////////////////////////////////
    // params::front
    template <class P>
    using front = at<P, 0>;

    ////////////////////////////////////////////////////////////////////////////
    // params::front_
    template <class P>
    using front_t = at_t<P, 0>;

    ////////////////////////////////////////////////////////////////////////////
    // params::back
    template <class P>
    using back = at<P, params::size<P>::value - 1>;

    ////////////////////////////////////////////////////////////////////////////
    // params::back_
    template <class P>
    using back_t = at_t<P, params::size<P>::value - 1>;

    namespace detail
    {
        ////////////////////////////////////////////////////////////////////
        template <std::size_t N>
        struct take_impl;

        template <>
        struct take_impl<0>
        {
            template <class Pack, class ...Args>
            struct apply : aux::no_decay< Pack > {};
        };

        template <>
        struct take_impl<1>
        {
            template <class Pack, class A0, class ...Args>
            struct apply : append<Pack, A0> {};
        };

        template <>
        struct take_impl<2>
        {
            template <class Pack, class A0, class A1, class ...Args>
            struct apply : append<Pack, A0, A1> {};
        };

        template <>
        struct take_impl<3>
        {
            template <class Pack, class A0, class A1, class A2, class ...Args>
            struct apply : append<Pack, A0, A1, A2> {};
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
        
        ////////////////////////////////////////////////////////////////////
        template <class T, std::size_t N>
        struct take_value_impl;

        template <class T>
        struct take_value_impl<T, 0>
        {
            template <class Pack, T ...Args>
            struct apply : aux::no_decay< Pack > {};
        };

        template <class T>
        struct take_value_impl<T, 1>
        {
            template <class Pack, T A0, T ...>
            struct apply : append_c<Pack, T, A0> {};
        };

        template <class T>
        struct take_value_impl<T, 2>
        {
            template <class Pack, T A0, T A1, T ...>
            struct apply : append_c<Pack, T, A0, A1> {};
        };

        template <class T>
        struct take_value_impl<T, 3>
        {
            template <class Pack, T A0, T A1, T A2, T ...>
            struct apply : append_c<Pack, T, A0, A1, A2> {};
        };

        template <class T, std::size_t N>
        struct take_value_impl
        {
            template <
                class Pack
              , T A0, T A1, T A2, T A3
              , T ...Args
              >
            using apply = typename take_value_impl<T, N-4>::template
              apply< 
                  typename append_c<Pack, T, A0, A1, A2, A3>::type
                , Args...
                >;
        };
    }                                                       // namespace detail

    ////////////////////////////////////////////////////////////////////////////
    // params::take
    template <class P, std::size_t N>
    struct take
    {
        static_assert(
            aux::never<P>::value
          , "Cannot instantiate default params::take"
        );
    };

    template <
        template <class...> class Pack, class ...As
      , std::size_t N
      >
    struct take< Pack<As...>, N >
      : detail::take_impl<N>::template apply<Pack<>, As...>
    {
        static_assert(sizeof...(As) >= N, "Invalid params to take");
    };

    template <class Pack, class ...As, std::size_t N>
    struct take< Pack(As...), N >
      : detail::take_impl<N>::template apply<Pack(), As...>
    {};
    
    template <
        template <class Tv, Tv ...> class Pack
      , class T, T ...Values
      , std::size_t N
      >
    struct take< Pack<T, Values...>, N>
      : detail::take_value_impl<T, N>::template apply<Pack<T>, Values...>
    {
        static_assert(sizeof...(Values) >= N, "Invalid params to take");
    };

    ////////////////////////////////////////////////////////////////////////////
    // params::take_
    template <class Pack, std::size_t N>
    using take_t = typename take<Pack, N>::type;

    namespace detail
    {
        ////////////////////////////////////////////////////////////////////
        template <class Pack, class Ignored>
        struct drop_impl_1_;

        template <class Pack, class ...Ignored>
        struct drop_impl_1_< Pack, param_pack<Ignored...> >
        {
            template <class ...Back>
            static typename append< Pack, typename Back::type... >::type 
            eval(aux::any_pod<Ignored>..., Back*...);
        };

        ////////////////////////////////////////////////////////////////////
        template <std::size_t N, class Pack, class ...Args>
        using drop_impl = 
            decltype(
              drop_impl_1_< Pack, typename fill<N, decltype(nullptr)>::type>
                ::eval(static_cast<aux::no_decay<Args>*>(nullptr)...)
              );
    }                                               // namespace detail

    ////////////////////////////////////////////////////////////////////////////
    // params::drop
    template <class P, std::size_t N>
    struct drop;
    

    template <
        template <class...> class Pack, class ...As
      , std::size_t N
      >
    struct drop< Pack<As...>, N >
    {
        using type = detail::drop_impl<N, Pack<>, As...>;
            
        static_assert(
            N <= sizeof...(As)
          , "Index out of range"
        );
    };
    
    
    

    template <class Pack, class ...As, std::size_t N>
    struct drop< Pack(As...), N >
    {
    private:
        using result = drop<param_pack<As...>, N>;

    public:
        using type = typename convert_to_tag_pack<Pack, typename result::type>::type;
            
        static_assert(
            N <= sizeof...(As)
          , "Index out of range"
        );
    };
    
    
    
    
    template <
        template <class Tv, Tv ...> class Pack
      , class T, T ...Values
      , std::size_t N
      >
    struct drop< Pack<T, Values...>, N >
    {
    private:
        using result = drop<param_pack_c<T, Values...>, N>;

    public:
        using type = typename convert_to_value_pack<Pack, T, typename result::type>::type;
        
        static_assert(
            N <= sizeof...(Values)
          , "Index out of range"
        );
    };

    ////////////////////////////////////////////////////////////////////////////
    // params::drop
    template <class Pack, std::size_t N>
    using drop_t = typename drop<Pack, N>::type;

    ////////////////////////////////////////////////////////////////////////////
    // params::pop_front
    template <class P>
    using pop_front = drop<P, 1>;

    ////////////////////////////////////////////////////////////////////////////
    // params::pop_front_
    template <class P>
    using pop_front_t = drop_t<P, 1>;

    ////////////////////////////////////////////////////////////////////////////
    // params::pop_back
    template <class P>
    using pop_back = take<P, params::size<P>::value - 1>;

    ////////////////////////////////////////////////////////////////////////////
    // params::pop_back_t
    template <class P>
    using pop_back_t = take_t<P, params::size<P>::value - 1>;

    ////////////////////////////////////////////////////////////////////////////
    // params::slice
    template <class P, std::size_t First, std::size_t Last>
    struct slice
        : take< drop_t<P, First>, (Last - First) >
    {};

    ////////////////////////////////////////////////////////////////////////////
    // params::slice_t
    template <class P, std::size_t First, std::size_t Second>
    using slice_t = typename slice<P, First, Second>::type;

}}}                                               // namespace elib::params::v1
#endif /* ELIB_PARAMS_HPP */