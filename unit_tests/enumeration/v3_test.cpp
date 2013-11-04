#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/enumeration/v3/basic_enum_traits.hpp>
#include <elib/enumeration/v3/intrusive_enum_traits.hpp>
#include <elib/enumeration/v3/enum_traits.hpp>

using namespace elib::enumeration;

enum class A
{
  none
};

enum class B
{
  none, 
  one, 
  
  ELIB_ENUM_DEFAULT_VALUE = none, 
  ELIB_ENUM_ERROR_VALUE = none, 
  
  ELIB_ENUM_FIRST_VALUE = none,
  ELIB_ENUM_LAST_VALUE = one, 
  
  ELIB_ENUM_IS_CONTIGIOUS = true, 
  ELIB_ENUM_IS_BITMASK = false, 
  ELIB_ENUM_IS_ARITHMETIC = false
};

enum class C
{
  none,
  one, 
  three = 3
};

namespace elib
{
  namespace enumeration
  {
    
    template <>
    struct basic_enum_traits<C>
    {
      static enum_map_t<C> name_map;
      
      static constexpr C ELIB_ENUM_DEFAULT_VALUE = C::none;
      static constexpr C ELIB_ENUM_ERROR_VALUE = C::none; 
  
      static constexpr C ELIB_ENUM_FIRST_VALUE = C::none;
      static constexpr C ELIB_ENUM_LAST_VALUE = C::three;
  
      static constexpr bool ELIB_ENUM_IS_CONTIGIOUS = false;
      static constexpr bool ELIB_ENUM_IS_BITMASK = true;
      static constexpr bool ELIB_ENUM_IS_ARITHMETIC = true;
    };
    
    enum_map_t<C> basic_enum_traits<C>::name_map = 
    { 
      {C::none, "none"}, 
      {C::one, "one"}, 
      {C::three, "three"}
    };
    
  }                                                    // namespace enumeration
}                                                           // namespace elib

template <typename T>
constexpr T bad_value() noexcept
{
  return static_cast<T>(-1);
}

BOOST_AUTO_TEST_SUITE(enum_v3_test_suite)

BOOST_AUTO_TEST_CASE(enum_v3_basic_enum_traits_detectors)
{
  BOOST_CHECK(has_basic_enum_traits<A>::value == false);
  BOOST_CHECK(has_basic_enum_traits<B>::value == false);
  BOOST_CHECK(has_basic_enum_traits<C>::value == true);
  
  BOOST_CHECK(has_name_map<A>::value == false);
  BOOST_CHECK(has_name_map<B>::value == false);
  BOOST_CHECK(has_name_map<C>::value == true);
}

BOOST_AUTO_TEST_CASE(meta_basic_enum_traits_test)
{
  typedef detail::meta_basic_enum_traits<A> meta_A;
  typedef detail::meta_basic_enum_traits<B> meta_B;
  typedef detail::meta_basic_enum_traits<C> meta_C;
  
  BOOST_CHECK(meta_A::has_basic_enum_traits == false);
  BOOST_CHECK(meta_B::has_basic_enum_traits == false);
  BOOST_CHECK(meta_C::has_basic_enum_traits == true);
                                
  BOOST_CHECK(meta_A::has_name_map == false);
  BOOST_CHECK(meta_B::has_name_map == false);
  BOOST_CHECK(meta_C::has_name_map == true);
  
  BOOST_CHECK(meta_A::has_default_value == false);
  BOOST_CHECK(meta_B::has_default_value == false);
  BOOST_CHECK(meta_C::has_default_value == true);
  
  BOOST_CHECK(meta_A::default_value == bad_value<A>());
  BOOST_CHECK(meta_B::default_value == bad_value<B>());
  BOOST_CHECK(meta_C::default_value == C::none);
  
  BOOST_CHECK(meta_A::has_error_value == false);
  BOOST_CHECK(meta_B::has_error_value == false);
  BOOST_CHECK(meta_C::has_error_value == true);
  
  BOOST_CHECK(meta_A::error_value == bad_value<A>());
  BOOST_CHECK(meta_B::error_value == bad_value<B>());
  BOOST_CHECK(meta_C::error_value == C::none);
  
  BOOST_CHECK(meta_A::has_first_value == false);
  BOOST_CHECK(meta_B::has_first_value == false);
  BOOST_CHECK(meta_C::has_first_value == true);
  
  BOOST_CHECK(meta_A::first_value == bad_value<A>());
  BOOST_CHECK(meta_B::first_value == bad_value<B>());
  BOOST_CHECK(meta_C::first_value == C::none);
  
  BOOST_CHECK(meta_A::has_last_value == false);
  BOOST_CHECK(meta_B::has_last_value == false);
  BOOST_CHECK(meta_C::has_last_value == true);
  
  BOOST_CHECK(meta_A::last_value == bad_value<A>());
  BOOST_CHECK(meta_B::last_value == bad_value<B>());
  BOOST_CHECK(meta_C::last_value == C::three);
  
  BOOST_CHECK(meta_A::has_is_contigious == false);
  BOOST_CHECK(meta_B::has_is_contigious == false);
  BOOST_CHECK(meta_C::has_is_contigious == true);
  
  BOOST_CHECK(meta_A::is_contigious == false);
  BOOST_CHECK(meta_B::is_contigious == false);
  BOOST_CHECK(meta_C::is_contigious == false);
  
  BOOST_CHECK(meta_A::has_is_bitmask == false);
  BOOST_CHECK(meta_B::has_is_bitmask == false);
  BOOST_CHECK(meta_C::has_is_bitmask == true);
  
  BOOST_CHECK(meta_A::is_bitmask == false);
  BOOST_CHECK(meta_B::is_bitmask == false);
  BOOST_CHECK(meta_C::is_bitmask == true);
  
  BOOST_CHECK(meta_A::has_is_arithmetic == false);
  BOOST_CHECK(meta_B::has_is_arithmetic == false);
  BOOST_CHECK(meta_C::has_is_arithmetic == true);
  
  BOOST_CHECK(meta_A::is_arithmetic == false);
  BOOST_CHECK(meta_B::is_arithmetic == false);
  BOOST_CHECK(meta_C::is_arithmetic == true);
}

BOOST_AUTO_TEST_CASE(intrusive_enum_traits_test)
{
  typedef detail::intrusive_enum_traits<A> int_A;
  typedef detail::intrusive_enum_traits<B> int_B;
  typedef detail::intrusive_enum_traits<C> int_C;
  
  BOOST_CHECK(int_A::has_default_value == false);
  BOOST_CHECK(int_B::has_default_value == true);
  BOOST_CHECK(int_C::has_default_value == false);
  
  BOOST_CHECK(int_A::default_value == bad_value<A>());
  BOOST_CHECK(int_B::default_value == B::none);
  BOOST_CHECK(int_C::default_value == bad_value<C>());
  
  BOOST_CHECK(int_A::has_error_value == false);
  BOOST_CHECK(int_B::has_error_value == true);
  BOOST_CHECK(int_C::has_error_value == false);
  
  BOOST_CHECK(int_A::error_value == bad_value<A>());
  BOOST_CHECK(int_B::error_value == B::none);
  BOOST_CHECK(int_C::error_value == bad_value<C>());
  
  BOOST_CHECK(int_A::has_first_value == false);
  BOOST_CHECK(int_B::has_first_value == true);
  BOOST_CHECK(int_C::has_first_value == false);
  
  BOOST_CHECK(int_A::first_value == bad_value<A>());
  BOOST_CHECK(int_B::first_value == B::none);
  BOOST_CHECK(int_C::first_value == bad_value<C>());
  
  BOOST_CHECK(int_A::has_last_value == false);
  BOOST_CHECK(int_B::has_last_value == true);
  BOOST_CHECK(int_C::has_last_value == false);
  
  BOOST_CHECK(int_A::last_value == bad_value<A>());
  BOOST_CHECK(int_B::last_value == B::one);
  BOOST_CHECK(int_C::last_value == bad_value<C>());
  
  BOOST_CHECK(int_A::has_is_contigious == false);
  BOOST_CHECK(int_B::has_is_contigious == true);
  BOOST_CHECK(int_C::has_is_contigious == false);
  
  BOOST_CHECK(int_A::is_contigious == false);
  BOOST_CHECK(int_B::is_contigious == true);
  BOOST_CHECK(int_C::is_contigious == false);
  
  BOOST_CHECK(int_A::has_is_bitmask == false);
  BOOST_CHECK(int_B::has_is_bitmask == true);
  BOOST_CHECK(int_C::has_is_bitmask == false);
  
  BOOST_CHECK(int_A::is_bitmask == false);
  BOOST_CHECK(int_B::is_bitmask == false);
  BOOST_CHECK(int_C::is_bitmask == false);
  
  BOOST_CHECK(int_A::has_is_arithmetic == false);
  BOOST_CHECK(int_B::has_is_arithmetic == true);
  BOOST_CHECK(int_C::has_is_arithmetic == false);
  
  BOOST_CHECK(int_A::is_arithmetic == false);
  BOOST_CHECK(int_B::is_arithmetic == false);
  BOOST_CHECK(int_C::is_arithmetic == false);
}

BOOST_AUTO_TEST_CASE(enum_traits_test)
{
  typedef enum_traits<A> traits_A;
  typedef enum_traits<B> traits_B;
  typedef enum_traits<C> traits_C;
  
  BOOST_CHECK(traits_A::has_basic_enum_traits == false);
  BOOST_CHECK(traits_B::has_basic_enum_traits == false);
  BOOST_CHECK(traits_C::has_basic_enum_traits == true);
  
  BOOST_CHECK(traits_A::has_name_map == false);
  BOOST_CHECK(traits_B::has_name_map == false);
  BOOST_CHECK(traits_C::has_name_map == true);
  
  BOOST_CHECK(traits_A::has_default_value == false);
  BOOST_CHECK(traits_B::has_default_value == true);
  BOOST_CHECK(traits_C::has_default_value == true);
  
  BOOST_CHECK(traits_A::has_error_value == false);
  BOOST_CHECK(traits_B::has_error_value == true);
  BOOST_CHECK(traits_C::has_error_value == true);
  
  BOOST_CHECK(traits_A::has_first_value == false);
  BOOST_CHECK(traits_B::has_first_value == true);
  BOOST_CHECK(traits_C::has_first_value == true);
  
  BOOST_CHECK(traits_A::has_last_value == false);
  BOOST_CHECK(traits_B::has_last_value == true);
  BOOST_CHECK(traits_C::has_last_value == true);
  
  BOOST_CHECK(traits_A::has_is_contigious == false);
  BOOST_CHECK(traits_B::has_is_contigious == true);
  BOOST_CHECK(traits_C::has_is_contigious == true);
  
  BOOST_CHECK(traits_A::has_is_bitmask == false);
  BOOST_CHECK(traits_B::has_is_bitmask == true);
  BOOST_CHECK(traits_C::has_is_bitmask == true);
  
  BOOST_CHECK(traits_A::has_is_arithmetic == false);
  BOOST_CHECK(traits_B::has_is_arithmetic == true);
  BOOST_CHECK(traits_C::has_is_arithmetic == true);
}

BOOST_AUTO_TEST_SUITE_END()