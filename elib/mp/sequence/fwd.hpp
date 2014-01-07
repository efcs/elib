#ifndef ELIB_MP_SEQUENCE_FWD_HPP
#define ELIB_MP_SEQUENCE_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace model
    {
    
      struct sequence_ {};
      
      struct variadic {};
      
      struct forward_sequence 
        : sequence_
      {};
      
      
      struct bidirectional_sequence 
        : forward_sequence 
      {};
      
      
      struct random_access_sequence 
        : bidirectional_sequence 
      {};
      
      
      struct variadic_sequence
        : random_access_sequence
      {};
      
      
      struct associative_sequence 
        : sequence_
      {};
  
      struct front_extensible_sequence
      {};
      
      
      struct back_extensible_sequence
      {};
      
      
      struct front_extensible_variadic_sequence
        : front_extensible_sequence
      {};
      
      
      struct back_extensible_variadic_sequence
        : back_extensible_sequence
      {};
      
      
      struct associative_extensible_sequence
      {};
      
    
      struct O1_size {};
    }                                                        // namespace model
    
  //----------------------------- intrinsics --------------------------------// 
  
    template <class Seq> struct begin;
    template <class Seq> struct end;
    template <class Seq> struct sequence_size;
    template <class Seq> struct empty;
    template <class Seq> struct front;
    
    template <class Seq> struct back;
    
    template <class Seq, class N> struct at;
    template <class Seq, std::size_t N> struct at_c;
    
    template <class Seq, class Key> struct has_key;
    template <class Seq, class T> struct key_type;
    template <class Seq, class Key> struct order;
    template <class Seq, class T> struct value_type;
    
    template <class Seq> struct clear;
    template <class Seq, class ...Args> struct erase;
    template <class Seq, class Pos, class T> struct insert;
    template <class Seq, class Pos, class Range> struct insert_range;
    
    template <class Seq, class T> struct push_back;
    template <class Seq> struct pop_back;
    
    template <class Seq, class T> struct push_front;
    template <class Seq> struct pop_front;
    
    template <class Seq, class Key> struct erase_key;
    
    template <class Seq, std::size_t N> struct drop;
    template <class Seq, std::size_t N> struct take;
    template <class Seq, std::size_t First, std::size_t Last> struct slice;
    template <class Left, class Right> struct join;
    template <class S, class ...Args> struct append;
    template <class S, class ...Args> struct prepend;
    
  //-------------------------------- traits --------------------------------// 
  
    template <class T> struct is_sequence;
    template <class T> struct is_variadic;
    template <class T> struct is_forward_sequence;
    template <class T> struct is_bidirectional_sequence;
    template <class T> struct is_random_access_sequence;
    template <class T> struct is_associative_sequence;
    template <class T> struct is_back_extensible_sequence;
    template <class T> struct is_front_extensible_sequence;
    template <class T> struct is_back_extensible_variadic_sequence;
    template <class T> struct is_front_extensible_variadic_sequence;
    template <class T> struct is_associative_extensible_sequence;
    template <class T> struct has_O1_size;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_FWD_HPP */