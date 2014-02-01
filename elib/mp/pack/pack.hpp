#ifndef ELIB_MP_PACK_PACK_HPP
#define ELIB_MP_PACK_PACK_HPP

# include <elib/mp/pack/pack_intrinsics.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/iterator/default_random_access_iterator.hpp>
# include <elib/aux.hpp>
# include <elib/params.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
   
    struct pack_tag {};

    struct pack_model
      : model::variadic
      , model::random_access_sequence
      , model::front_extensible_variadic_sequence
      , model::back_extensible_variadic_sequence
      , model::O1_size
    {};
   
    template <class ...Args>
    struct pack
    {
      using type = pack;
      
      using class_type = pack_tag;
      using model_type = pack_model;
    };
    
    
    template <class T, T ...Values>
    using pack_c = pack< integral_constant<T, Values>... >;
    
    
    template <class Pack, std::size_t N>
    using pack_iterator = default_random_access_iterator<Pack, N>;
    
    
    template <class T, std::size_t N>
    using make_pack = params::fill<N, T, pack<>>;
    
    
    template <class T, std::size_t N>
    using make_pack_t = typename params::fill<N, T, pack<>>::type;
    
    
    template <class ...Args>
    struct get_impl< pack<Args...> >
    {
      using type = pack_intrinsics;
    };
    
  }                                                         // namespace pack
}                                                           // namespace elib
#endif /* ELIB_MP_PACK_PACK_HPP */