#ifndef ELIB_MP_SEQUENCE_SEQUENCE_FWD_HPP
#define ELIB_MP_SEQUENCE_SEQUENCE_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
  
////////////////////////////////////////////////////////////////////////////////
//                            Sequence Classes                                              
////////////////////////////////////////////////////////////////////////////////

  //-------------------------------- vector --------------------------------// 

    template <class ...Args>
    struct vector;
    
    template <class T, T ...Values>
    struct vector_c;
    
    namespace detail
    {
      struct vector_tag {};
      struct vector_iter_tag {};
    }                                                       // namespace detail
    
  //-------------------------------- deque --------------------------------// 
    
    template <class ...Args>
    using deque = vector<Args...>;
    
  //-------------------------------- list --------------------------------// 
    
    template <class ...Args>
    struct list;
    
    template <class T, T ...Values>
    struct list_c;
    
    namespace detail
    {
      struct list_tag {};
      struct list_iter_tag {};
    }                                                       // namespace detail
  
  
  //-------------------------------- set --------------------------------// 
    
    template <class ...Args>
    struct set;
    
    template <class T, T ...Values>
    struct set_c;
    
    namespace detail
    {
      struct set_tag {};
      struct set_iter_tag {};
    }                                                       // namespace detail
  
  //-------------------------------- map --------------------------------// 
    template <class ...Args>
    struct map;
    
    namespace detail
    {
      struct map_tag {};
      struct map_iter_tag {};
    }                                                       // namespace detail
  
  //-------------------------------- range_c --------------------------------// 
    
    template <class T, T Start, T Finish>
    struct range_c;
    
    namespace detail
    {
      struct range_c_tag {};
      struct range_c_iter_tag {};
    }                                                       // namespace detail
    
    
////////////////////////////////////////////////////////////////////////////////
//                            Sequence Metafunctions                                              
////////////////////////////////////////////////////////////////////////////////
  
   
  //-------------------------------- sequence_tag ---------------------------//
  
    namespace detail
    {
      struct non_seq_tag {};
      struct nested_begin_tag {};
    }
    
    template <class T>
    struct sequence_tag;
    
    template <class T>
    using sequence_tag_t = typename sequence_tag<T>::type;
    
  //-------------------------------- at --------------------------------//
  
    namespace detail
    {
      template <class Tag>
      struct at_impl;
    }                                                       // namespace detail
  
    template <class Seq, class N>
    struct at 
      : detail::at_impl<sequence_tag_t<Seq>>
          ::template apply<Seq, N>
    {};
    
    template <class Seq, class N>
    using at_t = typename at<Seq, N>::type;
    
  //-------------------------------- at_c --------------------------------//
  
    namespace detail
    {
      template <class Tag>
      struct at_c_impl;
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
      template <class Tag>
      struct back_impl;
    }                                                       // namespace detail
  
    template <class Seq>
    struct back
      : detail::back_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq>
    {};
    
    template <class Seq>
    using back_t = typename back<Seq>::type;
  
  
  //-------------------------------- begin --------------------------------// 
  
    namespace detail
    {
      template <class Tag>
      struct begin_impl;
    }                                                       // namespace detail
  
    template <class T>
    struct begin
      : detail::begin_impl<sequence_tag_t<T>> 
          ::template apply<T>
    {};
    
    template <class T>
    using begin_t = typename begin<T>::type;
  
  //-------------------------------- clear --------------------------------// 
  
    namespace detail
    {
      template <class Tag>
      struct clear_impl;
    }                                                       // namespace detail
  
    template <class Seq>
    struct clear
      : detail::clear_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq>
    {};
    
    template <class Seq>
    using clear_t = typename clear<Seq>::type;
  
  //-------------------------------- empty --------------------------------// 
  
    namespace detail
    {
      template <class Tag>
      struct empty_impl;
    }                                                       // namespace detail
  
    template <class Seq>
    struct empty
      : detail::empty_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq>
    {};
    
    template <class Seq>
    using empty_t = typename empty<Seq>::type;
  
  //-------------------------------- end --------------------------------// 
  
    namespace detail
    {
      template <class Tag>
      struct end_impl;
    }                                                       // namespace detail
  
    template <class T>
    struct end
      : detail::end_impl<sequence_tag_t<T>> 
          ::template apply<T>
    {};
    
    template <class T>
    using end_t = typename end<T>::type;
  
  //-------------------------------- erase --------------------------------//
    
    namespace detail
    {
      template <class Tag>
      struct erase_impl;
    }                                                       // namespace detail
    
    template <class Seq, class First, class Last = typename First::next>
    struct erase
      : detail::erase_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, First, Last>
    {};
    
    template <class Seq, class First, class Last = typename First::next>
    using erase_t = typename erase<Seq, First, Last>::type;
  
  //-------------------------------- erase_key ------------------------------//
  
    namespace detail
    {
      template <class Tag>
      struct erase_key_impl;
    }                                                       // namespace detail
  
    template <class AssocSeq, class Key>
    struct erase_key
      : detail::erase_key_impl<sequence_tag_t<AssocSeq>>
          ::template apply<AssocSeq, Key>
    {};
    
    template <class AssocSeq, class Key>
    using erase_key_t = typename erase_key<AssocSeq, Key>::type;
  
  //-------------------------------- front --------------------------------// 
  
    namespace detail
    {
      template <class Tag>
      struct front_impl;
    }                                                       // namespace detail
  
    template <class Seq>
    struct front
      : detail::front_impl<sequence_tag_t<Seq>>
          ::template apply<Seq>
    {};
    
    template <class Seq>
    using front_t = typename front<Seq>::type;
  
  //-------------------------------- has_key --------------------------------//
  
    namespace detail
    {
      template <class Tag>
      struct has_key_impl;
    }                                                       // namespace detail
  
    template <class Seq, class Key>
    struct has_key
      : detail::has_key_impl<sequence_tag_t<Seq>>
          ::template apply<Seq, Key>
    {};
    
    template <class Seq, class Key>
    using has_key_t = typename has_key<Seq, Key>::type;
    
  //-------------------------------- insert --------------------------------// 
    
    namespace detail
    {
      template <class Tag>
      struct insert_impl;
    }                                                       // namespace detail
    
    template <class Seq, class Pos, class T>
    struct insert
      : detail::insert_impl<sequence_tag_t<Seq>>
          ::template apply<Seq, Pos, T>
    {};
    
    template <class Seq, class Pos, class T>
    using insert_t = typename insert<Seq, Pos, T>::type;
  
  //-------------------------------- insert_range ---------------------------// 
    
    namespace detail
    {
      template <class Tag>
      struct insert_range_impl;
    }                                                       // namespace detail
    
    template <class Seq, class Pos, class Range>
    struct insert_range
      : detail::insert_range_impl<sequence_tag_t<Seq>>
          ::template apply<Seq, Pos, Range>
    {};
    
    template <class Seq, class Pos, class Range>
    using insert_range_t = typename insert_range<Seq, Pos, Range>::type;
  
  //-------------------------------- is_sequence ----------------------------// 
  
    namespace detail
    {
      template <class Tag>
      struct is_sequence_impl;
    }                                                       // namespace detail
    
    template <class T>
    struct is_sequence
      : detail::is_sequence_impl<sequence_tag_t<T>> 
          ::template apply<T>
    {};
    
    template <class T>
    using is_sequence_t = typename is_sequence<T>::type;
    
  //-------------------------------- key_type -------------------------------//
  
    namespace detail
    {
      template <class Tag>
      struct key_type_impl;
    }                                                       // namespace detail
  
    template <class Seq, class T>
    struct key_type
      : detail::key_type_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, T>
    {};
    
    template <class Seq, class T>
    using key_type_t = typename key_type<Seq, T>::type;
  
  //-------------------------------- order --------------------------------// 
  
    namespace detail
    {
      template <class Tag>
      struct order_impl;
    }                                                       // namespace detail
  
    template <class Seq, class Key>
    struct order
      : detail::order_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, Key>
    {};
    
    template <class Seq, class Key>
    using order_t = typename order<Seq, Key>::type;
  
  //-------------------------------- pop_back -------------------------------// 
    
    namespace detail
    {
      template <class Tag>
      struct pop_back_impl;
    }                                                       // namespace detail
    
    template <class Seq>
    struct pop_back
      : detail::pop_back_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq>
    {};
    
    template <class Seq>
    using pop_back_t = typename pop_back<Seq>::type;
  
  //-------------------------------- pop_front ------------------------------// 
  
    namespace detail
    {
      template <class Tag>
      struct pop_front_impl;
    }                                                       // namespace detail
  
    template <class Seq>
    struct pop_front
      : detail::pop_front_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq>
    {};
    
    template <class Seq>
    using pop_front_t = typename pop_front<Seq>::type;
  
  //-------------------------------- push_back ------------------------------// 
    
    namespace detail
    {
      template <class Tag>
      struct push_back_impl;
      
      template <class Tag>
      struct has_push_back_impl;
    }                                                       // namespace detail
  
    template <class Seq, class T>
    struct push_back
      : detail::push_back_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, T>
    {};
    
    template <class Seq>
    struct has_push_back 
      : detail::has_push_back_impl<sequence_tag_t<Seq>>
          ::template apply<Seq>
    {};
        
    
    template <class Seq, class T>
    using push_back_t = typename push_back<Seq, T>::type;
    
    template <class Seq>
    using has_push_back_t = typename has_push_back<Seq>::type;
  
  //-------------------------------- push_front -----------------------------//
    
    namespace detail
    {
      template <class Tag>
      struct push_front_impl;
      
      template <class Tag>
      struct has_push_front_impl;
    }                                                       // namespace detail
  
    template <class Seq, class T>
    struct push_front
      : detail::push_front_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, T>
    {};
    
    template <class Seq>
    struct has_push_front
      : detail::has_push_front_impl<sequence_tag_t<Seq>>
          ::template apply<Seq>
    {};
    
    template <class Seq, class T>
    using push_front_t = typename push_front<Seq, T>::type;
    
    template <class Seq, class T>
    using has_push_front_t = typename has_push_front<Seq>::type;
  
  //-------------------------------- size --------------------------------// 
    
    namespace detail
    {
      template <class Tag>
      struct size_impl;
    }                                                       // namespace detail
    
    template <class T>
    struct size
      : detail::size_impl<sequence_tag_t<T>> 
          ::template apply<T>
    {};
    
    template <class T>
    using size_t = typename size<T>::type;
    
  //-------------------------------- nested_size ----------------------------// 
    
    namespace detail
    {
      template <class Tag> struct nested_size_impl;
    }
    
    template <class T>
    struct nested_size 
      : detail::nested_size_impl<sequence_tag_t<T>>
          ::template apply<T>
    {};
    
    template <class T>
    using nested_size_t = typename nested_size<T>::type;
    
  //-------------------------------- value_type -----------------------------// 
    
    namespace detail
    {
      template <class Tag>
      struct value_type_impl;
    }                                                       // namespace detail
    
    template <class Seq, class T>
    struct value_type
      : detail::value_type_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, T>
    {};
    
    template <class Seq, class T>
    using value_type_t = typename value_type<Seq, T>::type;
    
    
////////////////////////////////////////////////////////////////////////////////
//                            Adapters & Views                                              
////////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- empty_sequence -------------------------// 
    
    struct empty_sequence;
  
  //-------------------------------- filter_view ----------------------------//
  
    template <class Seq, class Pred>
    struct filter_view;
  
  //-------------------------------- iterator_range -------------------------//
  
    template <class First, class Last>
    struct iterator_range;
    
  //-------------------------------- joint_view -----------------------------//
  
    template <class FirstSeq, class LastSeq>
    struct joint_view;
  
  //-------------------------------- single_view ----------------------------//
  
    template <class T>
    struct single_view;
  
  //-------------------------------- transform_view -------------------------//
  
    template <class Seq, class F>
    struct transform_view;
  
  //-------------------------------- zip_view -------------------------------//
  
    template <class Sequences>
    struct zip_view;
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_SEQUENCE_FWD_HPP */