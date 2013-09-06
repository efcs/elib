#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/size_type.h"

#include <string>
#include <type_traits>
#include <limits>

using namespace elib;

typedef size_type_traits<std::string::size_type> string_size_type;

template <typename T>
struct check_size_type {
private:
    typedef size_type_traits<T> traits;
    typedef typename traits::size_type size_type;

    static constexpr bool m_is_integral = std::is_integral<size_type>::value;
    static constexpr bool m_is_signed = std::is_signed<size_type>::value;
    
    static constexpr size_type m_npos = traits::npos;
    static constexpr size_type m_max = std::numeric_limits<size_type>::max();
    
    static constexpr bool m_npos_good = ( m_is_signed && m_npos == 
                                          static_cast<size_type>(-1)) ||
                                        ( ! m_is_signed && m_npos == m_max);
    
public:
    
    static constexpr bool value = m_is_integral && m_npos_good;
};


BOOST_AUTO_TEST_SUITE(size_type_test_suite)

BOOST_AUTO_TEST_CASE(size_type_init)
{
    BOOST_CHECK(check_size_type<elib_size_type::size_type>::value);
    BOOST_CHECK(check_size_type<int>::value);
    BOOST_CHECK(check_size_type<unsigned>::value);
    BOOST_CHECK(check_size_type<std::size_t>::value);
    BOOST_CHECK(check_size_type<elib_size_t>::value);
}

BOOST_AUTO_TEST_SUITE_END()
