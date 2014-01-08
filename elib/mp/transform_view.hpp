#ifndef ELIB_MP_TRANSFORM_VIEW_HPP
#define ELIB_MP_TRANSFORM_VIEW_HPP

# include <elib/mp/apply.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/integral_constant.hpp>
# include <cstddef>


namespace elib 
{
  namespace mp
  {
   
    struct transform_view_tag {};
    
    struct transform_view_model
      : model::forward_sequence
    {};
    
   
    template <
        class Seq
      , class F
      >
    struct transform_view
    {
      using type = transform_view;
      using class_type = transform_view_tag;
      using model_type = transform_view_model;
      
      using seq_ = Seq;
      using func_ = F;
    };
    
    
    template <
        class It
      , class End
      , class F
      >
    struct transform_view_iterator
    {
      using model_type = model::forward_iterator;
      
      using it_ = It;
      using end_ = End;
      using func_ = F;
    };
    
    
    namespace detail
    {
      
      
      struct transform_view_intrinsics
      {
        
        template <class Seq>
        using sequence_size = mp::sequence_size< typename Seq::seq_ >;
        
        
        template <class Seq>
        using empty = mp::empty< typename Seq::seq_ >;
        
        
        template <class Seq>
        using begin = 
          identity< 
            transform_view_iterator< 
                begin_t<typename Seq::seq_>
              , end_t<typename Seq::seq_>
              , typename Seq::func_
              >
          >;
        
        
        template <class Seq>
        using end = 
          identity<
              transform_view_iterator<
                  end_t<typename Seq::seq_>
                , end_t<typename Seq::seq_>
                , typename Seq::func_
                >
            >;
            
            
        template <class Seq>
        using front = apply< typename Seq::func_, front_t<typename Seq::seq_> >;
        
      };                                           // transform_view_intrinsics
      
      
      struct transform_view_iterator_intrinsics
      {
        template <class It>
        using deref = apply< typename It::func_, deref_t<typename It::it_> >;
        
        template <class It>
        using next = 
          identity<
              transform_view_iterator<
                  next_t< typename It::it_ >
                , typename It::end_
                , typename It::func_
                >
            >;
        
        
        template <class It, class N>
        using advance = 
          identity<
              transform_view_iterator<
                  advance_t<typename It::it_, N>
                , typename It::end_
                , typename It::func_
                >
            >;
        
        
        template <class It, std::size_t N>
        using advance_c = advance< It, size_type<N> >;
        
        
        template <class First, class Last>
        using distance = 
          mp::distance< 
              typename First::it_
            , typename Last::it_
            >;
      };                                  // transform_view_iterator_intrinsics
      
      
    }                                                       // namespace detail
   
   
    template <class Seq, class F>
    struct get_impl< transform_view<Seq, F> >
    {
      using type = detail::transform_view_intrinsics;
    };
    
    
    template <class It, class End, class F>
    struct get_impl< transform_view_iterator<It, End, F> >
    {
      using type = detail::transform_view_iterator_intrinsics;
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TRANSFORM_VIEW_HPP */
