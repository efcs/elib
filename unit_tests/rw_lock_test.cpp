#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "elib/rw_lock.h"
#include "detail/rw_lock_impl.h"

#include <type_traits>

#define WRAP(fn)


namespace elib {
    
using namespace detail;
    
namespace unit_test {
    
    
class test_rw_lock_impl {
    
};
    
    
BOOST_AUTO_TEST_SUITE(rw_lock_test_suite)

  


BOOST_AUTO_TEST_SUITE_END()
} /* namespace unit_test */
} /* namespace elib */