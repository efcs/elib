#include <elib/mp/pack.hpp>

#include "../benchmark_helper.hpp"

int main()
{
  elib::mp::pack<ENUM_50(int)> l;
  unused(l);
}