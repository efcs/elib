#ifndef ELIB_MP_SEQUENCE_HPP
#define ELIB_MP_SEQUENCE_HPP

# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    struct forward_sequence_tag {};
    struct bidirectional_sequence_tag : forward_sequence_tag {};
    struct random_access_sequence_tag : bidirectional_sequence_tag {};
    struct associative_sequence_tag {};
    
    struct front_extensible_sequence_tag {};
    struct back_extensible_sequence_tag {};
    struct variadic_extensible_sequence_tag {};
    struct associative_extensible_sequence_tag {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            FORWARD SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq>
    using begin = typename get_impl_t<Seq>::template begin<Seq>;

    template <class Seq>
    using begin_t = typename begin<Seq>::type;
    
    
    template <class Seq>
    using end = typename get_impl_t<Seq>::template end<Seq>;

    template <class Seq>
    using end_t = typename end<Seq>::type;
    
    
    template <class Seq>
    using sequence_size = typename get_impl_t<Seq>::template sequence_size<Seq>;

    template <class Seq>
    using sequence_size_t = typename sequence_size<Seq>::type;
    
    
    template <class Seq>
    using O1_size = typename get_impl_t<Seq>::template O1_size<Seq>;
    
    template <class Seq>
    using O1_size_t = typename O1_size<Seq>::type;
     
     
    template <class Seq>
    using empty = typename get_impl_t<Seq>::template empty<Seq>;

    template <class Seq>
    using empty_t = typename empty<Seq>::type;
    
        
    template <class Seq>
    using front = typename get_impl_t<Seq>::template front<Seq>;

    template <class Seq>
    using front_t = typename front<Seq>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            BIDIRECTIONAL SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
      
    template <class Seq>
    using back = typename get_impl_t<Seq>::template back<Seq>;

    template <class Seq>
    using back_t = typename back<Seq>::type;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            RANDOM ACCESS SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq, class N>
    using at = typename get_impl_t<Seq>::template at<Seq, N>;
    
    template <class Seq, class N>
    using at_t = typename at<Seq, N>::type;
    
    
    template <class Seq, std::size_t N>
    using at_c = typename get_impl_t<Seq>::template at_c<Seq, N>;
    
    template <class Seq, std::size_t N>
    using at_c_t = typename at_c<Seq, N>::type;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            ASSOCIATIVE SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
  
    template <class Seq, class Key>
    using has_key = typename get_impl_t<Seq>::template has_key<Seq, Key>;

    template <class Seq, class Key>
    using has_key_t = typename has_key<Seq, Key>::type;
    
    
    template <class Seq, class T>
    using key_type = typename get_impl_t<Seq>::template key_type<Seq, T>;

    template <class Seq, class T>
    using key_type_t = typename key_type<Seq, T>::type;
    
    
    template <class Seq, class Key>
    using order = typename get_impl_t<Seq>::template order<Seq, Key>;

    template <class Seq, class Key>
    using order_t = typename order<Seq, Key>::type;
    
      
    template <class Seq, class T>
    using value_type = typename get_impl_t<Seq>::template value_type<Seq, T>;

    template <class Seq, class T>
    using value_type_t = typename value_type<Seq, T>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            EXTENSIBLE SEQUENCE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq>
    using clear = typename get_impl_t<Seq>::template clear<Seq>;

    template <class Seq>
    using clear_t = typename clear<Seq>::type;
    
    
    template <class Seq, class ...Args>
    using erase = typename get_impl_t<Seq>::template erase<Seq, Args...>;

    template <class Seq, class ...Args>
    using erase_t = typename erase<Seq, Args...>::type;
        
    
    template <class Seq, class Pos, class T>
    using insert = typename get_impl_t<Seq>::template insert<Seq, Pos, T>;

    template <class Seq, class Pos, class T>
    using insert_t = typename insert<Seq, Pos, T>::type;
    
    
    template <class Seq, class Pos, class Range>
    using insert_range = 
      typename get_impl_t<Seq>::template insert_range<Seq, Pos, Range>;

    template <class Seq, class Pos, class Range>
    using insert_range_t = 
      typename insert_range<Seq, Pos, Range>::type;
      
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            BACK EXTENSIBLE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq, class T>
    using push_back = typename get_impl_t<Seq>::template push_back<Seq, T>;

    template <class Seq, class T>
    using push_back_t = typename push_back<Seq, T>::type;
    
    
    template <class Seq>
    using pop_back = typename get_impl_t<Seq>::template pop_back<Seq>;

    template <class Seq>
    using pop_back_t = typename pop_back<Seq>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            FRONT EXTENSIBLE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq, class T>
    using push_front = typename get_impl_t<Seq>::template push_front<Seq, T>;

    template <class Seq, class T>
    using push_front_t = typename push_front<Seq, T>::type;
    
    
    template <class Seq>
    using pop_front = typename get_impl_t<Seq>::template pop_front<Seq>;

    template <class Seq>
    using pop_front_t = typename pop_front<Seq>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            ASSOCIATIVE EXTENSIBLE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Seq, class Key>
    using erase_key = typename get_impl_t<Seq>::template erase_key<Seq, Key>;

    template <class Seq, class Key>
    using erase_key_t = typename erase_key<Seq, Key>::type;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            VARIADIC EXTENSIBLE                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class Pack, std::size_t N>
    using drop = typename get_impl_t<Pack>::template drop<Pack, N>;
    
    template <class Pack, std::size_t N>
    using drop_t = typename drop<Pack, N>::type;
    
    
    template <class Pack, std::size_t N>
    using take = typename get_impl_t<Pack>::template take<Pack, N>;
    
    template <class Pack, std::size_t N>
    using take_t = typename take<Pack, N>::type;
    
    
    template <class Pack, std::size_t First, std::size_t Last>
    using slice = typename get_impl_t<Pack>::template slice<Pack, First, Last>;
    
    template <class Pack, std::size_t First, std::size_t Second>
    using slice_t = typename slice<Pack, First, Second>::type;
    
    
    template <class Left, class Right>
    using concat = typename get_impl_t<Left>::template concat<Left, Right>;
    
    template <class Left, class Right>
    using concat_t = typename concat<Left, Right>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_HPP */