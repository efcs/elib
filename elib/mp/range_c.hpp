#ifndef ELIB_MP_RANGE_C_HPP
# define ELIB_MP_RANGE_C_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/detail/sequence_fwd.hpp>
# include <elib/mp/sequence_metafunctions.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T, T Begin, T End>
    struct range_c 
    {
      using type = range_c;
      using tag = detail::range_c_tag;
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_RANGE_C_HPP */