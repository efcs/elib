#ifndef ELIB_MP_DETAIL_HAS_TAG_HPP
#define ELIB_MP_DETAIL_HAS_TAG_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
    //-------------------------------- has_tag_impl -------------------------// 
      
      template <class T>
      struct has_tag_impl
      {
      private:
        template <class U>
        static true_ test(typename U::tag*);
        
        template <class U>
        static false_ test(...);

      public:
        using type = decltype(test<T>(0));
      };
      
    //-------------------------------- has_tag ------------------------------// 
    
      template <class T>
      struct has_tag : has_tag_impl<T>::type
      {};
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_HAS_TAG_HPP */