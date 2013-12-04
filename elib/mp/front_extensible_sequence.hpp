#ifndef ELIB_MP_FRONT_EXTENSIBLE_SEQUENCE_HPP
#define ELIB_MP_FRONT_EXTENSIBLE_SEQUENCE_HPP


namespace elib 
{
  namespace mp
  {
    
    struct front_extensible_sequence
    {
      
      template <class Seq, class T>
      struct push_front;
      
      template <class Seq>
      struct pop_front;
      
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_FRONT_EXTENSIBLE_SEQUENCE_HPP */