#ifndef ELIB_MP_INTRINSIC_PUSH_BACK_HPP
#define ELIB_MP_INTRINSIC_PUSH_BACK_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/detail/has_type.hpp>
# include <type_traits>

namespace elib
{
  namespace mp
  {
  //-------------------------------- push_back ------------------------------// 
  
    template <class Seq, class T>
    struct push_back
      : detail::push_back_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, T>
    {};
    
    template <class Seq, class T>
    using push_back_t = typename push_back<Seq, T>::type;
  
  //-------------------------------- has_push_back --------------------------// 
    
    template <class Seq>
    struct has_push_back 
      : detail::has_push_back_impl<sequence_tag_t<Seq>>
          ::template apply<Seq>
    {};
    
      
    template <class Seq>
    using has_push_back_t = typename has_push_back<Seq>::type;
  
    
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
      // No default impl
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
#endif /* ELIB_MP_INTRINSIC_PUSH_BACK_HPP */