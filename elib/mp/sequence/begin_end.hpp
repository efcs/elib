#ifndef ELIB_MP_SEQUENCE_BEGIN_END_HPP
#define ELIB_MP_SEQUENCE_BEGIN_END_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/types.hpp>
# include <elib/mp/metafunction/if.hpp>
# include <elib/mp/detail/has_begin.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
      
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
      
    // partial specialization ( detail::nested_begin_tag )
    
      template <>
      struct begin_impl< detail::nested_begin_tag >
      {
        template <class Seq>
        struct apply
        {
          using type = typename Seq::begin;
        };
      };
      
    // partial specialization ( detail::non_seq_tag )
      
      template <>
      struct begin_impl< detail::non_seq_tag >
      {
        template <class Seq>
        struct apply
        {
          using type = void_;
        };
      };
      
    // partial specialization ( na )
      
      template <>
      struct begin_impl< na >
      {
        template <class Seq>
        struct apply
        {
          using type = void_;
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
      
    // partial specialization ( detail::nested_begin_tag )
    
      template <>
      struct end_impl< detail::nested_begin_tag >
      {
        template <class Seq>
        struct apply
        {
          using type = typename Seq::end;
        };
      };
      
    // partial specialization ( detail::non_seq_tag )
      
      template <>
      struct end_impl< detail::non_seq_tag >
      {
        template <class Seq>
        struct apply
        {
          using type = void_;
        };
      };
      
    // partial specialization ( na )
      
      template <>
      struct end_impl< na >
      {
        template <class Seq>
        struct apply
        {
          using type = void_;
        };
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_BEGIN_END_HPP */