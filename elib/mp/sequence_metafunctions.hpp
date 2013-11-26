#ifndef ELIB_MP_SEQUENCE_METAFUNCTIONS_HPP
#define ELIB_MP_SEQUENCE_METAFUNCTIONS_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>
# include <elib/mp/sequence_tag.hpp>
# include <elib/mp/detail/sequence_fwd.hpp>
# include <elib/mp/metafunctions/apply_wrap.hpp>

# include <elib/CXX14/type_traits.hpp>
# include <cstddef>

namespace elib
{
  namespace mp
  {
    
  //-------------------------------- at --------------------------------//
  
    namespace detail
    {
      template <class SeqTag>
      struct at_impl
      {
        template <class Seq, class N>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq, class N>
    struct at 
      : apply_wrap<
          detail::at_impl<sequence_tag_t<Seq>>
          , Seq, N
        >
    {};
    
    template <class Seq, class N>
    using at_t = typename at<Seq, N>::type;
    
  //-------------------------------- at_c --------------------------------//
  
    namespace detail
    {
      template <class SeqTag>
      struct at_c_impl
      {
        template <class Seq, std::size_t N>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq, std::size_t N>
    struct at_c 
      : detail::at_c_impl<sequence_tag_t<Seq>>
        ::template apply<Seq, N>
    {};
    
    template <class Seq, std::size_t N>
    using at_c_t = typename at_c<Seq, N>::type;
  
  //-------------------------------- back --------------------------------//
  
    namespace detail
    {
      template <class SeqTag>
      struct back_impl
      {
        template <class Seq>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq>
    struct back
      : apply_wrap<
          detail::back_impl<sequence_tag_t<Seq>>
          , Seq
        >
    {};
    
    template <class Seq>
    using back_t = typename back<Seq>::type;
  
  
  //-------------------------------- begin --------------------------------// 
  
    namespace detail
    {
      template <class SeqTag>
      struct begin_impl
      {
        template <class T>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class T>
    struct begin
      : apply_wrap<
          detail::begin_impl<sequence_tag_t<T>>
          , T
        >
    {};
    
    template <class T>
    using begin_t = typename begin<T>::type;
  
  //-------------------------------- clear --------------------------------// 
  
    namespace detail
    {
      template <class SeqTag>
      struct clear_impl
      {
        template <class Seq>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq>
    struct clear
      : apply_wrap<
          detail::clear_impl<sequence_tag_t<Seq>>
          , Seq
        >
    {};
    
    template <class Seq>
    using clear_t = typename clear<Seq>::type;
  
  //-------------------------------- empty --------------------------------// 
  
    namespace detail
    {
      template <class SeqTag>
      struct empty_impl
      {
        template <class Seq>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq>
    struct empty
      : apply_wrap<
          detail::empty_impl<sequence_tag_t<Seq>>
          , Seq
        >
    {};
    
    template <class Seq>
    using empty_t = typename empty<Seq>::type;
  
  //-------------------------------- end --------------------------------// 
  
    namespace detail
    {
      template <class SeqTag>
      struct end_impl
      {
        template <class T>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class T>
    struct end
      : apply_wrap<
          detail::end_impl<sequence_tag_t<T>>
          , T
        >
    {};
    
    template <class T>
    using end_t = typename end<T>::type;
  
  //-------------------------------- erase --------------------------------//
    
    namespace detail
    {
      template <class SeqTag>
      struct erase_impl
      {
        template <class Seq, class First, class Last>
        struct apply;
      };
    }                                                       // namespace detail
    
    //TODO void_? 
    template <class Seq, class First, class Last = void_>
    struct erase
      : apply_wrap<
          detail::erase_impl<sequence_tag_t<Seq>>
          , Seq, First, Last
        >
    {};
    
    template <class Seq, class First, class Last = void_>
    using erase_t = typename erase<Seq, First, Last>::type;
  
  //-------------------------------- erase_key ------------------------------//
  
    namespace detail
    {
      template <class SeqTag>
      struct erase_key_impl
      {
        template <class AssocSeq, class Key>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class AssocSeq, class Key>
    struct erase_key
      : apply_wrap<
          detail::erase_key_impl<sequence_tag_t<AssocSeq>>
          , AssocSeq, Key
        >
    {};
    
    template <class AssocSeq, class Key>
    using erase_key_t = typename erase_key<AssocSeq, Key>::type;
  
  //-------------------------------- front --------------------------------// 
  
    namespace detail
    {
      template <class SeqTag>
      struct front_impl
      {
        template <class Seq>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq>
    struct front
      : apply_wrap<
          detail::front_impl<sequence_tag_t<Seq>>
          , Seq
        >
    {};
    
    template <class Seq>
    using front_t = typename front<Seq>::type;
  
  //-------------------------------- has_key --------------------------------//
  
    namespace detail
    {
      template <class SeqTag>
      struct has_key_impl
      {
        template <class Seq, class Key>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq, class Key>
    struct has_key
      : apply_wrap<
          detail::has_key_impl<sequence_tag_t<Seq>>
          , Seq, Key
        >
    {};
    
    template <class Seq, class Key>
    using has_key_t = typename has_key<Seq, Key>::type;
    
  //-------------------------------- insert --------------------------------// 
    
    namespace detail
    {
      template <class SeqTag>
      struct insert_impl
      {
        template <class Seq, class Pos, class T>
        struct apply;
      };
    }                                                       // namespace detail
    
    template <class Seq, class Pos, class T>
    struct insert
      : apply_wrap<
          detail::insert_impl<sequence_tag_t<Seq>>
          , Seq, Pos, T
        >
    {};
    
    template <class Seq, class Pos, class T>
    using insert_t = typename insert<Seq, Pos, T>::type;
  
  //-------------------------------- insert_range ---------------------------// 
    
    namespace detail
    {
      template <class SeqTag>
      struct insert_range_impl
      {
        template <class Seq, class Pos, class Range>
        struct apply;
      };
    }                                                       // namespace detail
    
    template <class Seq, class Pos, class Range>
    struct insert_range
      : apply_wrap<
          detail::insert_range_impl<sequence_tag_t<Seq>>
          , Seq, Pos, Range
        >
    {};
    
    template <class Seq, class Pos, class Range>
    using insert_range_t = typename insert_range<Seq, Pos, Range>::type;
  
  //-------------------------------- is_sequence ----------------------------// 
  
    namespace detail
    {
      template <class SeqTag>
      struct is_sequence_impl
      {
        template <class T>
        struct apply;
      };
    }                                                       // namespace detail
    
    template <class T>
    struct is_sequence
      : apply_wrap<
          detail::is_sequence_impl<sequence_tag_t<T>>
          , T
        >
    {};
    
    template <class T>
    using is_sequence_t = typename is_sequence<T>::type;
    
  //-------------------------------- key_type -------------------------------//
  
    namespace detail
    {
      template <class SeqTag>
      struct key_type_impl
      {
        template <class Seq, class T>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq, class T>
    struct key_type
      : apply_wrap<
          detail::key_type_impl<sequence_tag_t<Seq>>
          , Seq, T
        >
    {};
    
    template <class Seq, class T>
    using key_type_t = typename key_type<Seq, T>::type;
  
  //-------------------------------- order --------------------------------// 
  
    namespace detail
    {
      template <class SeqTag>
      struct order_impl
      {
        template <class Seq, class Key>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq, class Key>
    struct order
      : apply_wrap<
          detail::order_impl<sequence_tag_t<Seq>>
          , Seq, Key
        >
    {};
    
    template <class Seq, class Key>
    using order_t = typename order<Seq, Key>::type;
  
  //-------------------------------- pop_back -------------------------------// 
    
    namespace detail
    {
      template <class SeqTag>
      struct pop_back_impl
      {
        template <class Seq>
        struct apply;
      };
    }                                                       // namespace detail
    
    template <class Seq>
    struct pop_back
      : apply_wrap<
          detail::pop_back_impl<sequence_tag_t<Seq>>
          , Seq
        >
    {};
    
    template <class Seq>
    using pop_back_t = typename pop_back<Seq>::type;
  
  //-------------------------------- pop_front ------------------------------// 
  
    namespace detail
    {
      template <class SeqTag>
      struct pop_front_impl
      {
        template <class Seq>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq>
    struct pop_front
      : apply_wrap<
          detail::pop_front_impl<sequence_tag_t<Seq>>
          , Seq
        >
    {};
    
    template <class Seq>
    using pop_front_t = typename pop_front<Seq>::type;
  
  //-------------------------------- push_back ------------------------------// 
    
    namespace detail
    {
      template <class SeqTag>
      struct push_back_impl
      {
        template <class Seq, class T>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq, class T>
    struct push_back
      : apply_wrap<
          detail::push_back_impl<sequence_tag_t<Seq>>
          , Seq, T
        >
    {};
    
    template <class Seq, class T>
    using push_back_t = typename push_back<Seq, T>::type;
  
  //-------------------------------- push_front -----------------------------//
    
    namespace detail
    {
      template <class SeqTag>
      struct push_front_impl
      {
        template <class Seq, class T>
        struct apply;
      };
    }                                                       // namespace detail
  
    template <class Seq, class T>
    struct push_front
      : apply_wrap<
          detail::push_front_impl<sequence_tag_t<Seq>>
          , Seq, T
        >
    {};
    
    template <class Seq, class T>
    using push_front_t = typename push_front<Seq, T>::type;
  
  //-------------------------------- size --------------------------------// 
    
    namespace detail
    {
      template <class SeqTag>
      struct size_impl
      {
        template <class> 
        struct apply;
      };
    }                                                       // namespace detail
    
    template <class T>
    struct size
      : apply_wrap<
          detail::size_impl<sequence_tag_t<T>>
          , T
        >
    {};
    
    template <class T>
    using size_t = typename size<T>::type;
    
  //-------------------------------- value_type -----------------------------// 
    
    namespace detail
    {
      template <class SeqTag>
      struct value_type_impl
      {
        template <class Seq, class T>
        struct apply;
      };
    }                                                       // namespace detail
    
    template <class Seq, class T>
    struct value_type
      : apply_wrap<
          detail::value_type_impl<sequence_tag_t<Seq>>
          , Seq, T
        >
    {};
    
    template <class Seq, class T>
    using value_type_t = typename value_type<Seq, T>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_METAFUNCTIONS_HPP */