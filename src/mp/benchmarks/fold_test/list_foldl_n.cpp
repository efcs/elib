#include "containers.hpp"
#include "fold_helper.hpp"



int main()
{
  using T = iter_foldl_n_count<List, void>;
  ((void)T{});
}