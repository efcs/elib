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

enum class B {
  zero, 
  one, 
  two
};

enum class C {
  zero, 
  one, 
  two, 
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
      
      
  
    template <>
    struct basic_enum_traits<B> 
    {
      static const std::map<B, std::string> name_map;
    };
      
#define ENUM_ENTRY(e) {::B::e, "" #e} 

    const std::map<B, std::string> basic_enum_traits<B>::name_map = 
      {
        ENUM_ENTRY(zero), 
        ENUM_ENTRY(one), 
        ENUM_ENTRY(two)
      };
      
#undef ENUM_ENTRY
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

#define CHECK_FIELD(Enum, field, is_good, v)             \
  BOOST_CHECK(en::field<Enum>::good == is_good); \
  BOOST_CHECK(dc(en::field<Enum>::value) == v)

BOOST_AUTO_TEST_CASE(test_enum_can_cast)
{
  
  CHECK_FIELD(en::ef, first_field, true, 0);
  CHECK_FIELD(en::ef, last_field, true, 1);
  CHECK_FIELD(en::ef, default_field, true, 0);
  CHECK_FIELD(en::ef, npos_field,  true,  static_cast<int>(-1));
  CHECK_FIELD(en::ef, is_contiguous_field, true, 1);
  CHECK_FIELD(en::ef, allow_bitwise_operators_field, true, 0);
  CHECK_FIELD(en::ef, allow_mixed_bitwise_operators_field, true, 1);
  CHECK_FIELD(en::ef, allow_logical_operators_field, true, 0);
  CHECK_FIELD(en::ef, allow_mixed_logical_operators_field, true, 1);  
  CHECK_FIELD(en::ef, allow_arithmetic_operators_field, true, 0);
  CHECK_FIELD(en::ef, allow_mixed_arithmetic_operators_field, true, 1);  
  CHECK_FIELD(en::ef, allow_stream_extraction_operator_field, true, 1);
  CHECK_FIELD(en::ef, allow_stream_insertion_operator_field, true, 1);  
  
  
  CHECK_FIELD(A, first_field, true, 0);
  CHECK_FIELD(A, last_field, true, 2);
  CHECK_FIELD(A, default_field, false, 0);
  CHECK_FIELD(A, npos_field,  false, 0);
  CHECK_FIELD(A, is_contiguous_field, true, 1);
  CHECK_FIELD(A, allow_bitwise_operators_field, false, 0);
  CHECK_FIELD(A, allow_mixed_bitwise_operators_field, false, 0);
  CHECK_FIELD(A, allow_logical_operators_field, false, 0);
  CHECK_FIELD(A, allow_mixed_logical_operators_field, false, 0);  
  CHECK_FIELD(A, allow_arithmetic_operators_field, false, 0);
  CHECK_FIELD(A, allow_mixed_arithmetic_operators_field, false, 0);  
  CHECK_FIELD(A, allow_stream_extraction_operator_field, false, 0);
  CHECK_FIELD(A, allow_stream_insertion_operator_field, false, 0);
  
  CHECK_FIELD(B, first_field, false, 0);
  CHECK_FIELD(B, last_field, false, 0);
  CHECK_FIELD(B, default_field, false, 0);
  CHECK_FIELD(B, npos_field,  false,  0);
  CHECK_FIELD(B, is_contiguous_field, false, 0);
  CHECK_FIELD(B, allow_bitwise_operators_field, false, 0);
  CHECK_FIELD(B, allow_mixed_bitwise_operators_field, false, 0);
  CHECK_FIELD(B, allow_logical_operators_field, false, 0);
  CHECK_FIELD(B, allow_mixed_logical_operators_field, false, 0);  
  CHECK_FIELD(B, allow_arithmetic_operators_field, false, 0);
  CHECK_FIELD(B, allow_mixed_arithmetic_operators_field, false, 0);  
  CHECK_FIELD(B, allow_stream_extraction_operator_field, false, 0);
  CHECK_FIELD(B, allow_stream_insertion_operator_field, false, 0);
  
  CHECK_FIELD(C, first_field, false, 0);
  CHECK_FIELD(C, last_field, false, 0);
  CHECK_FIELD(C, default_field, false, 0);
  CHECK_FIELD(C, npos_field,  false,  0);
  CHECK_FIELD(C, is_contiguous_field, false, 0);
  CHECK_FIELD(C, allow_bitwise_operators_field, false, 0);
  CHECK_FIELD(C, allow_mixed_bitwise_operators_field, false, 0);
  CHECK_FIELD(C, allow_logical_operators_field, false, 0);
  CHECK_FIELD(C, allow_mixed_logical_operators_field, false, 0);  
  CHECK_FIELD(C, allow_arithmetic_operators_field, false, 0);
  CHECK_FIELD(C, allow_mixed_arithmetic_operators_field, false, 0);  
  CHECK_FIELD(C, allow_stream_extraction_operator_field, false, 0);
  CHECK_FIELD(C, allow_stream_insertion_operator_field, false, 0);
  
}

BOOST_AUTO_TEST_CASE(test_has_basic_enum_traits)
{
  BOOST_CHECK(en::has_basic_enum_traits<en::ef>::value == false);
  BOOST_CHECK(en::has_basic_enum_traits<A>::value == true);
  BOOST_CHECK(en::has_basic_enum_traits<B>::value == true);
  BOOST_CHECK(en::has_basic_enum_traits<C>::value == false);
}

BOOST_AUTO_TEST_CASE(test_has_constexpr_bounds)
{
  BOOST_CHECK(en::has_constexpr_bounds<en::ef>::value == true);
  BOOST_CHECK(en::has_constexpr_bounds<A>::value == true);
  BOOST_CHECK(en::has_constexpr_bounds<B>::value == false);
  BOOST_CHECK(en::has_constexpr_bounds<C>::value == false);
}

BOOST_AUTO_TEST_CASE(test_has_bounds)
{
  BOOST_CHECK(en::has_bounds<en::ef>::value == true);
  BOOST_CHECK(en::has_bounds<A>::value == true);
  BOOST_CHECK(en::has_bounds<B>::value == true);
  BOOST_CHECK(en::has_basic_enum_traits<B>::value == true);
  BOOST_CHECK(en::has_bounds<C>::value == false);
}

BOOST_AUTO_TEST_CASE(test_has_constexpr_range)
{
  BOOST_CHECK(en::has_constexpr_range<en::ef>::value == true);
  BOOST_CHECK(en::has_constexpr_range<A>::value == true);
  BOOST_CHECK(en::has_constexpr_range<B>::value == false);
  BOOST_CHECK(en::has_constexpr_range<C>::value == false);
}

BOOST_AUTO_TEST_CASE(test_has_range)
{
  BOOST_CHECK(en::has_range<en::ef>::value == true);
  BOOST_CHECK(en::has_range<A>::value == true);
  BOOST_CHECK(en::has_range<B>::value == true);
  BOOST_CHECK(en::has_range<C>::value == false);
}

BOOST_AUTO_TEST_CASE(test_bounds)
{
  BOOST_CHECK(en::enum_bounds<en::ef>::min == en::ef::ELIB_ENUM_FIRST_VALUE);
  BOOST_CHECK(en::enum_bounds<en::ef>::max == en::ef::ELIB_ENUM_LAST_VALUE);
  
  BOOST_CHECK(en::enum_bounds<A>::min == A::zero);
  BOOST_CHECK(en::enum_bounds<A>::max == A::two);
  
  BOOST_CHECK(en::enum_bounds<B>::min == B::zero);
  BOOST_CHECK(en::enum_bounds<B>::max == B::two);
  
  static_assert(en::enum_bounds<en::ef>::min == en::ef::ELIB_ENUM_FIRST_VALUE, "");
  static_assert(en::enum_bounds<en::ef>::max == en::ef::ELIB_ENUM_LAST_VALUE, "");

  static_assert(en::enum_bounds<A>::min == A::zero, "");
  static_assert(en::enum_bounds<A>::max == A::two, "");
}

BOOST_AUTO_TEST_CASE(test_range)
{
  BOOST_CHECK(en::enum_range<en::ef>::min == en::ef::ELIB_ENUM_FIRST_VALUE);
  BOOST_CHECK(en::enum_range<en::ef>::max == en::ef::ELIB_ENUM_LAST_VALUE);
  BOOST_CHECK(en::enum_range<en::ef>::size == 2);

  BOOST_CHECK(en::enum_range<A>::min == A::zero);
  BOOST_CHECK(en::enum_range<A>::max == A::two);
  BOOST_CHECK(en::enum_range<A>::size == 3);

  BOOST_CHECK(en::enum_range<B>::min == B::zero);
  BOOST_CHECK(en::enum_range<B>::max == B::two);
  BOOST_CHECK(en::enum_range<B>::size == 3);

  static_assert(en::enum_range<en::ef>::min == en::ef::ELIB_ENUM_FIRST_VALUE, "");
  static_assert(en::enum_range<en::ef>::max == en::ef::ELIB_ENUM_LAST_VALUE, "");
  static_assert(en::enum_range<en::ef>::size == 2, "");

  static_assert(en::enum_range<A>::min == A::zero, "");
  static_assert(en::enum_range<A>::max == A::two, "");
  static_assert(en::enum_range<A>::size == 3, "");
}

BOOST_AUTO_TEST_CASE(test_is_valid_enum)
{
  BOOST_CHECK(en::valid_enum(static_cast<A>(0)));
  BOOST_CHECK(en::valid_enum(static_cast<B>(1)));
  
  
  BOOST_CHECK(!en::valid_enum(static_cast<A>(-1)));
  BOOST_CHECK(!en::valid_enum(static_cast<A>(10)));
  BOOST_CHECK(!en::valid_enum(static_cast<B>(10)));
  
}


////////////////////////////////////////////////////////////////////////////////
//                          ENUM_ITERATOR                                                
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(test_enum_iterator)
{
  {
    auto it = en::enum_iterator<en::ef>{en::detail::iter_pos_e::begin};
    auto end_it = en::enum_iterator<en::ef>{en::detail::iter_pos_e::end};
    
    BOOST_CHECK(*it == en::ef::ELIB_ENUM_FIRST_VALUE);
    ++it;
    BOOST_CHECK(*it == en::ef::ELIB_ENUM_LAST_VALUE);
    ++it;
    BOOST_CHECK(it == end_it);
  }
  
  {
    auto it = en::enum_iterator<A>{en::detail::iter_pos_e::begin};
    auto end_it = en::enum_iterator<A>{en::detail::iter_pos_e::end};

    BOOST_CHECK(*it == A::zero);
    BOOST_CHECK(it != end_it);
    ++it;
    BOOST_CHECK(*it == A::one);
    BOOST_CHECK(it != end_it);
    ++it;
    BOOST_CHECK(*it == A::two);
    BOOST_CHECK(it != end_it);
    ++it;
    BOOST_CHECK(it == end_it);
  }
  
  {
    auto it = en::enum_iterator<B>{en::detail::iter_pos_e::begin};
    auto end_it = en::enum_iterator<B>{en::detail::iter_pos_e::end};

    BOOST_CHECK(*it == B::zero);
    BOOST_CHECK(it != end_it);
    ++it;
    BOOST_CHECK(*it == B::one);
    BOOST_CHECK(it != end_it);
    ++it;
    BOOST_CHECK(*it == B::two);
    BOOST_CHECK(it != end_it);
    ++it;
    BOOST_CHECK(it == end_it);  
  }
}


////////////////////////////////////////////////////////////////////////////////
//                           ENUM CAST                                             
////////////////////////////////////////////////////////////////////////////////



BOOST_AUTO_TEST_CASE(test_enum_cast)
{
  BOOST_CHECK(en::underlying_cast(C::zero) == 0);
  BOOST_CHECK(en::underlying_cast(C::one) == 1);
  BOOST_CHECK(en::underlying_cast(C::two) == 2);
  
  // check constexpr-ness of underlying_enum_cast
  static_assert(en::underlying_cast(C::zero) == 0, "");
  static_assert(en::underlying_cast(C::one) == 1, "");
  static_assert(en::underlying_cast(C::two) == 2, "");
  
  // check unchecked_cast
  BOOST_CHECK(en::unchecked_enum_cast<int>(A::zero) == 0);
  BOOST_CHECK(en::unchecked_enum_cast<int>(A::one) == 1);
  BOOST_CHECK(en::unchecked_enum_cast<int>(A::two) == 2);
  
  BOOST_CHECK(en::unchecked_enum_cast<A>(0) == A::zero);
  BOOST_CHECK(en::unchecked_enum_cast<A>(1) == A::one);
  BOOST_CHECK(en::unchecked_enum_cast<A>(2) == A::two);
  
  static_assert(en::unchecked_enum_cast<int>(A::zero) == 0, "");
  static_assert(en::unchecked_enum_cast<int>(A::one) == 1, "");
  static_assert(en::unchecked_enum_cast<int>(A::two) == 2, "");

  static_assert(en::unchecked_enum_cast<A>(0) == A::zero, "");
  static_assert(en::unchecked_enum_cast<A>(1) == A::one, "");
  static_assert(en::unchecked_enum_cast<A>(2) == A::two, "");
  
  //check Integral enum_cast(Enum)
  BOOST_CHECK(en::enum_cast<int>(B::zero) == 0);
  BOOST_CHECK(en::enum_cast<int>(B::one) == 1);
  BOOST_CHECK(en::enum_cast<int>(B::two) == 2);
  
  static_assert(en::enum_cast<int>(B::zero) == 0, "");
  static_assert(en::enum_cast<int>(B::one) == 1, "");
  static_assert(en::enum_cast<int>(B::two) == 2, "");
  
  // check Enum enum_cast(Integral) 
  BOOST_CHECK(en::enum_cast<A>(0) == A::zero);
  BOOST_CHECK(en::enum_cast<B>(1) == B::one);
  
  BOOST_CHECK_THROW(en::enum_cast<A>(10), en::bad_enum_cast);
  BOOST_CHECK_THROW(en::enum_cast<B>(-1), en::bad_enum_cast);

}



BOOST_AUTO_TEST_SUITE_END()