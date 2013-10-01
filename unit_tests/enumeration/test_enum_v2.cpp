#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/enumeration/v2/basic_enum_traits.hpp>
#include <elib/enumeration/v2/enum_fields.hpp>
#include <elib/enumeration/v2/enum_traits.hpp>
#include <elib/enumeration/v2/enum_cast.hpp>
#include <elib/enumeration/v2/enum_iterator.hpp>

#include <type_traits>



enum class A {
  zero = 0, 
  one, 
  two, 
  
  ELIB_ENUM_FIRST_VALUE = zero, 
  ELIB_ENUM_LAST_VALUE = two, 
  ELIB_ENUM_IS_CONTIGUOUS = true, 
};

namespace elib { namespace enumeration {
  
    template <>
    struct basic_enum_traits<A> {
      static const std::map<A, std::string> name_map;
    };
    
    
    const std::map<A, std::string> basic_enum_traits<A>::name_map =
      {
        {::A::zero, "zero"},
        {::A::one, "one"}, 
        {::A::two, "two"}
      };
      
      
    using ef = enumeration_fields;
}}


namespace en = elib::enumeration;

template <typename T>
constexpr typename std::underlying_type<T>::type
dc(T v) noexcept
{
  return static_cast<typename std::underlying_type<T>::type>(v);
}

BOOST_AUTO_TEST_SUITE(enumeration_v2_test_suite)

BOOST_AUTO_TEST_CASE(test_enum_can_cast)
{
  
  BOOST_CHECK(en::first_field_value<en::ef>::good == true);
  BOOST_CHECK(dc(en::first_field_value<en::ef>::value) == 0);
  
  BOOST_CHECK(en::last_field_value<en::ef>::good);
  BOOST_CHECK(dc(en::last_field_value<en::ef>::value) == 1);
  
  BOOST_CHECK(en::default_field_value<en::ef>::good);
  BOOST_CHECK(dc(en::default_field_value<en::ef>::value) == 0);
  
  BOOST_CHECK(en::npos_field_value<en::ef>::good);
  BOOST_CHECK(dc(en::npos_field_value<en::ef>::value) 
      == static_cast<typename std::underlying_type<en::ef>::type>(-1));
      
  
  BOOST_CHECK(en::first_field_value<A>::good);
}

BOOST_AUTO_TEST_SUITE_END()