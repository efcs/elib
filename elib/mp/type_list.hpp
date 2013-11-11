#ifndef ELIB_MP_TYPE_LIST_HPP
# define ELIB_MP_TYPE_LIST_HPP

# include <elib/mp/config.hpp>

namespace elib 
{
  namespace mp
  {
    
      
    template <class ...Args>
    struct type_list
    {
      typedef type_list type;
    };
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPE_LIST_HPP */