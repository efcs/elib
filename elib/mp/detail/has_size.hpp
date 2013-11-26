#ifndef ELIB_MP_DETAIL_HAS_SIZE_HPP
#define ELIB_MP_DETAIL_HAS_SIZE_HPP

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
    //-------------------------------- has_size_impl ------------------------// 
      
      template <class T>
      struct has_size_impl
      {
      private:
        
        template <class U>
        static true_ test(typename U::size*);
        
        template <class U>
        static false_ test(...);
        
      public:
        using type = decltype(test<T>(0));
      };
      
    //-------------------------------- has_size -----------------------------// 
    
      template <class T>
      struct has_size : has_size_impl<T>::type
      {};
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_HAS_SIZE_HPP */