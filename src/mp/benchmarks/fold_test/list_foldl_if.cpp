#include "containers.hpp"
#include "fold_helper.hpp"



int main()
{
  using T = iter_foldl_if_count<List, void>;
  ((void)T{});
}