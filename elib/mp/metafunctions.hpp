#ifndef ELIB_MP_METAFUNCTIONS_HPP
#define ELIB_MP_METAFUNCTIONS_HPP
# 
// type selection
# include <elib/mp/metafunction/if.hpp>
# // invocation
# include <elib/mp/metafunction/apply.hpp>
# include <elib/mp/metafunction/apply_wrap.hpp>
# include <elib/mp/metafunction/unpack_args.hpp>
# // composition and arg binding
# include <elib/mp/metafunction/arg.hpp>
# include <elib/mp/metafunction/placeholders.hpp>
# include <elib/mp/metafunction/lambda.hpp>
# include <elib/mp/metafunction/bind.hpp>
# include <elib/mp/metafunction/quote.hpp>
# include <elib/mp/metafunction/protect.hpp>
# // common metafunctions
# include <elib/mp/metafunction/arithmetic.hpp>
# include <elib/mp/metafunction/comparison.hpp>
# include <elib/mp/metafunction/logical.hpp>
# include <elib/mp/metafunction/bitwise.hpp>
# include <elib/mp/metafunction/increment.hpp>
# include <elib/mp/metafunction/decrement.hpp>
# // misc
# include <elib/mp/metafunction/identity.hpp>
# include <elib/mp/metafunction/inherit.hpp>
# include <elib/mp/metafunction/inherit_linearly.hpp>
# include <elib/mp/metafunction/always.hpp>
# include <elib/mp/metafunction/min_max.hpp>
# include <elib/mp/metafunction/sizeof.hpp>
# include <elib/mp/metafunction/intc_cast.hpp>
# 
#endif /* ELIB_MP_METAFUNCTIONS_HPP */