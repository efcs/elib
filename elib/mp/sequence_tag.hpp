#ifndef ELIB_MP_SEQUENCE_TAG_HPP
# define ELIB_MP_SEQUENCE_TAG_HPP

# include <elib/mp/config.hpp>


namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      struct no_seq_tag {};
      
    //-------------------------------- has_tag_impl -----------------------// 
      
      template <class T>
      struct has_tag_impl
      {
      private:
        
        template <class U>
        static true_ test(typename U::tag*);
        
        template <class U>
        static false_ test(...);
        
      public:
        using type = decltype( test<T>(0) );
      };                                                    // has_tag_impl
      
    //-------------------------------- has_tag ----------------------------// 
      
      template <class T>
      struct has_tag : has_tag_impl<T>::type
      {};
      
      //--------------------------- sequence_tag_impl ------------------------// 
      
      
      template <bool HasTag, class T>
      struct sequence_tag_impl
      {
        using type = no_seq_tag;
        
        static_assert(!HasTag, "Must not have a tag");
      };
      
      template <class T>
      struct sequence_tag_impl<true, T>
      {
        using type = typename T::tag;
      };
      
    }                                                       // namespace detail
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            sequence_tag                                              
  ////////////////////////////////////////////////////////////////////////////////
  
    template <class T>
    struct sequence_tag 
      : detail::sequence_tag_impl<
          detail::has_tag<T>::value
          , T
        >
    {};
    
    template <class T>
    using sequence_tag_t = typename sequence_tag<T>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_TAG_HPP */