#ifndef ELIB_MP_SEQUENCE_ITERATOR_HPP
# define ELIB_MP_SEQUENCE_ITERATOR_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/sequence_metafunctions.hpp>
# include <elib/mp/metafunctions/apply_wrap.hpp>

namespace elib 
{
  namespace mp
  {
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            Iterator  Metafunctions                                          
  ////////////////////////////////////////////////////////////////////////////////
    
  //-------------------------------- advance ------------------------------// 
    
    namespace detail
    {
      template <class Tag>
      struct advance_impl
      {
        template <class Iter, class N>
        struct apply;
      };
    }                                                       // namespace detail
    
    template <class Iter, class N>
    struct advance 
      : apply_wrap<
          detail::advance_impl< sequence_tag_t<Iter> >
          , Iter, N
        >
    {};
          
    template <class Iter, class N>
    using advance_t = typename advance<Iter, N>::type;
    
  //-------------------------------- distance -----------------------------//
    
    namespace detail
    {
      template <class Tag>
      struct distance_impl
      {
        template <class First, class Last>
        struct apply;
      };
    }                                                       // namespace detail
    
    template <class First, class Last>
    struct distance :
      apply_wrap<
        detail::distance_impl<sequence_tag_t<First>>
        , First, Last
      >
    {};
    
    template <class First, class Last>
    using distance_t = typename distance<First, Last>::type;
  
  //-------------------------------- next ---------------------------------// 
    
  
    template <class Iter>
    struct next;
  
    template <class Iter>
    using next_t = typename next<Iter>::type;
  
  //-------------------------------- prior --------------------------------// 
    
    
    template <class Iter>
    struct prior;
    
    template <class Iter>
    using prior_t = typename prior<Iter>::type;
  
  //-------------------------------- deref --------------------------------// 
    
    template <class Iter>
    struct deref;
    
    template <class Iter>
    using deref_t = typename deref<Iter>::type;
  
  //-------------------------------- iterator_category --------------------// 
  
    struct forward_iterator_tag {};
    struct bidirectional_iterator_tag {};
    struct random_access_iterator_tag {};
  
    template <class Iter>
    struct iterator_category
    {
      using type = typename Iter::category;
    };
    
    template <class Iter>
    using iterator_category_t = typename iterator_category<Iter>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_ITERATOR_HPP */