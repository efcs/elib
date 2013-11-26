#ifndef ELIB_MP_IS_PLACEHOLDER_HPP
# define ELIB_MP_IS_PLACEHOLDER_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>
# include <elib/mp/metafunction/arg.hpp>

# include <cstddef>


namespace elib 
{
  namespace mp
  {
    
    template <typename T>
    struct is_placeholder : false_
    {};
    
    template <std::size_t N>
    struct is_placeholder<arg<N>> : true_
    {};
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_IS_PLACEHOLDER_HPP */