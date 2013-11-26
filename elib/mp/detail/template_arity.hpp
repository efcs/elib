#ifndef ELIB_MP_TEMPLATE_ARITY_HPP
# define ELIB_MP_TEMPLATE_ARITY_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <typename T>
      struct template_arity
      {
        using type = na;
      };
      
      
      template <template <class...> class T, class ...Args>
      struct template_arity<T<Args...>> : int_<sizeof...(Args)>
      {};
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TEMPLATE_ARITY_HPP */