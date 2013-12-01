#ifndef ELIB_MP_HAS_APPLY_HPP
#define ELIB_MP_HAS_APPLY_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      
      template <class T>
      struct has_apply_impl
      {
      private:
        
        template <class _T>
        static true_ test(typename _T::apply*);
        
        template <class _T>
        static false_ test(...);
        
      public:
        
        typedef decltype(test<T>(0)) type;
        
      };
                                                      // struct has_apply_impl
      
    }                                                       // namespace detail
    
    
    template <class T>
    struct has_apply : detail::has_apply_impl<T>::type
    {};
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_HAS_APPLY_HPP */