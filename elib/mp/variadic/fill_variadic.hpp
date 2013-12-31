#ifndef ELIB_MP_VARIADIC_FILL_VARIADIC_HPP
#define ELIB_MP_VARIADIC_FILL_VARIADIC_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/join.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <template <class...> class Seq, class T, std::size_t N>
    struct fill_variadic;
    
    template <template <class...> class Seq, class T, std::size_t N>
    using fill_variadic_t = typename fill_variadic<Seq, T, N>::type;
    
    
    template <template <class...> class Seq, class T, std::size_t N>
    struct fill_variadic
      : variadic_join<
          fill_variadic_t<Seq, T, (N / 2)>
        , fill_variadic_t<Seq, T, (N - (N / 2))>
        >
    {};
    
  //-------------------------------- base cases -----------------------------// 
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 0>
    {
      using type = Seq<>;
    };
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 1>
    {
      using type = Seq<T>;
    };
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 2>
    {
      using type = Seq<T, T>;
    };
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 3>
    {
      using type = Seq<T, T, T>;
    };
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 4>
    {
      using type = Seq<T, T, T, T>;
    };
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 5>
    {
      using type = Seq<T, T, T, T, T>;
    };
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 6>
    {
      using type = Seq<T, T, T, T, T, T>;
    };
    
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 7>
    {
      using type = Seq<T, T, T, T, T, T, T>;
    };
    
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 8>
    {
      using type = Seq<T, T, T, T, T, T, T, T>;
    };
    
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 9>
    {
      using type = Seq<T, T, T, T, T, T, T, T, T>;
    };
    
    
    template <template <class...> class Seq, class T>
    struct fill_variadic<Seq, T, 10>
    {
      using type = Seq<T, T, T, T, T, T, T, T, T, T>;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_FILL_VARIADIC_HPP */