#ifndef ELIB_MP_TEMPLATE_TYPEDEF_DETECTOR_HPP
#define ELIB_MP_TEMPLATE_TYPEDEF_DETECTOR_HPP

# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/void.hpp>
# include <elib/pp/overload.hpp>
# include <elib/pp/concat.hpp>

namespace elib 
{
  namespace  mp
  {
    
    template <class T, template <class, class...> class Detector>
    struct template_typedef_detector
    {
      template <class U, class ...Args>
      static pair<true_, Detector<U, Args...>> test_(int);
      
      template <class...>
      static pair<false_, void_> test_(...);
      
      template <class ...Args>
      using type = first_t<decltype(test_<T, Args...>(0))>;
    };
    
    
    template <class T, template <class, class...> class Test>
    using template_typedef_detector_t = template_typedef_detector<T, Test>;
    
    
    template <class T, template <class, class...> class Test, class ...Args>
    using has_template_typedef = 
      typename template_typedef_detector<T, Test>::template type<Args...>;
      
    
# define ELIB_MP_DETECT_HELPER_(...) \
  ELIB_PP_OVERLOAD(ELIB_MP_DETECT_HELPER_, __VA_ARGS__)(__VA_ARGS__)
# 
# 
# define ELIB_MP_DETECT_HELPER_1(name) ELIB_MP_DETECT_HELPER_I5(name)
# 
# 
# define ELIB_MP_DETECT_HELPER_2(name, arity) \
  ELIB_PP_CONCAT(ELIB_MP_DETECT_HELPER_I, arity)(name)
# 
# 
# define ELIB_MP_DETECT_HELPER_I1(name)
  
    
  }                                                         // namespace  mp
}                                                           // namespace elib
#endif /* ELIB_MP_TEMPLATE_TYPEDEF_DETECTOR_HPP */