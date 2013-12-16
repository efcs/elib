#ifndef ELIB_MP_OPTIMIZATION_HPP
#define ELIB_MP_OPTIMIZATION_HPP

namespace elib 
{
  namespace mp
  {
    
    struct optimization_tag {};
    
# if 0 && EXAMPLE_USAGE
    struct test_class
    {
      using O1_SIZE_OPTIMIZATION = optimization_tag;
    };
# endif
    
    namespace detail
    {
        
      template <template <class> class Test, class T>
      struct optimization_detector
      {
      private:
        template <class U>
        static true_ test(Test<U>*);
        
        template <class U>
        static false_ test(...);
        
      public:
        using type = decltype(test<T>(0));
      };
      
      template <template <class> class Test, class T>
      using optimization_detector_t = 
        typename optimization_detector<Test, T>::type;
      
      template <class T>
      using O1_size_test = typename T::O1_SIZE_OPTIMIZATION;
      
    }                                                       // namespace detail
    
    template <class T>
    using has_O1_size_optimization = 
      detail::optimization_detector_t<
          detail::O1_size_test
        , T
      >;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_OPTIMIZATION_HPP */