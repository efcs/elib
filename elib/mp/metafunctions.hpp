#ifndef ELIB_MP_METAFUNCTIONS_HPP
# define ELIB_MP_METAFUNCTIONS_HPP
# 
// type selection
# include <elib/mp/metafunctions/if.hpp>
# // invocation
# include <elib/mp/metafunctions/apply.hpp>
# include <elib/mp/metafunctions/apply_wrap.hpp>
# include <elib/mp/metafunctions/unpack_args.hpp>
# // composition and arg binding
# include <elib/mp/metafunctions/arg.hpp>
# include <elib/mp/metafunctions/lambda.hpp>
# include <elib/mp/metafunctions/bind.hpp>
# include <elib/mp/metafunctions/quote.hpp>
# include <elib/mp/metafunctions/protect.hpp>
# // common metafunctions
# include <elib/mp/metafunctions/arithmetic.hpp>
# include <elib/mp/metafunctions/comparison.hpp>
# include <elib/mp/metafunctions/logical.hpp>
# include <elib/mp/metafunctions/bitwise.hpp>
# // misc
# include <elib/mp/metafunctions/identity.hpp>
# include <elib/mp/metafunctions/always.hpp>
# include <elib/mp/metafunctions/min_max.hpp>
# include <elib/mp/metafunctions/sizeof.hpp>
# 
#endif /* ELIB_MP_METAFUNCTIONS_HPP */