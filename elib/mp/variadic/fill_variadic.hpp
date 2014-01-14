#ifndef ELIB_MP_VARIADIC_FILL_VARIADIC_HPP
#define ELIB_MP_VARIADIC_FILL_VARIADIC_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/join.hpp>

namespace elib 
{
  namespace mp
  {
  
    template <std::size_t N, class T, class List = detail::basic_pack<>>
    using variadic_fill_t = typename variadic_fill<N, T, List>::type;
    
    template <std::size_t N, class T, class Seq>
    struct variadic_fill
      : variadic_join<
          variadic_fill_t<(N / 2), T, Seq>
        , variadic_fill_t<(N - (N/2)), T, Seq>
        >
    {};
    
  //-------------------------------- base cases -----------------------------// 
    
    template <class T, class Seq>
    struct variadic_fill<0, T, Seq>
    {
      using type = Seq;
    };
    
    template <class T, template <class...> class Seq>
    struct variadic_fill<1, T, Seq<>>
    {
      using type = Seq<T>;
    };
    
    template <class T, class Seq>
    struct variadic_fill<1, T, Seq()>
    {
      using type = Seq(T);
    };
    
    template <class T, template <class...> class Seq>
    struct variadic_fill<2, T, Seq<>>
    {
      using type = Seq<T, T>;
    };
    
    template <class T, class Seq>
    struct variadic_fill<2, T, Seq()>
    {
      using type = Seq(T, T);
    };
    
    template <class T, template <class...> class Seq>
    struct variadic_fill<3, T, Seq<>>
    {
      using type = Seq<T, T, T>;
    };
    
    template <class T, class Seq>
    struct variadic_fill<3, T, Seq()>
    {
      using type = Seq(T, T, T);
    };
    
    template <class T, template <class...> class Seq>
    struct variadic_fill<4, T, Seq<>>
    {
      using type = Seq<T, T, T, T>;
    };
    
    template <class T, class Seq>
    struct variadic_fill<4, T, Seq()>
    {
      using type = Seq(T, T, T, T);
    };
    
    template <class T, template <class...> class Seq>
    struct variadic_fill<5, T, Seq<>>
    {
      using type = Seq<T, T, T, T, T>;
    };
    
    template <class T, class Seq>
    struct variadic_fill<5, T, Seq()>
    {
      using type = Seq(T, T, T, T, T);
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_FILL_VARIADIC_HPP */