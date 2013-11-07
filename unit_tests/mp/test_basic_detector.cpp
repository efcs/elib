#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/basic_detector.hpp>

using namespace elib;

enum class mem_enum
{
  test = 0
};

class mem_type
{
public:
  typedef void test;
};


class mem_data
{
public:
  int test = 0;
};

class mem_fn
{
public:
  void test();
};

template <class T>
using enum_dt = decltype(T::test);

template <class T>
using dne_enum_dt = decltype(T::dne);


template <class T>
using type_dt = typename T::test;

template <class T>
using dne_type_dt = typename T::dne;


template <class T>
using data_dt = decltype(&T::test);

template <class T>
using dne_data_dt = decltype(&T::dne);


template <class T>
using fn_dt = decltype(&T::test);

template <class T>
using dne_fn_dt = decltype(&T::dne);



BOOST_AUTO_TEST_SUITE(mp_detector_test_suite)

BOOST_AUTO_TEST_CASE(mp_detector_fail)
{
  BOOST_CHECK((mp::basic_detector<mem_enum, dne_enum_dt>::value) == false);
  BOOST_CHECK((mp::basic_detector<mem_type, dne_type_dt>::value) == false);
  BOOST_CHECK((mp::basic_detector<mem_data, dne_data_dt>::value) == false);
  BOOST_CHECK((mp::basic_detector<mem_fn, dne_fn_dt>::value) == false);
}

BOOST_AUTO_TEST_CASE(mp_detector_pass)
{
  BOOST_CHECK((mp::basic_detector<mem_enum, enum_dt>::value));
  BOOST_CHECK((mp::basic_detector<mem_type, type_dt>::value));
  BOOST_CHECK((mp::basic_detector<mem_data, data_dt>::value));
  BOOST_CHECK((mp::basic_detector<mem_fn, fn_dt>::value));
}

BOOST_AUTO_TEST_CASE(mp_detector_test_type)
{
  // for enum
  BOOST_CHECK(std::is_enum<enum_dt<mem_enum>>::value);
  BOOST_CHECK(std::is_member_pointer< enum_dt<mem_enum> >::value == false);
  
  // for type
  BOOST_CHECK(std::is_enum<type_dt<mem_type>>::value == false);
  BOOST_CHECK(std::is_member_pointer<type_dt<mem_type>>::value == false);
  
  // for member data
  BOOST_CHECK(std::is_member_pointer<data_dt<mem_data>>::value);
  BOOST_CHECK(std::is_member_object_pointer<data_dt<mem_data>>::value);
  BOOST_CHECK(std::is_member_function_pointer<data_dt<mem_data>>::value == false);
  BOOST_CHECK(std::is_enum<data_dt<mem_data>>::value == false);
  
  // for member function
  BOOST_CHECK(std::is_member_pointer<fn_dt<mem_fn>>::value);
  BOOST_CHECK(std::is_member_function_pointer<fn_dt<mem_fn>>::value);
  BOOST_CHECK(std::is_member_object_pointer<fn_dt<mem_fn>>::value == false);
  BOOST_CHECK(std::is_enum<fn_dt<mem_fn>>::value == false);
}


BOOST_AUTO_TEST_SUITE_END()
