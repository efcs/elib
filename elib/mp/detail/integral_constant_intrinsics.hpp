#ifndef ELIB_MP_DETAIL_INTEGRAL_CONSTANT_INTRINSICS_HPP
#define ELIB_MP_DETAIL_INTEGRAL_CONSTANT_INTRINSICS_HPP

# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/iterator.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      
      struct integral_constant_intrinsics
      {
        template <class IntC> struct deref;
        template <class IntC> struct next;
        template <class IntC> struct prior;
        template <class IntC> struct value_type;
        
        
        template <class IntC>
        struct deref : IntC
        {};
        
        template <class IntC>
        struct next 
          : integral_constant<
              typename IntC::value_type
            , static_cast<typename IntC::value_type>(IntC::value + 1)
          >
        {};
        
        
        template <class IntC>
        struct prior
          : integral_constant<
              typename IntC::value_type
            , static_cast<typename IntC::value_type>(IntC::value - 1)
          >
        {};
        

        template <class IntC>
        struct value_type
        {
          using type = typename IntC::value_type;
        };
        
        
      };                                 // struct integral_constant_intrinsics
      
    }                                                       // namespace detail
    
    
    template <class T, T Value>
    struct get_impl< integral_constant<T, Value> >
    {
      using type = detail::integral_constant_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_INTEGRAL_CONSTANT_INTRINSICS_HPP */