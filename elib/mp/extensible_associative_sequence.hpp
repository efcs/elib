#ifndef ELIB_MP_EXTENSIBLE_ASSOCIATIVE_SEQUENCE_HPP
#define ELIB_MP_EXTENSIBLE_ASSOCIATIVE_SEQUENCE_HPP

namespace elib 
{
  namespace mp
  {
    
    struct back_extensible_sequence
      : extensible_sequence
    {
      template <class Seq, class T>
      struct push_back;
      
      template <class Seq>
      struct pop_back;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_EXTENSIBLE_ASSOCIATIVE_SEQUENCE_HPP */