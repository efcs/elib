#ifndef ELIB_MP_VECTOR_VECTOR_HPP
#define ELIB_MP_VECTOR_VECTOR_HPP

# include <elib/mp/vector/fwd.hpp>
# include <elib/mp/vector/item.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/void.hpp>

namespace elib 
{
  namespace mp
  {

    template <class ...Args>
    struct vector
    {
      using type = vector;
      
      /* for sequence_traits */
      using class_type = vector_tag;
      using model_type = model::mpl_random_access_sequence;
      
      using lower_bound_ = size_type<32767>;
      using upper_bound_ = lower_bound_;
      using size = size_type<0>;
      
      static void_ index_lookup(...);
      
      static_assert(sizeof...(Args) == 0,  
                    "Overload resolution check");
    };
    
    
    template <class First, class ...Rest>
    struct vector<First,  Rest...>
      : detail::vector_item<
          detail::vector_front_tag, First, vector<Rest...>
        >
    {
      using type = vector;
    };
    
    
    template <class T, T ...Values>
    using vector_c = vector< integral_constant<T, Values>... >;
    
    
    template <class ...Args>
    struct get_impl< vector<Args...> >
    {
      using type = detail::vector_intrinsics;
    };
    
    template <class Tag, class T, class Vector>
    struct get_impl< detail::vector_item<Tag, T, Vector> >
    {
      using type = detail::vector_intrinsics;
    };
    
    template <class Tag, class Vector>
    struct get_impl< detail::vector_mask<Tag, Vector> >
    {
      using type = detail::vector_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VECTOR_VECTOR_HPP */
