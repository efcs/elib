#include <elib/mp/vector.hpp>
#include <elib/mp/sequence.hpp>

#include "../elib_containers.hpp"
#include "../benchmark_helper.hpp"

using namespace elib::mp;

int main()
{
  using T = typename ElibVector1000::type;
  using E = pop_back_t<T>;
  
  unused(E{});
}