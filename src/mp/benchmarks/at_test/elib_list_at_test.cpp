#include <elib/mp/list.hpp>
#include "../benchmark_helper.hpp"

using namespace elib::mp;

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