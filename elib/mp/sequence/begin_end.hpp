#ifndef ELIB_MP_SEQUENCE_BEGIN_END_HPP
#define ELIB_MP_SEQUENCE_BEGIN_END_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/types.hpp>
# include <elib/mp/metafunction/if.hpp>

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
      
    //-------------------------------- get_begin ----------------------------// 
      
      template <class T>
      struct get_begin
      {
        using type = typename T::begin;
      };
      
    //-------------------------------- get_end ------------------------------// 
      
      template <class T>
      struct get_end
      {
        using type = typename T::end;
      };
      
    //-------------------------------- begin_impl ---------------------------// 

      template <class Tag>
      struct begin_impl
      {
        template <class Seq>
        struct apply
        {
          using type = eval_if_t<has_begin<Seq>, get_begin<Seq>, void_>;
        };
      };
      
    //-------------------------------- end_impl -------------------------------// 
    
      template <class Tag>
      struct end_impl
      {
        template <class Seq>
        struct apply
        {
          using type = eval_if_t<has_begin<Seq>, get_end<Seq>, void_>;
        };
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_BEGIN_END_HPP */