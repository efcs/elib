#ifndef ELIB_MP_PACK_MAKE_PACK_HPP
#define ELIB_MP_PACK_MAKE_PACK_HPP

# include <elib/mp/pack/pack.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      template <class Left, class Right>
      struct pack_concat;
      
      template <class ...Left, class ...Right>
      struct pack_concat< pack<Left...>, pack<Right...> >
      {
        using type = pack<Left..., Right...>;
      };
    }                                                       // namespace detail
  
    template <class T, std::size_t N = 1>
    struct make_pack;
    
    template <class T, std::size_t N = 1>
    using make_pack_t = typename make_pack<T, N>::type;
    
    
    template <class T, std::size_t N>
    struct make_pack 
      : detail::pack_concat<
          make_pack<T, (N / 2) >
        , make_pack<T, (N - (N / 2))>
      >
    {};
    
    
    template <class T>
    struct make_pack<T, 0>
    { 
      using type = pack<>;
    };
    
    
    template <class T>
    struct make_pack<T, 1>
    {
      using type = pack<T>;
    };
    
    template <class T>
    struct make_pack<T, 2>
    {
      using type = pack<T, T>;
    };
    
    template <class T>
    struct make_pack<T, 3>
    {
      using type = pack<T, T, T>;
    };
    
    template <class T>
    struct make_pack<T, 4>
    {
      using type = pack<T, T, T, T>;
    };
    
    template <class T>
    struct make_pack<T, 5>
    {
      using type = pack<T, T, T, T, T>;
    };
    
    template <class T>
    struct make_pack<T, 6>
    {
      using type = pack<T, T, T, T, T, T>;
    };
    
    template <class T>
    struct make_pack<T, 7>
    {
      using type = pack<T, T, T, T, T, T, T>;
    };
    
    template <class T>
    struct make_pack<T, 8>
    {
      using type = pack<T, T, T, T, T, T, T, T>;
    };
    
    template <class T>
    struct make_pack<T, 9>
    {
      using type = pack<T, T, T, T, T, T, T, T, T>;
    };
    
    template <class T>
    struct make_pack<T, 10>
    {
      using type = pack<T, T, T, T, T, T, T, T, T, T>;
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PACK_MAKE_PACK_HPP */