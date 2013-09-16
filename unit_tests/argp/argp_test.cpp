#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/argp/arg_parser.hpp"
#include "elib/argp/arg.hpp"

#include "elib/enumeration/basic_enum_traits.hpp"

#include <vector>

#define ARG_OPTION(name, type, xarg_type, xcmd, xcmd_desc, xdesc) \
struct name { \
    static type value; \
\
    static constexpr arg_type_e arg_type = arg_type_e::xarg_type; \
    static constexpr char cmd[] = xcmd; \
    static constexpr char cmd_desc[] = xcmd_desc; \
    static constexpr char desc[] = xdesc; \
}; \
\
type name::value; \
constexpr char name::cmd[]; \
constexpr char name::cmd_desc[]; \
constexpr char name::desc[]


using namespace ::elib::argp;
using namespace ::elib::argp::detail;
using namespace ::elib::enumeration;



namespace elib {
namespace unit_test {
    
enum class test_arg_e {
    one,
    two,
    three
};

} /* namespace unit_test */

template <>
struct basic_enum_traits<unit_test::test_arg_e> {
    static constexpr unit_test::test_arg_e default_value = 
        unit_test::test_arg_e::one;
        
    static constexpr unit_test::test_arg_e first_value = 
        unit_test::test_arg_e::one;
        
    static constexpr unit_test::test_arg_e three_value = 
        unit_test::test_arg_e::three;
        

    static const std::map<unit_test::test_arg_e, std::string> name_map;
};

decltype(basic_enum_traits<unit_test::test_arg_e>::name_map)
basic_enum_traits<unit_test::test_arg_e>::name_map = 
{
    {unit_test::test_arg_e::one, "one"},
    {unit_test::test_arg_e::two, "two"},
    {unit_test::test_arg_e::three, "three"}
};


namespace unit_test {

    
ARG_OPTION(flag1, bool, flag, "-f,--flag", "[-f,--flag]", "flag 1 desc");
ARG_OPTION(opt1, std::string, option, "-o,--output", "-ofile,--output=file", "");

using std::vector;

    
BOOST_AUTO_TEST_SUITE(test_argp)


BOOST_AUTO_TEST_CASE(arg_test)
{
    test_arg_e e_val = test_arg_e::one;
    
    basic_arg<test_arg_e> o3(arg_type_e::option,
                               "-e,--enum",
                               "", "", e_val);
    
    std::vector<int> int_val;
    basic_arg<std::vector<int>> o5(arg_type_e::option,
                             "-I,--INT", "", "", int_val);
    
    tagged_arg<flag1> t;
    tagged_arg<opt1> o;
    
    typed_arg<std::string> o2(arg_type_e::option,
                                "-a,--Arg", 
                                "[-a=val,--Arg=val]", 
                                "");
    
    typed_arg<int> o4(arg_type_e::option,
                      "-i,--int", "", "");
    
    arg_parser par("hello");
    
    vector<std::string> args = {"invoke", "-f", "-ofilename", 
                                "--output=filename2", "-etwo", "--Arg=val",
                                "-i4", "-I1", "-I2", "-D"};
    
    par.add_option(t);
    par.add_option(o);
    par.add_option(o2);
    par.add_option(o3);
    par.add_option(o4);
    par.add_option(o5);

   
    par.run(args);

    
    BOOST_CHECK(flag1::value == true);
    BOOST_CHECK(opt1::value == "filename2");
    BOOST_CHECK(o2.value == "val");
    BOOST_CHECK(e_val == test_arg_e::two);
    BOOST_CHECK(o4.value = 4);
    BOOST_CHECK(int_val.size() == 2);
    BOOST_CHECK(int_val[0] == 1 && int_val[1] == 2);

}

BOOST_AUTO_TEST_SUITE_END()
    
}/* namespace unit_test */
} /* namespace elib */