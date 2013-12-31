#include <elib/mp/pack.hpp>
#include <elib/mp/integral_constant.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/sequence.hpp>

#include "../benchmark_helper.hpp"

using namespace elib::mp;

int main()
{
  using T = pack<ENUM_5000(int)>;
  using B = begin_t<T>;
  using E = advance_t<B, int_<4000>>;
  
  E e{};
  unused(e);
}