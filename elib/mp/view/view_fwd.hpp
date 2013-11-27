#ifndef ELIB_MP_VIEW_VIEW_FWD_HPP
#define ELIB_MP_VIEW_VIEW_FWD_HPP

namespace elib 
{
  namespace mp
  {

  //-------------------------------- empty_sequence -------------------------// 
    
    struct empty_sequence;
  
  //-------------------------------- filter_view ----------------------------//
  
    template <class Seq, class Pred>
    struct filter_view;
  
  //-------------------------------- iterator_range -------------------------//
  
    template <class First, class Last>
    struct iterator_range;
    
  //-------------------------------- joint_view -----------------------------//
  
    template <class FirstSeq, class LastSeq>
    struct joint_view;
  
  //-------------------------------- single_view ----------------------------//
  
    template <class T>
    struct single_view;
  
  //-------------------------------- transform_view -------------------------//
  
    template <class Seq, class F>
    struct transform_view;
  
  //-------------------------------- zip_view -------------------------------//
  
    template <class Sequences>
    struct zip_view;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VIEW_VIEW_FWD_HPP */