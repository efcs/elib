#ifndef ELIB_MP_SINGLE_VIEW_HPP
#define ELIB_MP_SINGLE_VIEW_HPP

# include <elib/mp/get_impl.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/sequence.hpp>

namespace elib 
{
  namespace mp
  {
    
    
    struct single_view_tag {};
    
    
    struct single_view_model
      : model::mpl_sequence, model::random_access_sequence
    {};
    
    
    template <class T>
    struct single_view
    {
      using type = single_view;
      
      using class_type = single_view_tag;
      using model_type = single_view_model;
      
      using value_type = T;
    };
    
    
    template <class T, std::size_t N>
    struct single_view_iterator;
    
    template <class T>
    struct single_view_iterator<T, 0>
    {
      using type = T;
      using type_ = T;
      using pos_ = long_<0>;
      
      using model_type = model::random_access_iterator;
    };
    
    
    template <class T>
    struct single_view_iterator<T, 1>
    {
      using type_ = T;
      using pos_ = long_<1>;
      
      using model_type = model::random_access_iterator;
    };
    
    
    namespace detail
    {
      
      
      struct single_view_intrinsics
      {
        
        template <class S>
        using begin = 
          identity< single_view_iterator<typename S::value_type, 0> >;
        
        
        template <class S>
        using end = 
          identity< single_view_iterator<typename S::value_type, 1> >;
        
        
        template <class S>
        using front = identity< typename S::value_type >;
        
        
        template <class S>
        using back = identity< typename S::value_type >;
        
        
        template <class S, std::size_t N>
        struct at_c
        {
          using type = typename S::value_type;
          static_assert(N == 0, "0 is only valid index for at_c");
        };
        
        
        template <class S, class N>
        using at = at_c<S, N::type::value>;
        
        
        template <class S>
        using sequence_size = size_type<1>;
        
        
        template <class S>
        using empty = false_;
        
      };
      
      
      struct single_view_iterator_intrinsics
      {
        template <class It>
        using deref = identity< typename It::type >;
        
        template <class It>
        using next = 
          identity< 
            single_view_iterator<typename It::type_, It::pos_::value + 1> 
          >;
        
        template <class It>
        using prior = 
          identity<
              single_view_iterator<typename It::type_, It::pos_::value - 1>
            >;
        
        template <class It, class N>
        struct advance 
        {
          using type = 
            single_view_iterator<
                typename It::type_
              , It::pos_::value + N::type::value
              >;
          static_assert( N::type::value == 0 || N::type::value == 1 
                         || N::type::value == -1, 
                        " Only valid advance distances");
        };
        
        
        template <class It, long N>
        using advance_c = advance<It, long_<N>>;
        
        
        template <class It1, class It2>
        using distance = long_< It2::pos_::value - It1::pos_::value >;
      };
      
    }                                                       // namespace detail
    
    
    template <class T>
    struct get_impl< single_view<T> >
    {
      using type = detail::single_view_intrinsics;
    };
    
    
    template <class T, std::size_t Begin>
    struct get_impl< single_view_iterator<T, Begin> >
    {
      using type = detail::single_view_iterator_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SINGLE_VIEW_HPP */