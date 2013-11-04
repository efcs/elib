#ifndef ELIB_ETL_BASIC_DETECTOR_HPP
# define ELIB_ETL_BASIC_DETECTOR_HPP

# include <elib/etl/config.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace etl
  {
    
    namespace detail
    {
      
      template <class T, template <class U> class Detector>
      struct _basic_detector
      {
      private:
        
        template <class _T>
        static std::true_type test(Detector<_T>*);
        
        template <class _T>
        static std::false_type test(...);

      public:
        
        typedef decltype(test<T>(0)) type;
        
      };
      
    }                                                       // namespace detail
    
    
    template <class T, template <class U> class Detector>
    struct basic_detector : detail::_basic_detector<T, Detector>::type
    { };
    
   
  }                                                           // namespace etl
}                                                           // namespace elib
#endif /* ELIB_ETL_BASIC_DETECTOR_HPP */