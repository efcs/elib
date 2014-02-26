#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/optional.hpp"
#include "elib/aux.hpp"

#include <string>

using namespace elib;

constexpr class dummy_class_t {} dummy_class{};

class nested_ref_class
{
public:
    constexpr nested_ref_class(dummy_class_t const & d) : m_ref(d) {}
    
private:
    dummy_class_t const & m_ref;
};

using test_type = nested_ref_class;

BOOST_AUTO_TEST_SUITE(elib_optional_test_suite)

BOOST_AUTO_TEST_CASE(elib_optional_ctor_tests)
{
    // ctor 1
    optional<test_type> o1;
    BOOST_CHECK(!o1);
    
    // ctor 2
    optional<test_type> o2(nullopt);
    BOOST_CHECK(!o2);
    
    // ctor 3 (copy)
    optional<test_type> o3(o2);
    BOOST_CHECK(!o3);
    
    // ctor 4 (move)
    optional<test_type> o4(elib::move(o3));
    BOOST_CHECK(!o4);
    
    // ctor 5 (copy object)
    test_type t(dummy_class);
    optional<test_type> o5(t);
    BOOST_CHECK(bool(o5));
    
    // ctor 6 (move object)
    optional<test_type> o6(test_type{dummy_class});
    BOOST_CHECK(bool(o6));
    
    // ctor 7 (construct inplace)
    optional<test_type> o7(in_place, dummy_class);
    BOOST_CHECK(bool(o7));
    
    //TODO
    // ctor 8 (inplace, init list)
    // optional<> o8(in_place, std::initializer_list<int>{0, 1});
}

BOOST_AUTO_TEST_CASE(test_assignment_operator)
{
    // assign 1 (nullopt)
    {
        optional<test_type> ninit;
        optional<test_type> init(test_type{dummy_class});
        
        ninit = nullopt;
        BOOST_CHECK(!ninit);
        
        init = nullopt;
        BOOST_CHECK(!init);
    }
    
    // assign 2 (copy)
    // NOTE: test_type not used since it has no assignment operator
    {
        optional<int> ninit;
        optional<int> init(0);
        
        optional<int> to;
        
        to = init;
        BOOST_CHECK(bool(init));
        
        to = ninit;
        BOOST_CHECK(!to);
    }
    
    // assign 3 (move)
    {
        optional<int> ninit;
        optional<int> init(0);
        
        optional<int> to;
        
        to = elib::move(init);
        BOOST_CHECK(bool(to));
        BOOST_CHECK(!init);
        
        to = elib::move(ninit);
        BOOST_CHECK(!to);
        BOOST_CHECK(!ninit);
    }
    
    // assign 4 (direct assignment)
    {
        optional<int> ninit;
        optional<int> init(0);
        
        ninit = 1;
        BOOST_CHECK(bool(ninit));
        BOOST_CHECK(*ninit == 1);
        
        init = 1;
        BOOST_CHECK(bool(init));
        BOOST_CHECK(*init == 1);
    }
}

BOOST_AUTO_TEST_CASE(emplace_test)
{
    optional<test_type> ninit;
    ninit.emplace(dummy_class);
    BOOST_CHECK(bool(ninit));
    
    optional<test_type> init(test_type{dummy_class});
    init.emplace(dummy_class);
    BOOST_CHECK(bool(init));
}

BOOST_AUTO_TEST_SUITE_END()