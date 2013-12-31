#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 50
#include <boost/mpl/list.hpp>

#include "../benchmark_helper.hpp"

int main()
{
  boost::mpl::list<ENUM_10(int)> v;
  unused(v);
}