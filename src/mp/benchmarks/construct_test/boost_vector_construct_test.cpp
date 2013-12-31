#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#include <boost/mpl/vector.hpp>

#include "../benchmark_helper.hpp"

int main()
{
  boost::mpl::vector<ENUM_10(int)> v;
  unused(v);
}