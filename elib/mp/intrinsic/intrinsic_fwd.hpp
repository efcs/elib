#ifndef ELIB_MP_INTRINSIC_INTRINSIC_FWD_HPP
#define ELIB_MP_INTRINSIC_INTRINSIC_FWD_HPP

namespace elib 
{
  namespace mp
  {
  //-------------------------------- sequence_tag ---------------------------//
    
    template <class T>
    struct sequence_tag;
    
  //-------------------------------- at --------------------------------//
  
    namespace detail
    {
      template <class Tag> struct at_impl;
    }                                                       // namespace detail
  
    template <class Seq, class N> struct at;
    
  //-------------------------------- at_c --------------------------------//
  
    namespace detail
    {
      template <class Tag> struct at_c_impl;
    }                                                       // namespace detail
  
    template <class Seq, long N> struct at_c;
  
  //-------------------------------- back --------------------------------//
  
    namespace detail
    {
      template <class Tag> struct back_impl;
    }                                                       // namespace detail
  
    template <class Seq> struct back;
   
  //-------------------------------- begin --------------------------------// 
  
    namespace detail
    {
      template <class Tag> struct begin_impl;
    }                                                       // namespace detail
  
    template <class T> struct begin;
  
  //-------------------------------- clear --------------------------------// 
  
    namespace detail
    {
      template <class Tag> struct clear_impl;
    }                                                       // namespace detail
  
    template <class Seq> struct clear;
  
  //-------------------------------- empty --------------------------------// 
  
    namespace detail
    {
      template <class Tag> struct empty_impl;
    }                                                       // namespace detail
  
    template <class Seq> struct empty;
  
  //-------------------------------- end --------------------------------// 
  
    namespace detail
    {
      template <class Tag> struct end_impl;
    }                                                       // namespace detail
  
    template <class T> struct end;
  
  //-------------------------------- erase --------------------------------//
    
    namespace detail
    {
      template <class Tag> struct erase_impl;
    }                                                       // namespace detail
    
    template <class Seq, class First, class Last> struct erase;
    
  //-------------------------------- erase_key ------------------------------//
  
    namespace detail
    {
      template <class Tag> struct erase_key_impl;
    }                                                       // namespace detail
  
    template <class AssocSeq, class Key> struct erase_key;
  
  //-------------------------------- front --------------------------------// 
  
    namespace detail
    {
      template <class Tag> struct front_impl;
    }                                                       // namespace detail
  
    template <class Seq> struct front;
  
  //-------------------------------- has_key --------------------------------//
  
    namespace detail
    {
      template <class Tag> struct has_key_impl;
    }                                                       // namespace detail
  
    template <class Seq, class Key> struct has_key;
    
  //-------------------------------- insert --------------------------------// 
    
    namespace detail
    {
      template <class Tag> struct insert_impl;
    }                                                       // namespace detail
    
    template <class Seq, class Pos, class T> struct insert;
     
  //-------------------------------- insert_range ---------------------------// 
    
    namespace detail
    {
      template <class Tag> struct insert_range_impl;
    }                                                       // namespace detail
    
    template <class Seq, class Pos, class Range> struct insert_range;
  
  //-------------------------------- is_sequence ----------------------------// 
  
    namespace detail
    {
      template <class Tag> struct is_sequence_impl;
    }                                                       // namespace detail
    
    template <class T> struct is_sequence;
    
  //-------------------------------- key_type -------------------------------//
  
    namespace detail
    {
      template <class Tag> struct key_type_impl;
    }                                                       // namespace detail
  
    template <class Seq, class T> struct key_type;
  
  //-------------------------------- order --------------------------------// 
  
    namespace detail
    {
      template <class Tag> struct order_impl;
    }                                                       // namespace detail
  
    template <class Seq, class Key> struct order;
    
  //-------------------------------- pop_back -------------------------------// 
    
    namespace detail
    {
      template <class Tag> struct pop_back_impl;
    }                                                       // namespace detail
    
    template <class Seq> struct pop_back;
    
  //-------------------------------- pop_front ------------------------------// 
  
    namespace detail
    {
      template <class Tag> struct pop_front_impl;
    }                                                       // namespace detail
  
    template <class Seq> struct pop_front;
   
  //-------------------------------- push_back ------------------------------// 
    
    namespace detail
    {
      template <class Tag> struct push_back_impl;
      template <class Tag> struct has_push_back_impl;
    }                                                       // namespace detail
  
    template <class Seq, class T> struct push_back;
    template <class Seq> struct has_push_back;
        
  //-------------------------------- push_front -----------------------------//
    
    namespace detail
    {
      template <class Tag> struct push_front_impl;
      template <class Tag> struct has_push_front_impl;
    }                                                       // namespace detail
  
    template <class Seq, class T> struct push_front;
    template <class Seq> struct has_push_front;
   
  //-------------------------------- size --------------------------------// 
    
    namespace detail
    {
      template <class Tag> struct size_impl;
    }                                                       // namespace detail
    
    template <class T> struct size;
    
  //-------------------------------- nested_size ----------------------------// 
    
    namespace detail
    {
      template <class Tag> struct nested_size_impl;
    }
    
    template <class T> struct nested_size;
   
    
  //-------------------------------- value_type -----------------------------// 
    
    namespace detail
    {
      template <class Tag> struct value_type_impl;
    }                                                       // namespace detail
    
    template <class Seq, class T> struct value_type;
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTRINSIC_INTRINSIC_FWD_HPP */