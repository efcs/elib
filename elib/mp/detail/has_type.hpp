#ifndef ELIB_MP_DETAIL_HAS_TYPE_HPP
#define ELIB_MP_DETAIL_HAS_TYPE_HPP


# include <elib/mp/types/bool.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
    //-------------------------------- has_type_impl ------------------------// 
      
      template <class T>
      struct has_type_impl
      {
      private:
        
        template <class _T>
        static true_ test(typename _T::type*);
        
        template <class _T>
        static false_ test(...);
        
      public:
        using type = decltype(test<T>(0));
      };                                                // struct has_type_impl
      
    
    //-------------------------------- has_type -----------------------------// 
      
      template <class T>
      struct has_type : has_type_impl<T>::type
      {};
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_HAS_TYPE_HPP */