#ifndef ELIB_MP_HAS_TYPE_HPP
# define ELIB_MP_HAS_TYPE_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      
      
      template <class T>
      struct has_type_impl
      {
      private:
        
        template <class _T>
        static true_ test(typename _T::type*);
        
        template <class _T>
        static false_ test(...);
        
      public:
        
        typedef decltype(test<T>(0)) type;
        
      };                                                // struct has_type_impl
      
    }                                                       // namespace detail
    
    
    template <class T>
    struct has_type : detail::has_type_impl<T>::type
    {};
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_HAS_TYPE_HPP */