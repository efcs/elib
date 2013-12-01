#ifndef ELIB_MP_ITERATOR_FWD_HPP
#define ELIB_MP_ITERATOR_FWD_HPP

# include <elib/mp/iterator_tags.hpp>

namespace elib 
{
  namespace mp
  {
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            Iterator  Metafunctions                                          
  ////////////////////////////////////////////////////////////////////////////////
    
  //-------------------------------- advance ------------------------------// 
    
    namespace detail
    {
      template <class Tag> struct advance_impl;
    }                                                       // namespace detail
    
    template <class Iter, class N> struct advance;
    
  //-------------------------------- distance -----------------------------//
    
    namespace detail
    {
      template <class Tag> struct distance_impl;
    }                                                       // namespace detail
    
    template <class First, class Last> struct distance;
  
  //-------------------------------- next ---------------------------------// 
    
    template <class Iter> struct next;
  
  //-------------------------------- prior --------------------------------// 
    
    template <class Iter> struct prior;
    
  //-------------------------------- deref --------------------------------// 
    
    template <class Iter> struct deref;
    
  //-------------------------------- iterator_category --------------------// 
  
    template <class Iter> struct iterator_category;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_FWD_HPP */