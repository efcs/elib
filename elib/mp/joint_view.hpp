#ifndef ELIB_MP_JOINT_VIEW_HPP
# define ELIB_MP_JOINT_VIEW_HPP

# include <elib/mp/get_impl.hpp>
# include <elib/mp/arithmetic.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/iterator_intrinsics.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/sequence.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct joint_view_tag {};
    
    
    struct joint_view_model 
      : model::forward_sequence
    {};
    
    
    template <class Seq1, class Seq2>
    struct joint_view
    {
      using type = joint_view;
      using class_type = joint_view_tag;
      using model_type = joint_view_model;
      
      using seq1_ = Seq1;
      using seq2_ = Seq2;
    };
    
    
    template <class FIt, class FEnd, class SIt, class SEnd>
    struct joint_view_iterator;
    
    /* in first iterator */
    template <class FIt, class FEnd, class SIt, class SEnd>
    struct joint_view_iterator
    {
      using model_type = model::forward_iterator;
      
      using item = mp::deref_t<FIt>;
      using next = joint_view_iterator< mp::next_t<FIt>, FEnd, SIt, SEnd >;
    };
    
    
    template <class FEnd, class SIt, class SEnd>
    struct joint_view_iterator<FEnd, FEnd, SIt, SEnd>
    {
      using model_type = model::forward_iterator;
      
      using item = mp::deref_t<SIt>;
      using next = joint_view_iterator<FEnd, FEnd, mp::next_t<SIt>, SEnd>;
    };
    
    
    template <class FEnd, class SEnd>
    struct joint_view_iterator<FEnd, FEnd, SEnd, SEnd>
    {
      using model_type = model::forward_iterator;
    };
    
    namespace detail
    {
      struct joint_view_intrinsics
      {
        template <class Seq>
        using sequence_size =
          add<
              mp::sequence_size<typename Seq::seq1_>
            , mp::sequence_size<typename Seq::seq2_>
            >;
            
        template <class Seq>
        using empty = 
          and_<
            mp::empty<typename Seq::seq1_>
          , mp::empty<typename Seq::seq2_>
          >;
        
        template <class Seq>
        using begin =
          identity<
            joint_view_iterator<
                mp::begin_t<typename Seq::seq1_>
              , mp::end_t<typename Seq::seq1_>
              , mp::begin_t<typename Seq::seq2_>
              , mp::end_t<typename Seq::seq2_>
            >
          >;
        
        template <class Seq>
        using end =
          identity<
              joint_view_iterator<
                  mp::end_t<typename Seq::seq1_>
                , mp::end_t<typename Seq::seq1_>
                , mp::end_t<typename Seq::seq2_>
                , mp::end_t<typename Seq::seq2_>
                >
            >;
        
        template <class Seq>
        using front = mp::deref< typename begin<Seq>::type >;
        
      };
      
      
    }                                                       // namespace detail
  
    template <class Seq1, class Seq2>
    struct get_impl< joint_view<Seq1, Seq2> >
    {
      using type = detail::joint_view_intrinsics;
    };
    
    
    template <class FIt, class FEnd, class SIt, class SEnd>
    struct get_impl< joint_view_iterator<FIt, FEnd, SIt, SEnd> >
    {
      using type = forward_iterator_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_JOINT_VIEW_HPP */