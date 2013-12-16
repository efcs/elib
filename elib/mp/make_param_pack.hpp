#ifndef ELIB_MP_MAKE_PARAM_PACK_HPP
#define ELIB_MP_MAKE_PARAM_PACK_HPP

# include <elib/mp/param_pack/param_pack.hpp>
# include <elib/mp/param_pack/param_pack_concat.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {

    template <class T, std::size_t N = 1>
    struct make_param_pack;
    
    
    template <class T, std::size_t N>
    struct make_param_pack 
      : param_pack_concat<
          make_param_pack<T, (N / 2) >
        , make_param_pack<T, (N - (N / 2))>
      >
    {};
    
    
    template <class T>
    struct make_param_pack<T, 0>
    { 
      using type = param_pack<>;
    };
    
    
    template <class T>
    struct make_param_pack<T, 1>
    {
      using type = param_pack<T>;
    };
    
    template <class T>
    struct make_param_pack<T, 2>
    {
      using type = param_pack<T, T>;
    };
    
    template <class T>
    struct make_param_pack<T, 3>
    {
      using type = param_pack<T, T, T>;
    };
    
    template <class T>
    struct make_param_pack<T, 4>
    {
      using type = param_pack<T, T, T, T>;
    };
    
    template <class T>
    struct make_param_pack<T, 5>
    {
      using type = param_pack<T, T, T, T, T>;
    };
    
    template <class T>
    struct make_param_pack<T, 6>
    {
      using type = param_pack<T, T, T, T, T, T>;
    };
    
    template <class T>
    struct make_param_pack<T, 7>
    {
      using type = param_pack<T, T, T, T, T, T, T>;
    };
    
    template <class T>
    struct make_param_pack<T, 8>
    {
      using type = param_pack<T, T, T, T, T, T, T, T>;
    };
    
    template <class T>
    struct make_param_pack<T, 9>
    {
      using type = param_pack<T, T, T, T, T, T, T, T, T>;
    };
    
    template <class T>
    struct make_param_pack<T, 10>
    {
      using type = param_pack<T, T, T, T, T, T, T, T, T, T>;
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_MAKE_PARAM_PACK_HPP */