#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/enumeration/v2/basic_enum_traits.hpp>
#include <elib/enumeration/v2/enum_fields.hpp>
#include <elib/enumeration/v2/enum_traits.hpp>
#include <elib/enumeration/v2/enum_cast.hpp>
#include <elib/enumeration/v2/enum_iterator.hpp>
#include <elib/enumeration/v2/operators.hpp>
#include <elib/enumeration/v2/enum_adapter.hpp>

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
  
  ELIB_ENUM_ALLOW_LOGICAL_OPERATORS = true
};

enum class D {
  none,
  one = 1, 
  two = 2, 
  three = 3, 
  four = 4, 
  five = 5, 
  six = 6, 
  seven = 7, 
  eight = 8, 
  nine = 9, 
  ten = 10, 
  
  // gives constexpr_range
  ELIB_ENUM_FIRST_VALUE = none, 
  ELIB_ENUM_LAST_VALUE = ten, 
  ELIB_ENUM_IS_CONTIGUOUS = true, 
  
  // gives operators
  ELIB_ENUM_ALLOW_MIXED_BITWISE_OPERATORS = true, 
  ELIB_ENUM_ALLOW_MIXED_LOGICAL_OPERATORS = true, 
  ELIB_ENUM_ALLOW_MIXED_ARITHMETIC_OPERATORS = true, 
  ELIB_ENUM_ALLOW_BOOL_INDIRECTION_OPERATOR = true,
  ELIB_ENUM_ALLOW_UNDERLYING_DEREFERENCE_OPERATOR = true
  
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

#define CHECK_FIELD(Enum, field, is_good, v)     \
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
  CHECK_FIELD(en::ef, allow_bool_indirection_operator_field, true, 1);
  CHECK_FIELD(en::ef, allow_underlying_dereference_operator_field, true, 1);
  
  
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
  CHECK_FIELD(A, allow_bool_indirection_operator_field, false, 0);
  CHECK_FIELD(A, allow_underlying_dereference_operator_field, false, 0);
  
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
  CHECK_FIELD(B, allow_bool_indirection_operator_field, false, 0);
  CHECK_FIELD(B, allow_underlying_dereference_operator_field, false, 0);
  
  
  CHECK_FIELD(C, first_field, false, 0);
  CHECK_FIELD(C, last_field, false, 0);
  CHECK_FIELD(C, default_field, false, 0);
  CHECK_FIELD(C, npos_field,  false,  0);
  CHECK_FIELD(C, is_contiguous_field, false, 0);
  CHECK_FIELD(C, allow_bitwise_operators_field, false, 0);
  CHECK_FIELD(C, allow_mixed_bitwise_operators_field, false, 0);
  CHECK_FIELD(C, allow_logical_operators_field, true, 1);
  CHECK_FIELD(C, allow_mixed_logical_operators_field, false, 0);  
  CHECK_FIELD(C, allow_arithmetic_operators_field, false, 0);
  CHECK_FIELD(C, allow_mixed_arithmetic_operators_field, false, 0);  
  CHECK_FIELD(C, allow_stream_extraction_operator_field, false, 0);
  CHECK_FIELD(C, allow_stream_insertion_operator_field, false, 0);
  
  
  
  CHECK_FIELD(D, first_field, true, 0);
  CHECK_FIELD(D, last_field, true, 10);
  
  CHECK_FIELD(D, default_field, false,  0);
  CHECK_FIELD(D, npos_field,  false,  0);
  CHECK_FIELD(D, is_contiguous_field, true, 1);
  
  CHECK_FIELD(D, allow_bitwise_operators_field, false, 0);
  CHECK_FIELD(D, allow_mixed_bitwise_operators_field, true, 1);
  CHECK_FIELD(D, allow_logical_operators_field, false, 0);
  CHECK_FIELD(D, allow_mixed_logical_operators_field, true, 1);  
  CHECK_FIELD(D, allow_arithmetic_operators_field, false, 0);
  CHECK_FIELD(D, allow_mixed_arithmetic_operators_field, true, 1);  
  
  CHECK_FIELD(D, allow_stream_extraction_operator_field, false, 0);
  CHECK_FIELD(D, allow_stream_insertion_operator_field, false,  0);
  
  CHECK_FIELD(D, allow_bool_indirection_operator_field, true, 1);
  CHECK_FIELD(D, allow_underlying_dereference_operator_field, true, 1);
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
    
    BOOST_CHECK((*it) == en::ef::ELIB_ENUM_FIRST_VALUE);
    ++it;
    BOOST_CHECK((*it) == en::ef::ELIB_ENUM_LAST_VALUE);
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
    auto bit = en::begin(en::enum_range<B>{});
    BOOST_CHECK(it == bit);
    auto end_it = en::enum_iterator<B>{en::detail::iter_pos_e::end};
    auto eit = en::end(en::enum_range<B>{});
    BOOST_CHECK(end_it == eit);

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
    
    it = en::enum_iterator<B>{en::detail::iter_pos_e::begin};
    for (auto& e : en::enum_range<B>{})
    {
      BOOST_REQUIRE(it != end_it);
      BOOST_CHECK(*it == e);
      ++it;
    }
    BOOST_CHECK(it == end_it);
  }
}


////////////////////////////////////////////////////////////////////////////////
//                           ENUM CAST                                             
////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_CASE(test_enum_cast)
{
  
  A a;
  B b;
  
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
  int x;
  BOOST_CHECK(en::enum_cast<int>(B::zero) == 0);
  BOOST_CHECK(en::enum_cast<int>(B::one) == 1);
  BOOST_CHECK(en::enum_cast<int>(B::two) == 2);
  BOOST_CHECK(en::safe_enum_cast<int>(B::zero, x));
  BOOST_CHECK(x == 0);
  BOOST_CHECK(en::safe_enum_cast<int>(B::one, x));
  BOOST_CHECK(x == 1);
  BOOST_CHECK(en::safe_enum_cast<int>(B::two, x));
  BOOST_CHECK(x == 2);
  
  static_assert(en::enum_cast<int>(B::zero) == 0, "");
  static_assert(en::enum_cast<int>(B::one) == 1, "");
  static_assert(en::enum_cast<int>(B::two) == 2, "");
  
  ////////////////////////////////////////////////////////////////////////////////
  //                       Integral -> Enum                                              
  ////////////////////////////////////////////////////////////////////////////////
  
  BOOST_CHECK(en::enum_cast<A>(0) == A::zero);
  BOOST_CHECK(en::enum_cast<B>(1) == B::one);
  BOOST_CHECK(en::enum_cast<A>(2) == A::two);
  BOOST_CHECK(en::safe_enum_cast<A>(0, a));
  BOOST_CHECK(a == A::zero);
  BOOST_CHECK(en::safe_enum_cast<B>(1, b));
  BOOST_CHECK(b == B::one);
  BOOST_CHECK(en::safe_enum_cast<A>(2, a));
  BOOST_CHECK(a == A::two);
  
  BOOST_CHECK_THROW(en::enum_cast<A>(10), en::bad_enum_cast);
  BOOST_CHECK_THROW(en::enum_cast<B>(-1), en::bad_enum_cast);
  BOOST_CHECK(en::safe_enum_cast<A>(1000, a) == false);
  BOOST_CHECK(en::safe_enum_cast<B>(3, b) == false);
  
  ////////////////////////////////////////////////////////////////////////////////
  //                          Enum -> Str                                                
  ////////////////////////////////////////////////////////////////////////////////
  
  BOOST_CHECK(en::enum_cast<std::string>(A::zero) == "zero");
  BOOST_CHECK(en::enum_cast<std::string>(B::one) == "one");
  BOOST_CHECK(en::enum_cast<std::string>(A::two) == "two");
  
  BOOST_CHECK_THROW(en::enum_cast<std::string>(static_cast<A>(-1)), en::bad_enum_cast);
  BOOST_CHECK_THROW(en::enum_cast<std::string>(static_cast<A>(10)), en::bad_enum_cast);
  BOOST_CHECK_THROW(en::enum_cast<std::string>(static_cast<B>(3)), en::bad_enum_cast);
  BOOST_CHECK_THROW(en::enum_cast<std::string>(static_cast<B>(100000)), en::bad_enum_cast);
  
  ////////////////////////////////////////////////////////////////////////////////
  //                          String -> Enum                                               
  ////////////////////////////////////////////////////////////////////////////////
  
  BOOST_CHECK(en::enum_cast<A>("zero") == A::zero);
  BOOST_CHECK(en::enum_cast<A>("one") == A::one);
  BOOST_CHECK(en::enum_cast<B>("two") == B::two);
  
  BOOST_CHECK(en::safe_enum_cast<A>("zero", a));
  BOOST_CHECK(a == A::zero);
  BOOST_CHECK(en::safe_enum_cast<A>("one", a));
  BOOST_CHECK(a == A::one);
  BOOST_CHECK(en::safe_enum_cast<B>("two", b));
  BOOST_CHECK(b == B::two);
  
  BOOST_CHECK_THROW(en::enum_cast<A>("foo"), en::bad_enum_cast);
  BOOST_CHECK_THROW(en::enum_cast<A>(""), en::bad_enum_cast);
  BOOST_CHECK_THROW(en::enum_cast<A>("A"), en::bad_enum_cast);
  BOOST_CHECK_THROW(en::enum_cast<B>("Zero"), en::bad_enum_cast);
  BOOST_CHECK_THROW(en::enum_cast<A>("One"), en::bad_enum_cast);
  
  BOOST_CHECK(en::safe_enum_cast<A>("foo", a) == false);
  BOOST_CHECK(en::safe_enum_cast<A>("", a) == false);
  BOOST_CHECK(en::safe_enum_cast<A>("A", a) == false);
  BOOST_CHECK(en::safe_enum_cast<B>("Zero", b) == false);
  BOOST_CHECK(en::safe_enum_cast<A>("One", a) == false);
  
}


////////////////////////////////////////////////////////////////////////////////
//                            ENUM OPERATORS                                              
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(test_has_operators)
{
  BOOST_CHECK(en::has_bitwise_operators<A>::value == false);
  BOOST_CHECK(en::has_mixed_bitwise_operators<A>::value == false);
  BOOST_CHECK(en::has_logical_operators<A>::value == false);
  BOOST_CHECK(en::has_mixed_logical_operators<A>::value == false);
  BOOST_CHECK(en::has_arithmetic_operators<A>::value == false);
  BOOST_CHECK(en::has_mixed_arithmetic_operators<A>::value == false);
  BOOST_CHECK(en::has_stream_insertion_operator<A>::value == false);
  BOOST_CHECK(en::has_stream_extraction_operator<A>::value == false);
  
  BOOST_CHECK(en::has_bitwise_operators<C>::value == false);
  BOOST_CHECK(en::has_mixed_bitwise_operators<C>::value == false);
  BOOST_CHECK(en::has_logical_operators<C>::value == true);
  BOOST_CHECK(en::has_mixed_logical_operators<C>::value == false);
  BOOST_CHECK(en::has_arithmetic_operators<C>::value == false);
  BOOST_CHECK(en::has_mixed_arithmetic_operators<C>::value == false);
  BOOST_CHECK(en::has_stream_insertion_operator<C>::value == false);
  BOOST_CHECK(en::has_stream_extraction_operator<C>::value == false);
  
  BOOST_CHECK(en::has_bitwise_operators<D>::value == true);
  BOOST_CHECK(en::has_mixed_bitwise_operators<D>::value == true);
  BOOST_CHECK(en::has_logical_operators<D>::value == true);
  BOOST_CHECK(en::has_mixed_logical_operators<D>::value == true);
  BOOST_CHECK(en::has_arithmetic_operators<D>::value == true);
  BOOST_CHECK(en::has_mixed_arithmetic_operators<D>::value == true);
  BOOST_CHECK(en::has_stream_insertion_operator<D>::value == false);
  BOOST_CHECK(en::has_stream_extraction_operator<D>::value == false);
}


template <typename T, typename U>
bool check_result(T ret1, U ret2)
{
  return (static_cast<U>(ret1) == ret2);
}

template <typename T, typename U, typename V>
bool check_result(T ret1, U ret2, V ret3)
{
  return ((static_cast<U>(ret1) == ret2) && (static_cast<V>(ret2) == ret3));
}


BOOST_AUTO_TEST_CASE(test_operators)
{
  
  auto test_bitwise = [](int lhs, int rhs)
  {
    D e_lhs = static_cast<D>(lhs);
    D e_rhs = static_cast<D>(rhs);
    D e_ret;
    
    int ret;
    
    // Unary negate
    D e_old = e_lhs;
    int old = lhs;
    BOOST_CHECK(~e_lhs == static_cast<D>(~lhs));
    BOOST_CHECK(e_lhs == e_old && lhs == old);
    e_old = e_rhs;
    old = rhs;
    BOOST_CHECK(~e_rhs == static_cast<D>(~rhs));
    BOOST_CHECK(e_rhs == e_old && rhs == old);
    
    // Binary Pure
    e_ret = e_lhs;
    BOOST_CHECK(check_result(e_lhs & e_rhs, lhs & rhs, e_ret &= e_rhs));
    e_ret = e_lhs;
    BOOST_CHECK(check_result(e_lhs | e_rhs, lhs | rhs, e_ret |= e_rhs));
    e_ret = e_lhs;
    BOOST_CHECK(check_result(e_lhs ^ e_rhs, lhs ^ rhs, e_ret ^= e_rhs));
    e_ret = e_lhs;
    BOOST_CHECK(check_result(e_lhs << e_rhs, lhs << rhs, e_ret <<= e_rhs));
    e_ret = e_lhs;
    BOOST_CHECK(check_result(e_lhs >> e_rhs, lhs >> rhs, e_ret >>= e_rhs));
    e_ret = e_lhs;
    
    
    // LHS = Enum && RHS = Integral
    BOOST_CHECK(check_result(e_lhs & rhs, lhs & rhs, e_ret &= rhs));
    e_ret = e_lhs;
    BOOST_CHECK(check_result(e_lhs | rhs, lhs | rhs, e_ret |= rhs));
    e_ret = e_lhs;
    BOOST_CHECK(check_result(e_lhs ^ rhs, lhs ^ rhs, e_ret ^= rhs));
    e_ret = e_lhs;
    BOOST_CHECK(check_result(e_lhs << rhs, lhs << rhs, e_ret <<= rhs));
    e_ret = e_lhs;
    BOOST_CHECK(check_result(e_lhs >> rhs, lhs >> rhs, e_ret >>= rhs));
    e_ret = e_lhs;
    
    
    // LHS = Integral && RHS = Enum
    // return type is Integral
    ret = lhs;
    BOOST_CHECK(check_result(lhs & e_rhs, lhs & rhs, ret &= e_rhs));
    ret = lhs;
    BOOST_CHECK(check_result(lhs | e_rhs, lhs | rhs, ret |= e_rhs));
    ret = lhs;
    BOOST_CHECK(check_result(lhs ^ e_rhs, lhs ^ rhs, ret ^= e_rhs));
    ret = lhs;
    BOOST_CHECK(check_result(lhs << e_rhs, lhs << rhs, ret <<= e_rhs));
    ret = lhs;
    BOOST_CHECK(check_result(lhs >> e_rhs, lhs >> rhs, ret >>= e_rhs));
    ret = lhs;
  };
  
  auto test_logical =
    [](int lhs, int rhs)
    {
      D e_lhs, e_rhs, e_ret;
      int ret;
      
      e_lhs = static_cast<D>(lhs);
      e_rhs = static_cast<D>(rhs);
      
      // Unary operators
      e_ret = e_lhs;
      ret = lhs;
      BOOST_CHECK(check_result(!e_ret, !ret));
      // check original values are unmodified
      BOOST_CHECK(e_ret == e_lhs && ret == lhs);
      e_ret = e_rhs;
      ret = rhs;
      BOOST_CHECK(check_result(!e_ret, !ret));
      BOOST_CHECK(e_ret == e_rhs && ret == rhs);
      
      // Pure Binary
      BOOST_CHECK(check_result(e_lhs && e_rhs, lhs && rhs));
      BOOST_CHECK(check_result(e_lhs || e_rhs, lhs || rhs));
      
      // LHS = Enum && RHS = Integral
      BOOST_CHECK(check_result(e_lhs && rhs, lhs && rhs));
      BOOST_CHECK(check_result(e_lhs || rhs, lhs || rhs));
      
      // LHS = Integral && RHS = Enum
      BOOST_CHECK(check_result(lhs && e_rhs, lhs && rhs));
      BOOST_CHECK(check_result(lhs || e_rhs, lhs || rhs));
    };
  
  auto test_arithmetic = 
    [](int lhs, int rhs)
    {
      D e_lhs, e_rhs, e_ret;
      int ret;
      
      e_lhs = static_cast<D>(lhs);
      e_rhs = static_cast<D>(rhs);
      
      // Unary + and -
      BOOST_CHECK(check_result(+ e_lhs, + lhs));
      BOOST_CHECK(check_result(+ e_rhs, + rhs));
      BOOST_CHECK(check_result(- e_lhs, - lhs));
      BOOST_CHECK(check_result(- e_rhs, - rhs));
      
      // Increment & decrement
      e_ret = e_lhs;
      ret = lhs;
      BOOST_CHECK(check_result(++e_ret, ++ret));
      e_ret = e_lhs;
      ret = lhs;
      BOOST_CHECK(check_result(e_ret++, ret++));
      e_ret = e_lhs;
      ret = lhs;
      BOOST_CHECK(check_result(--e_ret, --ret));
      e_ret = e_lhs;
      ret = lhs;
      BOOST_CHECK(check_result(e_ret--, ret--));

      // Pure Binary
      e_ret = e_lhs;
      BOOST_CHECK(check_result(e_lhs + e_rhs, lhs + rhs, e_ret += e_rhs));
      e_ret = e_lhs;
      BOOST_CHECK(check_result(e_lhs - e_rhs, lhs - rhs, e_ret -= e_rhs));
      e_ret = e_lhs;
      BOOST_CHECK(check_result(e_lhs * e_rhs, lhs * rhs, e_ret *= e_rhs));
      
      if (rhs != 0)
      {
        e_ret = e_lhs;
        BOOST_CHECK(check_result(e_lhs / e_rhs, lhs / rhs, e_ret /= e_rhs));
        e_ret = e_lhs;
        BOOST_CHECK(check_result(e_lhs % e_rhs, lhs % rhs, e_ret %= e_rhs));
      }
      
      
      // MIXED ARITHMETIC
      // LHS = Enum && RHS = Integral
      e_ret = e_lhs;
      BOOST_CHECK(check_result(e_lhs + rhs, lhs + rhs, e_ret += rhs));
      e_ret = e_lhs;
      BOOST_CHECK(check_result(e_lhs - rhs, lhs - rhs, e_ret -= rhs));
      e_ret = e_lhs;
      BOOST_CHECK(check_result(e_lhs * rhs, lhs * rhs, e_ret *= rhs));

      if (rhs != 0)
      {
        e_ret = e_lhs;
        BOOST_CHECK(check_result(e_lhs / rhs, lhs / rhs, e_ret /= rhs));
        e_ret = e_lhs;
        BOOST_CHECK(check_result(e_lhs % rhs, lhs % rhs, e_ret %= rhs));
      }
      
      // LHS = Integral && RHS = Enum
      ret = lhs;
      BOOST_CHECK(check_result(lhs + e_rhs, lhs + rhs, ret += e_rhs));
      ret = lhs;
      BOOST_CHECK(check_result(lhs - e_rhs, lhs - rhs, ret -= e_rhs));
      ret = lhs;
      BOOST_CHECK(check_result(lhs * e_rhs, lhs * rhs, ret *= e_rhs));

      if (rhs != 0)
      {
        ret = lhs;
        BOOST_CHECK(check_result(lhs / e_rhs, lhs / rhs, ret /= e_rhs));
        ret = lhs;
        BOOST_CHECK(check_result(lhs % e_rhs, lhs % rhs, ret %= e_rhs));
      }
      
    };
    
    auto test_bool_and_under_ops =
      [](int i)
      {
        D e = static_cast<D>(i);
        BOOST_CHECK(static_cast<bool>(i) == *e);
        BOOST_CHECK((en::underlying_cast(e) == &e) && (&e == i)); 
      };
  
  for (int i=-10; i <= 10; ++i)
  {
    test_bool_and_under_ops(i);
    for (int j=-10; j <= 10; ++j)
    {
      test_bitwise(i, j);
      test_logical(i, j);
      test_arithmetic(i, j);
    }
  }
    
}                                                        // case test_operators



////////////////////////////////////////////////////////////////////////////////
//                         BASIC_ENUM_ADAPTER                                              
////////////////////////////////////////////////////////////////////////////////



BOOST_AUTO_TEST_SUITE_END()