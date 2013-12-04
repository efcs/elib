#ifndef ELIB_MP_ASSOCIATIVE_SEQUENCE_HPP
#define ELIB_MP_ASSOCIATIVE_SEQUENCE_HPP

namespace elib 
{
  namespace mp
  {
    
    struct associative_sequence
    {
      
      template <class Seq>
      struct begin;
      
      template <class Seq>
      struct end;
      
      template <class Seq>
      struct size;
      
      template <class Seq>
      struct empty;
      
      template <class Seq>
      struct front;
      
      template <class Seq, class Key>
      struct has_key;
      
      template <class Seq, class Key>
      struct count;
      
      template <class Seq, class Key>
      struct order;
      
      template <class Seq, class Key, class Default>
      struct at;

      template <class Seq, class T>
      struct key_type;
      
      template <class Seq, class T>
      struct value_type;
      
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ASSOCIATIVE_SEQUENCE_HPP */