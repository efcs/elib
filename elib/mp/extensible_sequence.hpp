#ifndef ELIB_MP_EXTENSIBLE_SEQUENCE_HPP
#define ELIB_MP_EXTENSIBLE_SEQUENCE_HPP

namespace elib 
{
  namespace mp
  {
    
    struct extensible_sequence
    {
      template <class Seq, class Pos, class T> 
      struct insert;
      
      template <class Seq, class Pos, class Range> 
      struct insert_range;
      
      template <class Seq, class Pos, class Last> 
      struct erase;
      
      // NOTE: unimplemented
      template <class Seq> 
      struct clear;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_EXTENSIBLE_SEQUENCE_HPP */