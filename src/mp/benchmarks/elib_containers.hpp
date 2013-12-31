#include <elib/mp/vector.hpp>
#include <elib/mp/list.hpp>
#include <elib/mp/pack.hpp>

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#define BOOST_MPL_LIMIT_LIST_SIZE 50
#include <boost/mpl/list.hpp>
#include <boost/mpl/vector.hpp>

#include "benchmark_helper.hpp"

using ElibVector50 = typename elib::mp::vector<ENUM_50(int)>::type;
using ElibVector150 = typename elib::mp::vector<ENUM_150(int)>::type;
using ElibVector500 = typename elib::mp::vector<ENUM_500(int)>::type;
using ElibVector1000 = typename elib::mp::vector<ENUM_1000(int)>::type;

using ElibList50 = typename elib::mp::list<ENUM_50(int)>::type;
using ElibList150 = typename elib::mp::list<ENUM_150(int)>::type;
using ElibList500 = typename elib::mp::list<ENUM_500(int)>::type;
using ElibList1000 = typename elib::mp::list<ENUM_1000(int)>::type;

using ElibPack50 = typename elib::mp::pack<ENUM_50(int)>::type;
using ElibPack150 = typename elib::mp::pack<ENUM_150(int)>::type;
using ElibPack500 = typename elib::mp::pack<ENUM_500(int)>::type;
using ElibPack1000 = typename elib::mp::pack<ENUM_1000(int)>::type;

using BoostList50 = typename boost::mpl::list<ENUM_50(int)>::type;
using BoostVector50 = typename boost::mpl::vector<ENUM_50(int)>::type;
