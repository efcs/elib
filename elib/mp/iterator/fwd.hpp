#ifndef ELIB_MP_ITERATOR_FWD_HPP
#define ELIB_MP_ITERATOR_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace model
    {
      
      struct iterator 
      {};
      
      
      struct forward_iterator
        : iterator
      {};
      
      
      struct bidirectional_iterator
        : forward_iterator
      {};
      
      
      struct random_access_iterator 
        : bidirectional_iterator
      {};
      
      /* default_random_access_iterator has a definition of
       * template <class Seq, std::size_t N> struct iterator
       */
      struct default_random_access_iterator
        : random_access_iterator
      {};
      
    }                                                       // namespace model
    
  //-------------------------------- iterator --------------------------------// 
    
    template <class Seq, std::size_t N>
    struct default_random_access_iterator;
  
  //---------------------------- intrinsics ---------------------------------// 
    
    template <class Iter> struct deref;
    template <class Iter> struct next;
    template <class Iter> struct prior;
    template <class Iter, class N> struct advance;
    template <class Iter, long N> struct advance_c;
    template <class First, class Last> struct distance;
    
    template <class Model> struct iterator_intrinsics;
    template <> struct iterator_intrinsics< model::forward_iterator >;
    template <> struct iterator_intrinsics< model::bidirectional_iterator >;
    template <> struct iterator_intrinsics< model::default_random_access_iterator >;
    
    using forward_iterator_intrinsics = 
      iterator_intrinsics< model::forward_iterator >;
    
    using bidirectional_iterator_intrinsics =
      iterator_intrinsics< model::bidirectional_iterator >;
      
    using default_random_access_iterator_intrinsics = 
      iterator_intrinsics< model::default_random_access_iterator >;
      
  //-------------------------------- dispatch --------------------------------// 
    
    template <class It> struct iterator_intrinsics_dispatch;
    
  //-------------------------------- traits --------------------------------// 
  
    template <class T> struct is_iterator;
    template <class T> struct is_forward_iterator;
    template <class T> struct is_bidirectional_iterator;
    template <class T> struct is_random_access_iterator;
    template <class T> struct is_default_random_access_iterator;
    
    template <class T> struct has_nested_item;
    template <class T> struct has_nested_next;
    template <class T> struct has_nested_prior;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_FWD_HPP */