#ifndef ELIB_MP_PARAM_PACK_PARAM_PACK_HPP
# define ELIB_MP_PARAM_PACK_PARAM_PACK_HPP

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct param_pack
    {
      using type = param_pack;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PARAM_PACK_PARAM_PACK_HPP */