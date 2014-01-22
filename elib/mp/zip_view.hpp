#ifndef ELIB_MP_ZIP_VIEW_HPP
#define ELIB_MP_ZIP_VIEW_HPP

# include <elib/mp/arg.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/transform_view.hpp>
# include <elib/mp/get_impl.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/algorithm/min_element.hpp>
# include <elib/mp/algorithm/transform.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct zip_view_tag {};
    
    struct zip_view_model
      : model::forward_sequence
    {};
    
    
    template <class Seq>
    struct zip_view
    {
      using type = zip_view;
      
      using class_type = zip_view_tag;
      using model_type = zip_view_model;
      
      using seq_ = Seq;
    };
    
    
    template <class Iters>
    struct zip_view_iterator
    {
      using model_type = model::forward_iterator;
      
      using iters_ = Iters;
    };
    
    
    namespace detail
    {
      
      
      struct zip_view_intrinsics
      {
        
        template <class Seq>
        using sequence_size =
          mp::deref<
            min_element_t<
                transform_view< typename Seq::seq_, mp::sequence_size<_1> >
              >
            >;
        
        
        template <class Seq>
        using empty = bool_< sequence_size<Seq>::type::value == 0 >;
        
        
        template <class Seq>
        using begin = 
          identity<
              zip_view_iterator<
                unary_transform_t< typename Seq::seq_, mp::begin<_1> >
              >
            >;
          
        
        template <class Seq>
        using end = 
          identity<
              zip_view_iterator<
                  unary_transform_t< typename Seq::seq_, mp::end<_1> >
                >
            >;
        
        template <class Seq>
        using front = unary_transform< typename Seq::seq_, mp::front<_1> >;
      };                                                 // zip_view_intrinsics
      
      
      struct zip_view_iterator_intrinsics
      {
        
        template <class It>
        using deref = unary_transform< typename It::iters_, mp::deref<_1> >;
        
        
        template <class It>
        using next = 
          identity<
            zip_view_iterator<
              unary_transform_t< typename It::iters_, mp::next<_1> >
            >
          >;
        
        
        template <class It, class N>
        using advance = 
          identity<
            zip_view_iterator<
              unary_transform_t< typename It::iters_, mp::advance<_1, N> >
            >
          >;
            
        
        
        template <class It, std::size_t N>
        using advance_c = advance<It, size_type_<N>>;
        
        
        template <class First, class Last>
        using distance = 
          mp::distance< 
            front_t<typename First::iters_>
          , front_t<typename Last::iters_>
          >;
        
      };                                        // zip_view_iterator_intrinsics
      
      
    }                                                       // namespace detail
    
    
    template <class Seq>
    struct get_impl< zip_view<Seq> >
    {
      using type = detail::zip_view_intrinsics;
    };
    
    
    template <class Iters>
    struct get_impl< zip_view_iterator<Iters> >
    {
      using type = detail::zip_view_iterator_intrinsics;
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ZIP_VIEW_HPP */