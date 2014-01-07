#ifndef ELIB_MP_VECTOR_VECTOR_HPP
#define ELIB_MP_VECTOR_VECTOR_HPP

# include <elib/mp/vector/fwd.hpp>
# include <elib/mp/vector/item.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/void.hpp>

namespace elib 
{
  namespace mp
  {

    
    struct vector_model
      : model::random_access_sequence
      , model::front_extensible_sequence
      , model::back_extensible_sequence
      , model::O1_size
    {};
    
  
    template <class ...Args>
    struct vector
    {
      using type = vector;
      
      /* for sequence_traits */
      using class_type = vector_tag;
      using model_type = vector_model;
      
      using lower_bound_ = size_type<32767>;
      using upper_bound_ = lower_bound_;
      using size = size_type<0>;
      
      static void_ index_lookup(...);
      
      static_assert(sizeof...(Args) == 0,  
                    "Overload resolution check");
    };
    
   
    template <class First, class ...Rest>
    struct vector<First,  Rest...>
      : vector<Rest...>
    {
      using type = vector;
      using base = vector<Rest...>;
      
      using lower_bound_ = size_type<base::lower_bound_::value - 1>;
      using upper_bound_ = typename base::upper_bound_;
      
      using size = size_type< base::size::value + 1 >;
      using index_ = lower_bound_;
      
      static First index_lookup(index_);
      using base::index_lookup;
    };
    
    
    template <class A1, class A2, class ...Rest>
    struct vector<A1, A2, Rest...>
      : vector<Rest...>
    {
      using type = vector;
      using base = vector<Rest...>;
      
      using lower_bound_ = size_type< base::lower_bound_::value - 2 >;
      using upper_bound_ = typename base::upper_bound_;
      
      using size = size_type< base::size::value + 2 >;
      
      using index_1 = lower_bound_;
      using index_2 = size_type< lower_bound_::value + 1>;
      
      static A1 index_lookup(index_1);
      static A2 index_lookup(index_2);
      using base::index_lookup;
    };
    
    
    template <class A1, class A2, class A3, class ...Rest>
    struct vector<A1, A2, A3, Rest...>
      : vector<Rest...>
    {
      using type = vector;
      using base = vector<Rest...>;
      
      using lower_bound_ = size_type<base::lower_bound_::value - 3>;
      using upper_bound_ = typename base::upper_bound_;
      
      using size = size_type< base::size::value +  3>;
      
      using index_1 = lower_bound_;
      using index_2 = size_type< lower_bound_::value + 1>;
      using index_3 = size_type< lower_bound_::value + 2 >;
      
      static A1 index_lookup(index_1);
      static A2 index_lookup(index_2);
      static A3 index_lookup(index_3);
      using base::index_lookup;
    };
    
    template <class A1, class A2, class A3, class A4, class ...Rest>
    struct vector<A1, A2, A3, A4, Rest...>
      : vector<Rest...>
    {
      using type = vector;
      using base = vector<Rest...>;
      
      using lower_bound_ = size_type< base::lower_bound_::value - 4 >;
      using upper_bound_ = typename base::upper_bound_;
      
      using size = size_type< base::size::value +  4>;
      
      using index_1 = lower_bound_;
      using index_2 = size_type< lower_bound_::value + 1 >;
      using index_3 = size_type< lower_bound_::value + 2 >;
      using index_4 = size_type< lower_bound_::value + 3 >;
      
      static A1 index_lookup(index_1);
      static A2 index_lookup(index_2);
      static A3 index_lookup(index_3);
      static A4 index_lookup(index_4);
      
      using base::index_lookup;
    };
    
    
    template <class A1, class A2, class A3, class A4, class A5, class ...Rest>
    struct vector<A1, A2, A3, A4, A5, Rest...>
      : vector<Rest...>
    {
      using type = vector;
      using base = vector<Rest...>;
      
      using lower_bound_ = size_type< base::lower_bound_::value - 5 >;
      using upper_bound_ = typename base::upper_bound_;
      
      using size = size_type< base::size::value +  5 >;
      
      using index_1 = lower_bound_;
      using index_2 = size_type< lower_bound_::value + 1 >;
      using index_3 = size_type< lower_bound_::value + 2 >;
      using index_4 = size_type< lower_bound_::value + 3 >;
      using index_5 = size_type< lower_bound_::value + 4 >;
      
      static A1 index_lookup(index_1);
      static A2 index_lookup(index_2);
      static A3 index_lookup(index_3);
      static A4 index_lookup(index_4);
      static A5 index_lookup(index_5);
      using base::index_lookup;
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
