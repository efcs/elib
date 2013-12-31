#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50

#include "../elib_vector.hpp"
#include "../benchmark_helper.hpp"

using namespace boost::mpl;

int main()
{
  using T = vector<ENUM_50(int)>;
  using E = typename pop_back<>::type;
  
  E e{};
  unused(e);
}
