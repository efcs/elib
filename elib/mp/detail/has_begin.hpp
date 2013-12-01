#ifndef ELIB_MP_DETAIL_HAS_BEGIN_HPP
#define ELIB_MP_DETAIL_HAS_BEGIN_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
     
    //-------------------------------- has_begin_impl -----------------------// 
      
      template <class T>
      struct has_begin_impl
      {
      private:
        
        template <class U>
        static true_ test(typename U::begin*);
        
        template <class U>
        static false_ test(...);

      public:
        using type = decltype(test<T>(0));
      };
      
    //-------------------------------- has_begin ----------------------------// 
  
      template <class T>
      struct has_begin : has_begin_impl<T>::type
      {};
      
    }                                                       // namespace detail    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_HAS_BEGIN_HPP */