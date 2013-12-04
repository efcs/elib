#ifndef ELIB_MP_FORWARD_SEQUENCE_HPP
#define ELIB_MP_FORWARD_SEQUENCE_HPP

namespace elib 
{
  namespace mp
  {
    struct forward_sequence
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
    };
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_FORWARD_SEQUENCE_HPP */