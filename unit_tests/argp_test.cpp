#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/argp/arg_parser.h"
#include "elib/elog.h"


using namespace ::elib::argp;
using namespace ::elib::argp::detail;

namespace elib {
namespace unit_test {
    
BOOST_AUTO_TEST_SUITE(test_argp)


BOOST_AUTO_TEST_CASE(arg_test)
{
    arg_parser par("hello");
    int x;
    basic_arg<int> arg(arg_type_e::option, "-f,--FAIL", "[-f,--FAIL=]", "desc",
                        x);
    par.add_option(arg);
    elog::raw_out(par.description());
    
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
    
}/* namespace unit_test */
} /* namespace elib */