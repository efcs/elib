#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 50
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>

#include "../benchmark_helper.hpp"

using namespace boost::mpl;

template <class S, class T>
using at_t = typename at<S, T>::type;

int main()
{
  using T = list<ENUM_50(int)>;
  using AT0 = at_t<T, int_<0>>;
  using AT25 = at_t<T, int_<25>>;
  using AT_END = at_t<T, int_<49>>;
  
  AT0 at0{};
  AT25 at25{};
  AT_END atend{};
  unused(at0, at25, atend);
}