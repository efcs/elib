#ifndef ELIB_MP_INTRINSIC_PUSH_FRONT_HPP
#define ELIB_MP_INTRINSIC_PUSH_FRONT_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/detail/has_type.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- push_front -----------------------------//
  
    template <class Seq, class T>
    struct push_front
      : detail::push_front_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, T>
    {};
    
     
    template <class Seq, class T>
    using push_front_t = typename push_front<Seq, T>::type;
  
  //-------------------------------- has_push_front -------------------------// 
    
    template <class Seq>
    struct has_push_front
      : detail::has_push_front_impl<sequence_tag_t<Seq>>
          ::template apply<Seq>
    {};
    
    
    template <class Seq, class T>
    using has_push_front_t = typename has_push_front<Seq>::type;
  
    
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
    
      /* Method for implementation checking stolen from boost::mpl */
      // No default Impl
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
#endif /* ELIB_MP_INTRINSIC_PUSH_FRONT_HPP */