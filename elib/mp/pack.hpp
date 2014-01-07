#ifndef ELIB_MP_PACK_HPP
#define ELIB_MP_PACK_HPP

# include <elib/mp/variadic_pack.hpp>
# include <elib/mp/fill_variadic.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/iterator/default_random_access_iterator.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
   
    struct pack_tag {};
    
    struct pack_model_tag
      : model::mpl_sequence
      , model::variadic_sequence
      , model::back_extensible_variadic_sequence
    {};
   
    
    template <class ...Args>
    struct pack
    {
      using type = pack;
      
      using class_type = pack_tag;
      using model_type = pack_model_tag;
    };
    
    
    template <class T, T ...Values>
    using pack_c = pack< integral_constant<T, Values>... >;
    
    
    template <class Pack, std::size_t N>
    using pack_iterator = default_random_access_iterator<Pack, N>;
    
    
    template <class T, std::size_t N>
    using make_pack = fill_variadic<pack, T, N>;
    
    
    template <class T, std::size_t N>
    using make_pack_t = typename fill_variadic<pack, T, N>::type;
    
    
    template <class ...Args>
    struct get_impl< pack<Args...> >
    {
      using type = variadic_pack_intrinsics<>;
    };
    
  }                                                         // namespace pack
}                                                           // namespace elib
#endif /* ELIB_MP_PACK_HPP */