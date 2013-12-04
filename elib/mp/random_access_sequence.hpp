#ifndef ELIB_MP_RANDOM_ACCESS_SEQUENCE_HPP
#define ELIB_MP_RANDOM_ACCESS_SEQUENCE_HPP

namespace elib 
{
  namespace mp
  {
    
    struct random_access_sequence
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
      
      template <class Seq>
      struct back;
      
      template <class Seq, class N>
      struct at;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_RANDOM_ACCESS_SEQUENCE_HPP */