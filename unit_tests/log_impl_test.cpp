#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/log.h"
#include "impl/log_impl.h"
#include "elib/enum_traits.h"

#include <string>
#include <map>


namespace elib {
    
using namespace detail;
    
namespace unit_test {


class test_basic_log_impl {
public:
   std::ostream &
   _get_stream(basic_log_impl & impl, level_e l)
   { return impl._get_stream(l); }
   
   bool 
   _should_print(basic_log_impl & impl, level_e l)
   { return impl._should_print(l); }
};

BOOST_AUTO_TEST_SUITE(_log_test_suite)

test_basic_log_impl log_helper; 

BOOST_AUTO_TEST_CASE(test_on)
{
    log_impl l;
    BOOST_CHECK(l.on());
    l.on(false);
    BOOST_CHECK(l.on() == false);
    l.on(true);
    BOOST_CHECK(l.on());
}

BOOST_AUTO_TEST_CASE(test_should_print)
{
    log_impl l;
    
    for (auto lev : enum_traits<level_e>()) {
        if (basic_log_impl::is_basic_level(lev)) {
            l.level(lev);
            BOOST_CHECK(l.level() == lev);
            
            for (auto e : enum_traits<level_e>()) {
                BOOST_CHECK(log_helper._should_print(l, e) == (e >= lev));
            }
        }
    }
    
    l.on(false);
    for (auto lev : enum_traits<level_e>()) {
        if (basic_log_impl::is_basic_level(lev)) {
            l.level(lev);
            BOOST_CHECK(l.level() == lev);
            
            for (auto e : enum_traits<level_e>()) {
                BOOST_CHECK(log_helper._should_print(l, e) == false);
            }
        }
    }
    
    
}


BOOST_AUTO_TEST_CASE(check_level_test)
{
    for (auto e : enum_traits<level_e>()) {
        BOOST_CHECK(basic_log_impl::is_raw_level(e) == 
                    (e == level_e::raw_out || e == level_e::raw_err));
        
        BOOST_CHECK(basic_log_impl::is_basic_level(e) ==
                    (e != level_e::raw_out && e != level_e::raw_err));
    }
    
}

BOOST_AUTO_TEST_CASE(invalid_prompt_test)
{
    log_impl l;
    
    for (auto e : enum_traits<level_e>()) {
        if (basic_log_impl::is_raw_level(e)) {
            try {
                l.prompt(e);
                BOOST_CHECK(false);
            } catch (std::logic_error & ex) {
                BOOST_CHECK(true);
            }
        }
    }
    
    for (auto e : enum_traits<level_e>()) {
        if (basic_log_impl::is_raw_level(e)) {
            try {
                l.prompt(e, "");
                BOOST_CHECK(false);
            } catch (std::logic_error & ex) {
                BOOST_CHECK(true);
            }
        }
    }
    
}

BOOST_AUTO_TEST_CASE(valid_prompt_test)
{
    log_impl l;
    
    std::map<level_e, std::string> pmap =
        { {level_e::debug, "debug: "},
          {level_e::info, "info: "},
          {level_e::step, "step: "},
          {level_e::warn, "warn: "},
          {level_e::err, "err: "},
          {level_e::fatal, "fatal: "}
        };
        
    for (auto e : enum_traits<level_e>()) {
        if (pmap.count(e))
            l.prompt(e, pmap.at(e));
    }
    
    for (auto e : enum_traits<level_e>()) {
        if (pmap.count(e)) {
            BOOST_CHECK(l.prompt(e) == pmap.at(e));
        }
    }
}

BOOST_AUTO_TEST_CASE(invalid_level_test)
{
    log_impl l;
    for (auto e : enum_traits<level_e>()) {
        if (basic_log_impl::is_raw_level(e)) {
            try {
                l.level(e);
                BOOST_CHECK(false);
            } catch (std::logic_error & ex) {
                BOOST_CHECK(true);
            }
        }
    }
    
}

BOOST_AUTO_TEST_CASE(valid_level_test)
{
    log_impl l;
    for (auto e : enum_traits<level_e>()) {
        if (basic_log_impl::is_basic_level(e)) {
            l.level(e);
            BOOST_CHECK(l.level() == e);
        }
    }
}


BOOST_AUTO_TEST_CASE(valid_log_test)
{
    log_impl l;
    l.on(false);
    
    for (auto e : enum_traits<level_e>()) {
            l.log(e, "");
            BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace unit_test */
} /* namespace elib */