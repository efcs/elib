#include <elib/mp/vector.hpp>
#include <elib/mp/list.hpp>
#include <elib/mp/pack.hpp>

#include "../benchmark_helper.hpp"

using Vector = typename elib::mp::vector_c<int, ENUM_0_TO_500()>::type;
using List = typename elib::mp::list_c<int, ENUM_0_TO_500()>::type;
using Pack = typename elib::mp::pack_c<int, ENUM_0_TO_500()>::type;

