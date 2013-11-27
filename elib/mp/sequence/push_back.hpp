#ifndef ELIB_MP_SEQUENCE_PUSH_BACK_HPP
#define ELIB_MP_SEQUENCE_PUSH_BACK_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/detail/has_type.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
      
    //-------------------------------- push_back_dummy ----------------------// 
    
      struct push_back_dummy {};
      
    //-------------------------------- has_push_back_impl -------------------// 
      
      template <class Tag>
      struct has_push_back_impl 
      {
        template <class Seq>
        struct apply 
          : detail::has_type< push_back<Seq, push_back_dummy> >
        {};
      };

    //-------------------------------- push_back_impl -----------------------// 
      
      /* Implementation checking shamelessly stolen from boost::mpl */
      template <class Tag>
      struct push_back_impl
      {
        template <class Seq, class T>
        struct apply
        {
          static_assert( std::is_same<push_back_dummy, T>::value, 
                "No default implementation of push_back provided");
        };
      };
      
    

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_PUSH_BACK_HPP */