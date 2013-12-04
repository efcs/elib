#ifndef ELIB_MP_BIDIRECTIONAL_SEQUENCE_HPP
# define ELIB_MP_BIDIRECTIONAL_SEQUENCE_HPP

namespace elib 
{
  
    struct bidirectional_sequence
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
    };
    
}                                                           // namespace elib
#endif /* ELIB_MP_BIDIRECTIONAL_SEQUENCE_HPP */