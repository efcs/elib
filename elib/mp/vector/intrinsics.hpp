#ifndef ELIB_MP_VECTOR_INTRINSICS_HPP
#define ELIB_MP_VECTOR_INTRINSICS_HPP

# include <elib/mp/vector/fwd.hpp>
# include <elib/mp/vector/vector.hpp>
# include <elib/mp/vector/iterator.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/sequence.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class Vector, std::size_t N>
      struct vector_at_impl
      {
        using type = decltype( 
          Vector::index_lookup(
            size_type_<Vector::lower_bound_::value + N>()
          )
        );
      };
      
      struct vector_intrinsics
      {
        // fwd
        //template <class S> struct front;
        //template <class S> struct back;
        //template <class S> struct sequence_size;
        //template <class S> struct O1_size;
        //template <class S> struct empty;
        //template <class S> struct begin;
        //template <class S> struct end;
        //template <class S, class N> struct at;
        //template <class S, std::size_t N> struct at_c;
        //template <class S> struct clear;
        //template <class S, class T> struct push_back;
        //template <class S> struct pop_back;
        //template <class S, class T> struct push_front;
        //template <class S> struct pop_front;
        
        template <class Vector>
        using front = vector_at_impl<Vector, 0>;
        
        template <class Vector>
        using back = vector_at_impl<Vector, Vector::size::value - 1>;
        
        template <class Vector>
        using sequence_size = typename Vector::size;
        
        template <class Vector>
        using O1_size = typename Vector::size;
        
        template <class Vector>
        using empty = bool_< Vector::size::value == 0>;
        
        template <class Vector>
        using begin = 
          identity<
            vector_iterator<Vector, 0>
          >;
        
        template <class Vector>
        using end = 
          identity<
            vector_iterator<Vector, Vector::size::value>
          >;
        
        template <class Vector, class N>
        using at = vector_at_impl<Vector, N::type::value>;
        
        template <class Vector, std::size_t N>
        using at_c = vector_at_impl<Vector, N>;
        
        template <class>
        using clear = vector<>;
        
        template <class Vector, class T>
        using push_front = vector_item<vector_front_tag, T, Vector>;
        
        template <class Vector>
        using pop_front = vector_mask<vector_front_tag, Vector>;
        
        template <class Vector, class T>
        using push_back = vector_item<vector_back_tag, T, Vector>;
        
        template <class Vector>
        using pop_back = vector_mask<vector_back_tag, Vector>;
        
        
      };                                            // struct vector_intrinsics
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VECTOR_INTRINSICS_HPP */