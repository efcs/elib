#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#include <boost/mpl/vector.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/integral_c.hpp>

#include "../boost_vector.hpp"
#include "../benchmark_helper.hpp"

using namespace boost::mpl;

int main()
{
  using B = typename begin<BoostVector50>::type;
  using E = typename advance<B, int_<49>>::type;
  
  E e{};
  unused(e);
}