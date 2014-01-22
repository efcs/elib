#ifndef ELIB_MP_FILTER_VIEW_HPP
#define ELIB_MP_FILTER_VIEW_HPP

# include <elib/mp/apply.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/iterator_intrinsics.hpp>
# include <elib/mp/iterator_range.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/algorithm/count.hpp>
# include <elib/mp/algorithm/find.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct filter_view_tag {};
    
    
    struct filter_view_model
      : model::forward_sequence
    {};
    
    
    template <class Seq, class Pred>
    struct filter_view
    {
      using type = filter_view;
      using class_type = filter_view_tag;
      using model_type = filter_view_model;
      
      using seq_ = Seq;
      using pred_ = Pred;
    };
    
    
    template <class It, class End, class Pred>
    struct filter_view_iterator
    {
      using model_type = model::forward_iterator;
      
      using it_ = It;
      using end_ = End;
      using pred_ = Pred;
    };
    
    
    namespace detail
    {
      
      struct filter_view_intrinsics
      {
        template <class Seq>
        using sequence_size = 
          count_if< 
            typename Seq::seq_
          , typename Seq::pred_
          >;
        
        
        template <class Seq>
        using empty = bool_< sequence_size<Seq>::type::value == 0 >;
        
        template <class Seq>
        using begin = 
          identity< 
              filter_view_iterator<
                  find_if_t<
                    typename Seq::seq_
                  , typename Seq::pred_
                  >
                , end_t<typename Seq::seq_>
                , typename Seq::pred_
                >
            >;
            
        template <class Seq>
        using end =
          identity<
              filter_view_iterator<
                  end_t<typename Seq::seq_>
                , end_t<typename Seq::seq_>
                , typename Seq::pred_
                >
            >;
        
        
        template <class Seq>
        using front = 
          mp::deref<
              typename begin<Seq>::type
            >;
        
      };
      
      
      struct filter_view_iterator_intrinsics
      {
        template <class It>
        using deref = mp::deref<typename It::it_>;
        
        template <class It>
        using next = 
          identity<
            filter_view_iterator<
                find_if_t<
                  iterator_range<next_t<typename It::it_>, typename It::end_>
                , typename It::pred_
                >
              , typename It::end_
              , typename It::pred_
              >
            >;
            
        template <class It, class N>
        using advance = forward_iterator_intrinsics::advance<It, N>;
        
        template <class It, std::size_t N>
        using advance_c = forward_iterator_intrinsics::advance_c<It, N>;
        
        template <class First, class Last>
        using distance = forward_iterator_intrinsics::distance<First, Last>;
      };
      
    }                                                       // namespace detail
    
    
    template <class Seq, class Pred>
    struct get_impl< filter_view<Seq, Pred> >
    {
      using type = detail::filter_view_intrinsics;
    };
    
    
    template <class It, class End, class Pred>
    struct get_impl< filter_view_iterator<It, End, Pred> >
    {
      using type = detail::filter_view_iterator_intrinsics;
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_FILTER_VIEW_HPP */