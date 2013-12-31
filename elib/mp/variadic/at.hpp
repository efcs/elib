#ifndef ELIB_MP_VARIADIC_AT_HPP
#define ELIB_MP_VARIADIC_AT_HPP

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
    struct variadic_at;
      
      
    template <
        template <class...> class Seq
      , class ...Args
      , std::size_t N
      , template <class...> class Pack
      >
    struct variadic_at< Seq<Args...>, N, Pack>
    {
      using type = decltype(
        detail::variadic_at_impl< 
            fill_variadic_t<Pack, decltype(nullptr), N>
          >
          ::eval((identity<Args>*)nullptr...)
        );
    };
      
      
    template <
        class Seq
      , std::size_t N
      , template <class...> class Pack = detail::basic_pack
      >
    using variadic_at_t = typename variadic_at<Seq, N, Pack>::type;
      
      
    namespace detail
    {
      
      template <template <class...> class Seq, class ...Ignored>
      struct variadic_at_impl< Seq<Ignored...> >
      {
        template <class T, class ...Rest>
          static typename T::type 
        eval(eat_pod<Ignored>..., T*, Rest*...);
        
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_AT_HPP */