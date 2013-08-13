#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "elib/rw_lock.h"
#include "detail/rw_lock_impl.h"

#include <thread>
#include <type_traits>


#define READ lock_type_e::read
#define WRITE lock_type_e::write


using namespace ::elib::detail;

namespace elib {    
namespace unit_test {
    

typedef rw_lock_impl::lock_type_e lock_type_e;
typedef rw_lock_impl::request_group request_group;
typedef rw_lock_impl::list_type list_type;

    

struct test_rw_lock_impl {
    static list_type &
    get_lock_list(rw_lock_impl & l)
    { return l.m_groups; }
};

list_type &
get_lock_list(rw_lock_impl & l)
{
    return test_rw_lock_impl::get_lock_list(l);
}



void check_lock_group(rw_lock_impl & l, lock_type_e e, unsigned count,
                       bool allowed = true)
{
    list_type & list = get_lock_list(l);
    request_group & g = list.front();
    BOOST_CHECK(g.lock_type == e);
    BOOST_CHECK(g.lock_count == count);
    BOOST_CHECK(g.allowed == allowed);
}
    
    
BOOST_AUTO_TEST_SUITE(rw_lock_test_suite)


BOOST_AUTO_TEST_CASE(test_rw_lock_impl_imm_schedule)
{
    rw_lock_impl l;
    
    BOOST_CHECK(l._can_imm_schedule(READ));
    BOOST_CHECK(l._can_imm_schedule(WRITE));
    
    l.read_lock();
    BOOST_CHECK(l._can_imm_schedule(READ));
    BOOST_CHECK(l._can_imm_schedule(WRITE) == false);
    l.read_unlock();
    
    l.write_lock();
    BOOST_CHECK(l._can_imm_schedule(READ) == false);
    BOOST_CHECK(l._can_imm_schedule(WRITE) == false);
    l.write_unlock();
    
    BOOST_CHECK(l._can_imm_schedule(READ));
    BOOST_CHECK(l._can_imm_schedule(WRITE));
}

BOOST_AUTO_TEST_CASE(test_rw_lock_impl_read_lock)
{
    rw_lock_impl l;
    
    BOOST_CHECK(l.try_read_lock());
    check_lock_group(l, READ, 1);
    
    BOOST_CHECK(l.try_read_lock());
    check_lock_group(l, READ, 2);
    
    BOOST_CHECK(l.try_write_lock() == false);
    
    BOOST_CHECK(l._can_imm_schedule(READ) == true);
    BOOST_CHECK(l._can_imm_schedule(WRITE) == false);
    
    l.read_unlock();
    check_lock_group(l, READ, 1);
    
    l.read_unlock();
    BOOST_CHECK(get_lock_list(l).size() == 0);
}

BOOST_AUTO_TEST_CASE(test_rw_lock_impl_write)
{
    rw_lock_impl l;
    l.write_lock();
    check_lock_group(l, WRITE, 1);
    BOOST_CHECK(l.try_write_lock() == false);
    check_lock_group(l, WRITE, 1);
    BOOST_CHECK(l.try_read_lock() == false);
    check_lock_group(l, WRITE, 1);
    l.write_unlock();
    BOOST_CHECK(get_lock_list(l).size() == 0);
}


BOOST_AUTO_TEST_SUITE_END()
} /* namespace unit_test */
} /* namespace elib */