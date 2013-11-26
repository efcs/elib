#ifndef ELIB_MP_SEQUENCE_BEGIN_END_HPP
#define ELIB_MP_SEQUENCE_BEGIN_END_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/types.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
      
    //-------------------------------- has_begin_impl ------------------------// 
      
      template <class T>
      struct has_begin_impl
      {
      private:
        
        template <class U>
        static true_ test(typename U::begin*);
        
        template <class U>
        static false_ test(...);
        
      public:
        using type = decltype(test<T>(0));
      };
      
    //-------------------------------- has_begin ----------------------------// 
      
      template <class T>
      struct has_begin : has_begin_impl<T>::type
      {};
      
    //-------------------------------- begin_impl ---------------------------// 
      //TODO
      template <class Tag>
      struct begin_impl
      {
        template <class Seq>
        struct apply;
      };
      
  //-------------------------------- end_impl -------------------------------// 
    
    //TODO
    template <class Tag>
    struct end_impl
    {
      template <class Seq>
      struct apply;
    };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_BEGIN_END_HPP */