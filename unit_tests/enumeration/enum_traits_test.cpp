#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/enumeration/enum.hpp"
#include "elib/enumeration/enum_traits.hpp"



namespace elib {
    
enum class test_e {
    none = -10,
    one = 1,
    two = 2,
    // non-contiguous section 
    five = 5,
    npos = 6
};

constexpr unsigned test_size = 5;
constexpr test_e test_last_value = test_e::npos;
    
template <>
struct basic_enum_traits<test_e> {
    static constexpr test_e default_value = test_e::none;
    static constexpr test_e first_value = test_e::none;
    static constexpr test_e last_value = test_last_value;
      
    typedef const std::map<test_e, std::string> map_type;
    static map_type name_map;
};


basic_enum_traits<test_e>::map_type
basic_enum_traits<test_e>::name_map =
    { {test_e::none, "none"},
      {test_e::one, "one"},
      {test_e::two, "two"},
      {test_e::five, "five"},
      {test_e::npos, "npos"}
    };
    
    
} /* namespace elib */


using namespace elib;
using namespace elib::enumeration;


static_assert(has_enum_traits<std::string>::value == false, "");
static_assert(has_enum_traits<test_e>::value, "");

/* all test cases use these typedefs */
typedef basic_enum_traits<test_e> basic_traits;
typedef enum_traits<test_e> traits;
typedef typename enum_traits<test_e>::iterator iterator;
typedef typename enum_traits<test_e>::const_iterator const_iterator;
typedef typename traits::underlying_type utype;

/* these are test cases, but they are static because they
 * test a constexpr function */
static_assert(base_enum_cast(test_e::one) == 1, "");
static_assert(base_enum_cast(test_e::five) == 5, "");
static_assert(base_enum_cast(static_cast<test_e>(-100)) == -100, "");


BOOST_AUTO_TEST_SUITE(base_enum_test_suite)


BOOST_AUTO_TEST_CASE(test_basic_enum_traits)
{
    BOOST_CHECK(basic_traits::default_value == test_e::none);
    BOOST_CHECK(basic_traits::first_value == test_e::none);
    BOOST_CHECK(basic_traits::last_value == test_last_value);
    
    BOOST_CHECK(basic_traits::name_map.size() == test_size);
}

BOOST_AUTO_TEST_CASE(test_enum_traits)
{
    BOOST_CHECK(basic_traits::name_map.size() == traits::size());
    BOOST_CHECK(basic_traits::default_value == traits::default_value);
    BOOST_CHECK(basic_traits::first_value == traits::first_value);
    BOOST_CHECK(basic_traits::last_value == traits::last_value);
}


BOOST_AUTO_TEST_CASE(test_lexical_enum_cast)
{    
    auto test_fn = 
        [&](test_e e, const std::string & s)
        {
            std::string ret_s = lexical_enum_cast<std::string>(e);
            BOOST_CHECK(ret_s == s);
            
            auto val = static_cast<utype>(e);
            auto ret_val = lexical_enum_cast<utype>(e);
            BOOST_CHECK(ret_val == val);
            return;
        };
    
    test_fn(test_e::none, "none");
    test_fn(test_e::five, "five");
    test_fn(test_e::npos, "npos");
}

BOOST_AUTO_TEST_CASE(test_enum_cast)
{    
    auto test_fn = 
        [&](test_e e, const std::string & s, utype val)
        {
            test_e ret_e;
            ret_e = enum_cast<test_e>(s);
            BOOST_CHECK(ret_e == e);
            
            ret_e = enum_cast<test_e>(val);
            BOOST_CHECK(ret_e == e);
            return;
        };
    
    test_fn(test_e::none, "none", -10);
    test_fn(test_e::one, "one", 1);
    test_fn(test_e::five, "five", 5);
    
    auto test_bad_fn =
        [&](const std::string & s, utype val)
        {
            try {
                auto e = enum_cast<test_e>(s);
                ELIB_UNUSED(e);
                BOOST_CHECK(false);
            } catch (bad_enum_cast & ex) {
                BOOST_CHECK(true);
            }
            
            try {
                auto e = enum_cast<test_e>(val);
                ELIB_UNUSED(e);
                BOOST_CHECK(false);
            } catch (bad_enum_cast & ex) {
                BOOST_CHECK(true);
            }
        };
        
    test_bad_fn("dne", -100);
    test_bad_fn("aoeuaoeu", 100);
}


BOOST_AUTO_TEST_CASE(test_enum_cast2)
{
    std::string str_val;
    utype val;
    test_e other_e;
    for (auto & e : traits()) {
        str_val = lexical_enum_cast<std::string>(e);
        val = lexical_enum_cast<utype>(e);
        
        other_e = enum_cast<test_e>(val);
        BOOST_CHECK(other_e == e);
        
        other_e = enum_cast<test_e>(str_val);
        BOOST_CHECK(other_e == e);
    }
    
    str_val = "three";
    val = 3;
    
    try {
        other_e = enum_cast<test_e>(val);
        BOOST_CHECK(false);
    } catch (bad_enum_cast &ex) {
        BOOST_CHECK(true);
    }
    
    try {
        other_e = enum_cast<test_e>(str_val);
        BOOST_CHECK(false);
    } catch (bad_enum_cast &ex) {
        BOOST_CHECK(true);
    }
    
}


BOOST_AUTO_TEST_CASE(test_safe_enum_cast)
{
    std::string str_val;
    utype val;
    test_e dest;
    
    for (auto e : traits()) {
        str_val = lexical_enum_cast<std::string>(e);
        val = lexical_enum_cast<utype>(e);
        dest = npos_enum<test_e>();
        
        BOOST_CHECK(enum_cast(val, dest));
        BOOST_CHECK(dest == e);
        
        BOOST_CHECK(enum_cast(str_val, dest));
        BOOST_CHECK(dest == e);
    }
    
    str_val = "three";
    val = 3;
    
    dest = test_e::none;
    BOOST_CHECK(enum_cast(val, dest) == false);
    BOOST_CHECK(dest == npos_enum<test_e>());
    
    dest = test_e::none;
    BOOST_CHECK(enum_cast(str_val, dest) == false);
    BOOST_CHECK(dest == npos_enum<test_e>());
}




BOOST_AUTO_TEST_CASE(test_enum_iter)
{
    test_e last = test_e::none;
    unsigned count = 0;
    
    auto b = traits::sbegin();
    auto e = traits::send();
    
    for (auto it=b; it != e; ++it) {
        test_e curr = *it;
        BOOST_CHECK(traits::name_map.count(curr) == 1);
        BOOST_CHECK((count == 0 && curr == last) ||
                    (count > 0 && curr > last));
        last = curr;
        ++count;
    }
    
    BOOST_CHECK(count == test_size);
    
    auto other_b = traits::sbegin();
    BOOST_CHECK(b == other_b);
}

BOOST_AUTO_TEST_CASE(test_auto_iter)
{
    iterator it = traits::sbegin();
    test_e other_e;
    for (auto e : traits()) {
        other_e = *it;
        BOOST_CHECK(e == other_e);
        ++it;
    }
    
    BOOST_CHECK(it == traits().end());
}

BOOST_AUTO_TEST_CASE(test_prefix_iter)
{
    iterator it = traits::sbegin();
    test_e other_e;
    for (auto e : traits()) {
        auto other_it = it++;
        other_e = *other_it;
        BOOST_CHECK(e == other_e);
    }
    
    BOOST_CHECK(it == traits().end());
}

BOOST_AUTO_TEST_CASE(test_enum_traits_good)
{
    for (auto e : traits()) {
        BOOST_CHECK(traits::good(e));
        utype val = lexical_enum_cast<utype>(e);
        BOOST_CHECK(traits::good(val));
    }
    
    utype val;
    test_e e;
    
    val = 3;
    e = static_cast<test_e>(val);
    BOOST_CHECK(traits::good(e) == false);
    BOOST_CHECK(traits::good(val) == false);
    
    try {
        test_e bad_e = enum_cast<test_e>(val);
        ELIB_UNUSED(bad_e);
        BOOST_CHECK(false);
    } catch (bad_enum_cast & ex) {
        BOOST_CHECK(true);
    }
    
    val = 4;
    e = static_cast<test_e>(val);
    BOOST_CHECK(traits::good(e) == false);
    BOOST_CHECK(traits::good(val) == false);
    try {
        test_e bad_e = enum_cast<test_e>(val);
        ELIB_UNUSED(bad_e);
        BOOST_CHECK(false);
    } catch (bad_enum_cast & ex) {
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_CASE(test_verify_enum)
{
    BOOST_CHECK(traits::verify_enum_traits());
}

BOOST_AUTO_TEST_SUITE_END()