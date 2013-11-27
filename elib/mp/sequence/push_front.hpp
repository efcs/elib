#ifndef ELIB_MP_SEQUENCE_PUSH_FRONT_HPP
# define ELIB_MP_SEQUENCE_PUSH_FRONT_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/detail/has_type.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
    //-------------------------------- push_front_dummy ---------------------// 
      
      struct push_front_dummy {};
      
    //-------------------------------- has_push_front_impl ------------------// 
      
      template <class Tag>
      struct has_push_front_impl
      {
        template <class Seq>
        struct apply
          : has_type< push_front<Seq, push_front_dummy> >
        {};
      };
      
    //-------------------------------- push_front_impl ----------------------// 
    
      template <class Tag>
      struct push_front_impl
      {
        template <class Seq, class T>
        struct apply
        {
          static_assert( std::is_same<T, push_front_dummy>::value,
              "No default implementation provided for push_front");
        };
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_PUSH_FRONT_HPP */