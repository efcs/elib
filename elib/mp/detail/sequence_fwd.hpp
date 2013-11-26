#ifndef ELIB_MP_SEQUENCE_FWD_HPP
# define ELIB_MP_SEQUENCE_FWD_HPP


namespace elib 
{
  namespace mp
  {
  
  ////////////////////////////////////////////////////////////////////////////////
  //                          Vector
  ////////////////////////////////////////////////////////////////////////////////
  
    template <class ...Args>
    struct vector;
    
    template <class T, T ...Values>
    struct vector_c;
    
    namespace detail
    {
      struct vector_tag {};
      struct vector_iter_tag {};
    }                                                       // namespace detail
    
  ////////////////////////////////////////////////////////////////////////////////
  //                                List
  ////////////////////////////////////////////////////////////////////////////////
  
    template <class ...Args>
    struct list;
    
    template <class T, T ...Values>
    struct list_c;
    
    namespace detail
    {
      struct list_tag {};
      struct list_iter_tag {};
    }                                                       // namespace detail
  
  
  ////////////////////////////////////////////////////////////////////////////////
  //                               Set                                         
  ////////////////////////////////////////////////////////////////////////////////
  
    template <class ...Args>
    struct set;
    
    template <class T, T ...Values>
    struct set_c;
    
    namespace detail
    {
      struct set_tag {};
      struct set_iter_tag {};
    }                                                       // namespace detail
  
  ////////////////////////////////////////////////////////////////////////////////
  //                            Map                                              
  ////////////////////////////////////////////////////////////////////////////////
  
    template <class ...Args>
    struct map;
    
    namespace detail
    {
      struct map_tag {};
      struct map_iter_tag {};
    }                                                       // namespace detail
  
  ////////////////////////////////////////////////////////////////////////////////
  //                            range_c                                              
  ////////////////////////////////////////////////////////////////////////////////
  
    template <class T, T Start, T Finish>
    struct range_c;
    
    namespace detail
    {
      struct range_c_tag {};
      struct range_c_iter_tag {};
    }                                                       // namespace detail
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_FWD_HPP */