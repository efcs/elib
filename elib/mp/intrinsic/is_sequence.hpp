#ifndef ELIB_MP_INTRINSIC_IS_SEQUENCE_HPP
#define ELIB_MP_INTRINSIC_IS_SEQUENCE_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/intrinsic/begin_end.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/void.hpp>
# include <type_traits>

namespace elib
{
  namespace mp
  {
  //-------------------------------- is_sequence ----------------------------//
  
    template <class T>
    struct is_sequence
      : detail::is_sequence_impl<sequence_tag_t<T>> 
          ::template apply<T>
    {};
    
    
    template <class T>
    using is_sequence_t = typename is_sequence<T>::type;
    
    
    namespace detail
    {
    //-------------------------------- is_sequence_impl ---------------------// 
      
      template <class Tag>
      struct is_sequence_impl
      {
        template <class T>
        struct apply
        { using type = typename not_< std::is_same<T, void_> >::type; };
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTRINSIC_IS_SEQUENCE_HPP */