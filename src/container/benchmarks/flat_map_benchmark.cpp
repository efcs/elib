#include <elib/container/flat_map.hpp>
#include <elib/container/linear_flat_map.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <cstddef>

#define STR(x) XSTR(x)
#define XSTR(x) #x

using value_type = std::pair<int, int>;
using flat_map = elib::flat_map<int, int>;
using linear_flat_map = elib::linear_flat_map<int, int>;
using standard_map = std::map<int, int>;


std::vector<value_type> make_values(int to_add)
{
    std::vector<value_type> dest;
    dest.reserve(to_add);
    
    for (int i=0; i < to_add; ++i) {
        dest.emplace_back(value_type(i, i));
    }
    
    std::random_shuffle(dest.begin(), dest.end());
    return dest;
}

template <class MapType>
MapType construct_test(std::vector<value_type> const & v)
{
    MapType m(v.begin(), v.end());
    return m;
}

template <class MapType>
void find_test(std::vector<value_type> const & v, MapType const & m)
{
    for (int i=0; i < 10; ++i) {
        for (auto & kv : v) {
            m.find(kv.first);
        }
    }
}

template <class MapType>
int iter_test(MapType const & m)
{
    int accum = 0;
    for (int i=0; i < 100; ++i) {
        for (auto & kv : m) {
            accum += kv.first;
            accum %= 2;
        }
    }
    return accum;
}

template <class Fn>
void time(const char *name, Fn f)
{
    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();
    f();
    auto end = clock::now();
    clock::duration tp = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(tp);
    auto mm = std::chrono::duration_cast<std::chrono::microseconds>(tp);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp);
    auto s = std::chrono::duration_cast<std::chrono::seconds>(tp);
    
    std::cout << name << " test took " << s.count() << " s "
              << "(" <<  ms.count() << " ms) "
              << "(" <<  mm.count() << " micros) "
              << "(" <<  ns.count() << " ns) "
              << std::endl;
}

int main()
{
    std::cout << "Testing " STR(MAP_TYPE) << std::endl;
    using Map = MAP_TYPE;
    auto kv = make_values(100000000);
    Map m;
    int x = 0;
    time("Construct", [&]() { m = construct_test<Map>(kv); });
    //time("Find", [&]() { find_test(kv, m); });
    time("Iterate", [&]() { x = iter_test(m); });
    std::cout << x;
}