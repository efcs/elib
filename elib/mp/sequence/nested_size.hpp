#ifndef ELIB_MP_SEQUENCE_NESTED_SIZE_HPP
#define ELIB_MP_SEQUENCE_NESTED_SIZE_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/types.hpp>
# include <elib/mp/metafunction/if.hpp>
# include <elib/mp/detail/has_size.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
    //-------------------------------- nested_size_wrapper ------------------// 
    
      template <class T>
      struct nested_size_wrapper
      {
        using type = typename T::size;
      };
      
    //-------------------------------- nested_size_impl ---------------------// 
    
      template <class Tag>
      struct nested_size_impl
      {
        template <class Seq>
        struct apply
        {
          using type = eval_if_t<has_size<Seq>
            , nested_size_wrapper<Seq>
            , long_<-1>
          >;
        };
      };                                             // struct nested_size_impl
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_NESTED_SIZE_HPP */