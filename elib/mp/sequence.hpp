#ifndef ELIB_MP_SEQUENCE_HPP
#define ELIB_MP_SEQUENCE_HPP

# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
   
   namespace model
   {
  //-------------------------------- concept tags ----------------------------// 
    
    struct sequence {};
    
    
    struct variadic
      : sequence
    {};
    
    
    struct forward_sequence 
      : sequence 
    {};
    
    
    struct bidirectional_sequence 
      : forward_sequence 
    {};
    
    
    struct random_access_sequence 
      : bidirectional_sequence 
    {};
    
    
    struct variadic_sequence 
      : variadic, random_access_sequence
    {};
    
    
    struct variadic_list 
      : variadic, forward_sequence 
    {};
    
    
    struct associative_sequence 
      : sequence
    {};
    
    
    struct extensible_sequence
      : forward_sequence
    {};
    
    
    struct front_extensible_sequence
      : extensible_sequence
    {};
    
    
    struct back_extensible_sequence
      : extensible_sequence
    {};
    
    
    struct front_extensible_variadic_sequence
      : variadic, front_extensible_sequence
    {};
    
    
    struct back_extensible_variadic_sequence
      : front_extensible_variadic_sequence, back_extensible_sequence
    {};
    
    
    struct associative_extensible_sequence
      : associative_sequence
    {};
    
    
  //-------------------------------- mpl concept tags -----------------------// 
    
    struct mpl_sequence {};
    
   }                                                        // namespace model
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            FORWARD SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq>
    using begin_t = typename get_impl_t<Seq>::template begin<Seq>::type;

    template <class Seq>
    struct begin : get_impl_t<Seq>::template begin<Seq>
    {};
    
    
    template <class Seq>
    using end_t = typename get_impl_t<Seq>::template end<Seq>::type;

    template <class Seq>
    struct end : get_impl_t<Seq>::template end<Seq>
    {};
    
    
    template <class Seq>
    using sequence_size_t = 
      typename get_impl_t<Seq>::template sequence_size<Seq>::type;

    template <class Seq>
    struct sequence_size : get_impl_t<Seq>::template sequence_size<Seq>
    {};
    
     
    template <class Seq>
    using empty_t = typename get_impl_t<Seq>::template empty<Seq>::type;

    template <class Seq>
    struct empty : get_impl_t<Seq>::template empty<Seq>
    {};
    
        
    template <class Seq>
    using front_t = typename get_impl_t<Seq>::template front<Seq>::type;

    template <class Seq>
    struct front : get_impl_t<Seq>::template front<Seq>
    {};
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            BIDIRECTIONAL SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
      
    template <class Seq>
    using back_t = typename get_impl_t<Seq>::template back<Seq>::type;

    template <class Seq>
    struct back : get_impl_t<Seq>::template back<Seq>
    {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            RANDOM ACCESS SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq, class N>
    using at_t = typename get_impl_t<Seq>::template at<Seq, N>::type;
    
    template <class Seq, class N>
    struct at : get_impl_t<Seq>::template at<Seq, N>
    {};
    
    
    template <class Seq, std::size_t N>
    using at_c_t = typename get_impl_t<Seq>::template at_c<Seq, N>::type;
    
    template <class Seq, std::size_t N>
    struct at_c : get_impl_t<Seq>::template at_c<Seq, N>
    {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            ASSOCIATIVE SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
  
    template <class Seq, class Key>
    using has_key_t = typename get_impl_t<Seq>::template has_key<Seq, Key>::type;

    template <class Seq, class Key>
    struct has_key : get_impl_t<Seq>::template has_key<Seq, Key>
    {};
    
    
    template <class Seq, class T>
    using key_type_t = typename get_impl_t<Seq>::template key_type<Seq, T>::type;

    template <class Seq, class T>
    struct key_type : get_impl_t<Seq>::template key_type<Seq, T>
    {};
    
    
    template <class Seq, class Key>
    using order_t = typename get_impl_t<Seq>::template order<Seq, Key>::type;

    template <class Seq, class Key>
    struct order : get_impl_t<Seq>::template order<Seq, Key>
    {};
    
      
    template <class Seq, class T>
    using value_type_t = 
      typename get_impl_t<Seq>::template value_type<Seq, T>::type;

    template <class Seq, class T>
    struct value_type : get_impl_t<Seq>::template value_type<Seq, T>
    {};
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            EXTENSIBLE SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq>
    using clear_t = typename get_impl_t<Seq>::template clear<Seq>::type;

    template <class Seq>
    struct clear : get_impl_t<Seq>::template clear<Seq>
    {};
    
    
    template <class Seq, class ...Args>
    using erase_t = 
      typename get_impl_t<Seq>::template erase<Seq, Args...>::type;

    template <class Seq, class ...Args>
    struct erase : get_impl_t<Seq>::template erase<Seq, Args...>
    {};
        
    
    template <class Seq, class Pos, class T>
    using insert_t = 
      typename get_impl_t<Seq>::template insert<Seq, Pos, T>::type;

    template <class Seq, class Pos, class T>
    struct insert : get_impl_t<Seq>::template insert<Seq, Pos, T>
    {};
    
    
    template <class Seq, class Pos, class Range>
    using insert_range_t = 
      typename get_impl_t<Seq>::template insert_range<Seq, Pos, Range>::type;

    template <class Seq, class Pos, class Range>
    struct insert_range : get_impl_t<Seq>::template insert_range<Seq, Pos, Range>
    {};
      
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            BACK EXTENSIBLE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    template <class Seq, class T>
    struct push_back : get_impl_t<Seq>::template push_back<Seq, T>
    {};
    
    template <class Seq, class T>
    using push_back_t = typename get_impl_t<Seq>::template push_back<Seq, T>::type;

    
    template <class Seq>
    struct pop_back : get_impl_t<Seq>::template pop_back<Seq>
    {};
    
    template <class Seq>
    using pop_back_t = typename get_impl_t<Seq>::template pop_back<Seq>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            FRONT EXTENSIBLE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    template <class Seq, class T>
    struct push_front : get_impl_t<Seq>::template push_front<Seq, T>
    {};
    
    template <class Seq, class T>
    using push_front_t = 
      typename get_impl_t<Seq>::template push_front<Seq, T>::type;

      
    template <class Seq>
    struct pop_front : get_impl_t<Seq>::template pop_front<Seq>
    {};
    
    template <class Seq>
    using pop_front_t = typename get_impl_t<Seq>::template pop_front<Seq>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            ASSOCIATIVE EXTENSIBLE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq, class Key>
    struct erase_key : get_impl_t<Seq>::template erase_key<Seq, Key>
    {};
    
    template <class Seq, class Key>
    using erase_key_t = 
      typename get_impl_t<Seq>::template erase_key<Seq, Key>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            VARIADIC EXTENSIBLE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    template <class Pack, std::size_t N>
    struct drop : get_impl_t<Pack>::template drop<Pack, N>
    {};
    
    template <class Pack, std::size_t N>
    using drop_t = typename get_impl_t<Pack>::template drop<Pack, N>::type;
    
    
    template <class Pack, std::size_t N>
    struct take : get_impl_t<Pack>::template take<Pack, N>
    {};
    
    template <class Pack, std::size_t N>
    using take_t = typename get_impl_t<Pack>::template take<Pack, N>::type;
    
    
    template <class Pack, std::size_t First, std::size_t Second>
    struct slice : get_impl_t<Pack>::template slice<Pack, First, Second>
    {};
    
    template <class Pack, std::size_t First, std::size_t Last>
    using slice_t = 
      typename get_impl_t<Pack>::template slice<Pack, First, Last>::type;
    
    
    template <class Left, class Right>
    struct join : get_impl_t<Left>::template join<Left, Right>
    {};
    
    template <class Left, class Right>
    using join_t = typename get_impl_t<Left>::template join<Left, Right>::type;
    
    
    template <class S, class ...Args>
    struct prepend : get_impl_t<S>::template prepend<S, Args...>
    {};
    
    template <class S, class ...Args>
    using prepend_t = typename get_impl_t<S>::template prepend<S, Args...>::type;
    
    
    template <class S, class ...Args>
    struct append : get_impl_t<S>::template append<S, Args...>
    {};
    
    template <class S, class ...Args>
    using append_t = typename get_impl_t<S>::template append<S, Args...>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_HPP */