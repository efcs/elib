#ifndef ELIB_MP_MEMBER_TEMPLATE_DETECTOR_HPP
#define ELIB_MP_MEMBER_TEMPLATE_DETECTOR_HPP

# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/void.hpp>


namespace elib 
{
  namespace  mp
  {
    
    template <template <class, class...> class Detector>
    struct member_template_detector
    {
      template <class U, class ...Args>
      static pair<true_, Detector<U, Args...>> test_(int);
      
      template <class...>
      static pair<false_, void_> test_(...);
      
      template <class T, class ...Args>
      using result_type = decltype(test_<T, Args...>(0));
      
      template <class T, class ...Args>
      using type = first_t<decltype(test_<T, Args...>(0))>;
      
      template <class T, class ...Args>
      using value_type = second_t<decltype(test_<T, Args...>(0))>;
    };
    
    
    template <class T, template <class, class...> class Test, class ...Args>
    using has_member_template = 
      typename member_template_detector<Test>::template type<T, Args...>;

      
    template <class T, template <class, class...> class Test, class ...Args>
    using member_template_t = 
      typename member_template_detector<Test>::template value_type<T, Args...>;
    
    
    template <class T, template <class, class...> class Test, class ...Args>
    using member_template = identity< member_template_t<T, Test, Args...> >;
    
    
    
  }                                                         // namespace  mp
}                                                           // namespace elib
#endif /* ELIB_MP_MEMBER_TEMPLATE_DETECTOR_HPP */