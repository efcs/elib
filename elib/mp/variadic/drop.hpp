#ifndef ELIB_MP_VARIADIC_DROP_HPP
#define ELIB_MP_VARIADIC_DROP_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/fill_variadic.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/detail/eat_pod.hpp>
# include <cstddef>


namespace elib 
{
  namespace mp
  {
    
    template <
        class Seq, std::size_t N
      , template <class...> class Pack /* = detail::basic_pack */
      >
    struct variadic_drop;
    
    
    template <
        template <class...> class Seq
      , class ...Args
      , std::size_t N
      , template <class...> class Pack
      >
    struct variadic_drop< Seq<Args...>, N, Pack>
    {
      using type = decltype(
        detail::variadic_drop_impl< 
            fill_variadic_t<Pack, decltype(nullptr), N>
          , Seq
          >
        ::eval((identity<Args>*)nullptr...)
      );
    };
    
    
    template <
        class Seq
      , std::size_t N
      , template <class...> class Pack = detail::basic_pack
      >
    using variadic_drop_t = typename variadic_drop<Seq, N, Pack>::type;
    
    
    namespace detail
    {
      
      template <
          template <class...> class Seq
        , class ...Ignored
        , template <class...> class To
        >
      struct variadic_drop_impl< Seq<Ignored...>, To>
      {
        template <class ...Back>
          static To<typename Back::type...>
        eval(eat_pod<Ignored>..., Back*...);
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_DROP_HPP */