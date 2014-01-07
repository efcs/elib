#ifndef ELIB_MP_UNPACK_HPP
#define ELIB_MP_UNPACK_HPP

# include <elib/mp/apply.hpp>
# include <elib/mp/pack.hpp>
# include <elib/mp/sequence_traits.hpp>
# include <elib/mp/algorithm/copy.hpp>
# include <elib/mp/algorithm/inserter.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <bool IsVariadic>
      struct unpack_impl;
      
      
      template <>
      struct unpack_impl<true>
      {
        template <class F, class Seq>
        struct apply;
        
        template <class F, template <class...> class Seq, class ...Args>
        struct apply< F, Seq<Args...> >
        {
          using type = apply_t<F, Args...>;
        };
        
      };
      
      
      template <>
      struct unpack_impl<false>
      {
        template <class F, class Seq>
        using apply = 
          unpack_impl<true>::apply< 
            F
          , copy_t<Seq, back_inserter<pack<>>>
          >;
      };
    }                                                       // namespace detail
    
    template <class F>
    struct unpack
    {
      template <class Seq>
      using type = typename
        detail::unpack_impl<
            is_variadic<Seq>::type::value
          >::template
        apply<
            F, Seq
          >::type;
    };
    
    template <class T>
    using unpack_t = typename unpack<T>::type;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_UNPACK_HPP */