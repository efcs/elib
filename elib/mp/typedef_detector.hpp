#ifndef ELIB_MP_TYPEDEF_DETECTOR_HPP
#define ELIB_MP_TYPEDEF_DETECTOR_HPP

# include <elib/mp/detail/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      
      template <class T, template <class> class Test>
      struct typedef_detector_impl
      {
      private:
        template <class U>
        static true_ test(Test<U>*);
        
        template <class>
        static false_ test(...);

      public:
        using type = decltype( test<T>(0) );
      };
      
      
    //-------------------------------- common tests ---------------------------// 
  
      template <class T>
      using type_typedef_test = typename T::type;
      
      template <class T>
      using size_typedef_test = typename T::size;
      
      template <class T>
      using apply_typedef_test = typename T::apply;
      
      template <class T>
      using concepts_typedef_test = typename T::concepts;
      
      template <class T>
      using next_typedef_test = typename T::next;
      
      template <class T>
      using prior_typedef_test = typename T::prior;
      
      template <class T>
      using item_typedef_test = typename T::item;
      
      template <class T>
      using value_type_typedef_test = typename T::value_type;
      
      template <class T>
      using tag_typedef_test = typename T::tag;
      
      template <class T>
      using category_typedef_test = typename T::category;
    
    }                                                       // namespace detail
    
    
    template <class T, template <class> class Test>
    using typedef_detector = 
      typename detail::typedef_detector_impl<T, Test>::type;
      
      
    template <class T>
    using has_type_typedef = 
      typedef_detector<T, detail::type_typedef_test>;
    
    
    template <class T>
    using has_size_typedef = 
      typedef_detector<T, detail::size_typedef_test>;
    
    
    template <class T>
    using has_apply_typedef = 
      typedef_detector<T, detail::apply_typedef_test>;
    
    
    template <class T>
    using has_concepts_typedef = 
      typedef_detector<T, detail::concepts_typedef_test>;
    
    
    template <class T>
    using has_next_typedef = 
      typedef_detector<T, detail::next_typedef_test>;
    
    
    template <class T>
    using has_prior_typedef = 
      typedef_detector<T, detail::prior_typedef_test>;
    
    
    template <class T>
    using has_item_typedef = 
      typedef_detector<T, detail::item_typedef_test>;
    
    
    template <class T>
    using has_value_type_typedef = 
      typedef_detector<T, detail::value_type_typedef_test>;
    
    
    template <class T>
    using has_tag_typedef = 
      typedef_detector<T, detail::tag_typedef_test>;
    
    
    template <class T>
    using has_category_typedef = 
      typedef_detector<T, detail::category_typedef_test>;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPEDEF_DETECTOR_HPP */