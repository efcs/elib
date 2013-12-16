#ifndef ELIB_MP_PARAM_PACK_DETAIL_CONCAT_HPP
#define ELIB_MP_PARAM_PACK_DETAIL_CONCAT_HPP

# include <elib/mp/param_pack/param_pack.hpp>

namespace elib 
{
  namespace mp
  {

    template <class LeftPack, class RightPack>
    struct param_pack_concat;
      
      
    template <class ...Left, class ...Right>
    struct param_pack_concat< param_pack<Left...>, param_pack<Right...> >
    {
      using type = param_pack<Left..., Right...>;
    };

    
    template <class LeftPack, class RightPack>
    using param_pack_concat_t = 
      typename param_pack_concat<LeftPack, RightPack>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PARAM_PACK_CONCAT_HPP */