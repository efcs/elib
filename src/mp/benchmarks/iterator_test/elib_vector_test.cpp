#include <elib/mp/vector.hpp>
#include <elib/mp/integral_constant.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/sequence.hpp>

#include "../elib_containers.hpp"
#include "../benchmark_helper.hpp"

using namespace elib::mp;

int main()
{
  using T = ElibVector1000;
  using B = begin_t<T>;
  using E = advance_t<B, int_<99>>;
  
  unused(E{});
}