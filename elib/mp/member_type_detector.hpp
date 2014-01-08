#ifndef ELIB_MP_MEMBER_TYPE_DETECTOR_HPP
#define ELIB_MP_MEMBER_TYPE_DETECTOR_HPP

# include <elib/mp/identity.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/void.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <template <class> class Test>
    struct member_type_detector
    {
      template <class U>
      static pair<true_, Test<U>> test_(int);
      
      template <class>
      static pair<false_, void_> test_(...);
      
      /* dec, 24, 2013: GCC shits bricks if you attempt
       * to use result_type<T> in type or value_type aliases
       * workaround is to always call test_
       */
      template <class T>
      using result_type = decltype( test_<T>(0) );
      
      template <class T>
      using type = first_t< decltype(test_<T>(0)) >;
      
      template <class T>
      using value_type = second_t< decltype(test_<T>(0)) >;
    };
    
    
    template <class T, template <class> class Test>
    using has_member_type = 
      typename member_type_detector<Test>::template type<T>;
    
    template <class T, template <class> class Test>
    using member_type_t = 
      typename member_type_detector<Test>::template value_type<T>;
    
    template <class T, template <class> class Test>
    using member_type = identity< member_type_t<T, Test> >;
      
    
# define ELIB_MP_DETECT_HELPER_(name)                    \
                                                         \
  namespace detail {                                     \
    template <class T>                                   \
    using name##_member_type_test = typename T::name;    \
  }                                                      \
  template <class T> using has_##name##_member_type =    \
    has_member_type<T, detail::name##_member_type_test>; \
                                                         \
  template <class T> using name##_member_type =          \
    member_type<T, detail::name##_member_type_test>;     \
                                                         \
  template <class T> using name##_member_type_t =        \
    member_type_t<T, detail::name##_member_type_test>

    
    ELIB_MP_DETECT_HELPER_(type);
    ELIB_MP_DETECT_HELPER_(value_type);
    ELIB_MP_DETECT_HELPER_(result_type);
    ELIB_MP_DETECT_HELPER_(class_type);
    ELIB_MP_DETECT_HELPER_(model_type);
    ELIB_MP_DETECT_HELPER_(item);
    ELIB_MP_DETECT_HELPER_(next);
    ELIB_MP_DETECT_HELPER_(prior);
    ELIB_MP_DETECT_HELPER_(begin);
    ELIB_MP_DETECT_HELPER_(end);
    
    
# undef ELIB_MP_DETECT_HELPER_

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_MEMBER_TYPE_DETECTOR_HPP */