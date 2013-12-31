#ifndef ELIB_MP_VIEW_EMPTY_SEQUENCE_HPP
#define ELIB_MP_VIEW_EMPTY_SEQUENCE_HPP

# include <elib/mp/get_impl.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/detail/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct empty_sequence_tag {};
    
    struct empty_sequence_model
      : model::mpl_sequence, model::random_access_sequence
    {};
    
    
    struct empty_sequence
    {
      using type = empty_sequence;
      using class_type = empty_sequence_tag;
      using model_type = empty_sequence_model;
    };
    
    
    struct empty_sequence_iterator
    {
      using tag = random_access_iterator_tag;
    };
    
    
    namespace detail
    {
      
      struct empty_sequence_intrinsics
      {
        
        template <class Seq>
        using sequence_size = size_type<0>;
        
        template <class Seq>
        using empty = true_;
        
        template <class Seq>
        using begin = identity<empty_sequence_iterator>;
        
        template <class Seq>
        using end = identity<empty_sequence_iterator>;
        
        template <class Seq> struct front;
        template <class Seq> struct back;
        template <class Seq, class N> struct at;
        template <class Seq, std::size_t N> struct at_c;
      };                                           // empty_sequence_intrinsics
      
      
      struct empty_sequence_iterator_intrinsics
      {
        template <class It>
        struct deref;
        
        template <class It>
        struct next;
        
        template <class It, class N>
        struct advance
        {
          using type = It;
          static_assert(N::type::value == 0, "may only be zero");
        };
        
        template <class It, long N>
        using advance_c = advance<It, long_<N>>;
        
        template <class It, class It1>
        using distance = long_<0>;
      };
      
    }                                                       // namespace detail
    
    
    template <>
    struct get_impl< empty_sequence >
    {
      using type = detail::empty_sequence_intrinsics;
    };
    
    
    template <>
    struct get_impl<empty_sequence_iterator >
    {
      using type = detail::empty_sequence_iterator_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VIEW_EMPTY_SEQUENCE_HPP */