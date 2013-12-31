#include "containers.hpp"
#include "fold_helper.hpp"



int main()
{
  using T = iter_foldl_n_count<Vector, void>;
  ((void)T{});
}