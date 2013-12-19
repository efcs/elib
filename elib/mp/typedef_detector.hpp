#ifndef ELIB_MP_TYPEDEF_DETECTOR_HPP
#define ELIB_MP_TYPEDEF_DETECTOR_HPP

# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/void.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T, template <class> class Test>
    struct typedef_detector
    {
    private:
      template <class U>
      static pair<true_, Test<U>> test(Test<U>*);
      
      template <class>
      static pair<false_, void_> test(...);

    public:
      using result_type = decltype( test<T>(0) );
      using type = first_t<result_type>;
      using value_type = second_t<result_type>;
    };
    
    
    template <class T, template <class> class Test>
    using typedef_detected = typename typedef_detector<T, Test>::type;
    
    template <class T, template <class> class Test>
    using detected_typedef_t = typename typedef_detector<T, Test>::value_type;
    
    template <class T, template <class> class Test>
    using detected_typedef = identity< detected_typedef_t<T, Test> >;
      
    
# define ELIB_MP_DETECT_HELPER_(name)                 \
                                                      \
  namespace detail {                                  \
    template <class T>                                \
    using name##_typedef_test = typename T::name;     \
  }                                                   \
  template <class T> using has_##name##_typedef =     \
    typedef_detected<T, detail::name##_typedef_test>; \
                                                      \
  template <class T> using name##_typedef =           \
    detected_typedef<T, detail::name##_typedef_test>; \
                                                      \
  template <class T> using name##_typedef_t =         \
    detected_typedef_t<T, detail::name##_typedef_test>

    
    ELIB_MP_DETECT_HELPER_(type);
    ELIB_MP_DETECT_HELPER_(value_type);
    ELIB_MP_DETECT_HELPER_(result_type);
    ELIB_MP_DETECT_HELPER_(item);
    ELIB_MP_DETECT_HELPER_(base);
    ELIB_MP_DETECT_HELPER_(tag);
    ELIB_MP_DETECT_HELPER_(category);
    ELIB_MP_DETECT_HELPER_(apply);
    ELIB_MP_DETECT_HELPER_(next);
    ELIB_MP_DETECT_HELPER_(prior);
    ELIB_MP_DETECT_HELPER_(begin);
    ELIB_MP_DETECT_HELPER_(end);
    
    
# undef ELIB_MP_DETECT_HELPER_

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPEDEF_DETECTOR_HPP */