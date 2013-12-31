#include <elib/mp/pack.hpp>
#include <elib/mp/sequence.hpp>

#include "../benchmark_helper.hpp"

using namespace elib::mp;

int main()
{
  using T = pack<ENUM_100(int), ENUM_50(int)>;
  using E = pop_back_t<T>;
  
  E e{};
  unused(e);
}