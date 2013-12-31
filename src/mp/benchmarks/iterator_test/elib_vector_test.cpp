#include <elib/mp/vector.hpp>
#include <elib/mp/integral_constant.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/sequence.hpp>

#include "../benchmark_helper.hpp"

using namespace elib::mp;

int main()
{
  using T = vector<ENUM_50(int)>;
  using B = begin_t<T>;
  using E = advance_t<B, int_<49>>;
  
  E e{};
  unused(e);
}