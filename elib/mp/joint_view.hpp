#ifndef ELIB_MP_JOINT_VIEW_HPP
# define ELIB_MP_JOINT_VIEW_HPP

# include <elib/mp/get_impl.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/algorithm/iter_fold_n.hpp>
# include <elib/mp/detail/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct joint_view_tag {};
    
    
    struct joint_view_model 
      : model::forward_sequence
    {};
    
    
    template <
        class Seq1
      , class Seq2
      >
    struct joint_view
    {
      using type = joint_view;
      
      using class_type = joint_view_tag;
      using model_type = joint_view_model;
      
      using first = Seq1;
      using second = Seq2;
    };
    
    
    template <class It, class End, class Next = na, class NextEnd = na >
    struct joint_view_iterator;
    
    
    template <class It, class End, class Next, class NextEnd>
    struct joint_view_iterator
    {
      using deref = ::elib::mp::deref<It>;
      
      using next =
        if_<
            same_type<next_t<It>, End>
          , joint_view_iterator<Next, NextEnd>
          , joint_view_iterator<next_t<It>, End, Next, NextEnd>
          >;
      
      using tag = forward_iterator_tag;
    };
    
    
    template <class End, class Next, class NextEnd>
    struct joint_view_iterator<End, End, Next, NextEnd>;
    
    
    template <class It, class End>
    struct joint_view_iterator<It, End, na, na>
    {
      using deref = ::elib::mp::deref<It>;
      
      using next =
        identity<
          joint_view_iterator< next_t<It>, End >
        >;
        
      using tag = forward_iterator_tag;
    };
    
    
    template <class End>
    struct joint_view_iterator<End, End, na, na>
    {
      
      using tag = forward_iterator_tag;
    };
    
    
    namespace detail
    {
      
      struct joint_view_iterator_intrinsics
      {
        template <class It>
        using next = typename It::next;
        
        template <class It>
        using prior = typename It::prior;
        
        template <class It>
        using deref = typename It::deref;
        
        template <class It, std::size_t N>
        struct advance_c
          : advance_c<next_t<It>, N - 1>
        {};
        
        template <class It>
        struct advance_c<It, 0>
        {
          using type = It;
        };
        
        
        template <class It, class N>
        using advance = advance_c<It, N::type::value>;
        
        template <class It1, class It2>
        struct distance;
        
        
      };
      
      
      struct joint_view_intrinsics
      {
        
        
        template <class Seq>
        using sequence_size = 
          size_type<
            sequence_size_t< typename Seq::first >::value
            + sequence_size_t< typename Seq::second >::value
          >;
        
        
        template <class Seq>
        using empty = 
          and_< 
              empty<typename Seq::first> 
            , empty<typename Seq::second> 
            >;
            
            
        template <class Seq>
        struct begin
        {
          using first = typename Seq::first;
          using second = typename Seq::second;
          
          using type = 
            joint_view_iterator<
                begin_t<first>, end_t<first>
              , begin_t<second>, end_t<second>
              >;
        };
        
        
        template <class Seq>
        using end = identity<
          joint_view_iterator<
              end_t<typename Seq::second>
            , end_t<typename Seq::second>
            >
          >;
        
        
        template <class Seq>
        using front = ::elib::mp::deref< begin_t< Seq > >;
        
      };
      
      
    }                                                       // namespace detail
    
    
    template <class S1, class S2>
    struct get_impl< joint_view<S1, S2> >
    {
      using type = detail::joint_view_intrinsics;
    };
    
    
    
    template <class B, class E, class B1, class E1>
    struct get_impl< joint_view_iterator<B, E, B1, E1> >
    {
      using type = detail::joint_view_iterator_intrinsics;
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_JOINT_VIEW_HPP */