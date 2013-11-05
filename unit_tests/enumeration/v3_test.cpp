#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/enumeration/v3/enum_traits.hpp>
#include <elib/enumeration/v3/enum_cast.hpp>
#include <elib/enumeration/v3/operators.hpp>

#include <string>

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
  ELIB_ENUM_IS_ARITHMETIC = false, 
  ELIB_ENUM_IS_LOGICAL = false
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
      static constexpr bool ELIB_ENUM_IS_LOGICAL = true;
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
  
  BOOST_CHECK(meta_A::has_is_logical == false);
  BOOST_CHECK(meta_B::has_is_logical == false);
  BOOST_CHECK(meta_C::has_is_logical == true);
  
  BOOST_CHECK(meta_A::is_logical == false);
  BOOST_CHECK(meta_B::is_logical == false);
  BOOST_CHECK(meta_C::is_logical == true);
}

BOOST_AUTO_TEST_CASE(intrusive_enum_traits_test)
{
  typedef detail::meta_intrusive_traits<A> int_A;
  typedef detail::meta_intrusive_traits<B> int_B;
  typedef detail::meta_intrusive_traits<C> int_C;
  
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
  
  BOOST_CHECK(int_A::has_is_logical == false);
  BOOST_CHECK(int_B::has_is_logical == true);
  BOOST_CHECK(int_C::has_is_logical == false);
  
  BOOST_CHECK(int_A::is_logical == false);
  BOOST_CHECK(int_B::is_logical == false);
  BOOST_CHECK(int_C::is_logical == false);
}

BOOST_AUTO_TEST_CASE(enum_traits_test)
{
  typedef enum_traits<A> traits_A;
  typedef enum_traits<B> traits_B;
  typedef enum_traits<C> traits_C;
  
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
  
  BOOST_CHECK(traits_A::has_is_logical == false);
  BOOST_CHECK(traits_B::has_is_logical == true);
  BOOST_CHECK(traits_C::has_is_logical == true);
}

BOOST_AUTO_TEST_CASE(test_has_range)
{
  BOOST_CHECK(has_range<A>::value == false);
  BOOST_CHECK(has_range<B>::value == true);
  BOOST_CHECK(has_range<C>::value == true);
  
  BOOST_CHECK(enum_traits<A>::has_constexpr_range == false);
  BOOST_CHECK(enum_traits<B>::has_constexpr_range == true);
  BOOST_CHECK(enum_traits<C>::has_constexpr_range == false);
}

BOOST_AUTO_TEST_CASE(test_value_functions)
{
  BOOST_CHECK(default_value<B>() == B::none);
  BOOST_CHECK(default_value<C>() == C::none);
  
  BOOST_CHECK(error_value<B>() == B::none);
  BOOST_CHECK(error_value<C>() == C::none);
  
  BOOST_CHECK(first_value<B>() == B::none);
  BOOST_CHECK(first_value<C>() == C::none);
  
  BOOST_CHECK(last_value<B>() == B::one);
  BOOST_CHECK(last_value<C>() == C::three);
  
  BOOST_CHECK(size<B>() == 2);
  BOOST_CHECK(size<C>() == 3);
  
  BOOST_CHECK(is_contigious<B>() == true);
  BOOST_CHECK(is_contigious<C>() == false);
}

BOOST_AUTO_TEST_CASE(test_in_range)
{
  BOOST_CHECK(in_range(B::none));
  BOOST_CHECK(in_range(B::one));
  
  BOOST_CHECK(in_range(static_cast<B>(-1)) == false);
  BOOST_CHECK(in_range(static_cast<B>(2)) == false);
  
  BOOST_CHECK(in_range(C::none));
  BOOST_CHECK(in_range(C::one));
  BOOST_CHECK(in_range(C::three));

  BOOST_CHECK(in_range(static_cast<C>(-1)) == false);
  BOOST_CHECK(in_range(static_cast<C>(4)) == false);
  BOOST_CHECK(in_range(static_cast<C>(2)) == false);
}

BOOST_AUTO_TEST_CASE(test_enum_cast)
{
  /* Enum -> Enum */
  B b;
  C c;
  
  b = B::none;
  c = C::none;
  BOOST_CHECK(enum_cast<B>(b) == b);
  BOOST_CHECK(enum_cast<C>(b) == c);
  BOOST_CHECK(enum_cast<C>(c) == c);
  BOOST_CHECK(enum_cast<B>(c) == b);
 
 
  b = B::one;
  c = C::one;
  BOOST_CHECK(enum_cast<B>(b) == b);
  BOOST_CHECK(enum_cast<C>(b) == c);
  BOOST_CHECK(enum_cast<C>(c) == c);
  BOOST_CHECK(enum_cast<B>(c) == b);
  
  c = C::three;
  BOOST_CHECK_THROW(enum_cast<B>(c), bad_enum_cast);
  BOOST_CHECK_THROW(enum_cast<B>(static_cast<B>(-1)),  bad_enum_cast);
  BOOST_CHECK_THROW(enum_cast<C>(static_cast<B>(100)), bad_enum_cast);
  
  /* Integral -> Enum */
  BOOST_CHECK(enum_cast<B>(0) == B::none);
  BOOST_CHECK(enum_cast<C>(0) == C::none);
  BOOST_CHECK(enum_cast<B>(1) == B::one);
  BOOST_CHECK(enum_cast<C>(3) == C::three);
  
  BOOST_CHECK_THROW(enum_cast<B>(-1), bad_enum_cast);
  BOOST_CHECK_THROW(enum_cast<B>(3), bad_enum_cast);
  BOOST_CHECK_THROW(enum_cast<C>(2), bad_enum_cast);
  
  /* Enum -> Integral : only check to force its instatiation */
  BOOST_CHECK(enum_cast<int>(A::none) == 0);
  BOOST_CHECK(enum_cast<long>(B::one) == 1);
  BOOST_CHECK(enum_cast<unsigned char>(C::three) == 3);
  
  /* String -> Enum : only C has a name map */
  std::string s = "none";
  const std::string const_s = "one";
  const char* cs1 = "three";
  BOOST_CHECK(enum_cast<C>("none") == C::none);
  BOOST_CHECK(enum_cast<C>(std::string{"none"}) == C::none);
  BOOST_CHECK(enum_cast<C>(s) == C::none);
  BOOST_CHECK(enum_cast<C>(const_s) == C::one);
  BOOST_CHECK(enum_cast<C>(cs1) == C::three);
  
  BOOST_CHECK_THROW(enum_cast<C>(""), bad_enum_cast);
  BOOST_CHECK_THROW(enum_cast<C>("hello"), bad_enum_cast);
  
  /* Enum -> String : only std::string is supported */
  BOOST_CHECK(enum_cast<std::string>(C::none) == "none");
  BOOST_CHECK(enum_cast<std::string>(C::one) == "one");
  BOOST_CHECK(enum_cast<std::string>(C::three) == "three");
  
  BOOST_CHECK_THROW(enum_cast<std::string>(static_cast<C>(-1)), bad_enum_cast);
  BOOST_CHECK_THROW(enum_cast<std::string>(static_cast<C>(2)), bad_enum_cast);
  BOOST_CHECK_THROW(enum_cast<std::string>(static_cast<C>(100)), bad_enum_cast);

}


BOOST_AUTO_TEST_SUITE_END()