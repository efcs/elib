#ifndef ELIB_MP_METAFUNCTION_INHERIT_LINEARLY_HPP
#define ELIB_MP_METAFUNCTION_INHERIT_LINEARLY_HPP

# include <elib/mp/algorithm/fold.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Types, class Node, class Root>
    struct inherit_linearly : fold<Types, Node, Root>
    {};
    
    template <class Types, class Node, class Root>
    using inherit_linearly_t = fold_t<Types, Node, Root>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_INHERIT_LINEARLY_HPP */