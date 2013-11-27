#ifndef ELIB_MP_SEQUENCE_SEQUENCE_TAG_HPP
#define ELIB_MP_SEQUENCE_SEQUENCE_TAG_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/detail/has_tag.hpp>
# include <elib/mp/detail/has_begin.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
    //-------------------------------- sequence tags ------------------------// 
      struct non_seq_tag {};
      struct nested_begin_tag {};
      
    //-------------------------------- sequence_tag_impl --------------------// 
      
      template <bool HasTag, bool HasBegin, class T>
      struct sequence_tag_impl
      {
        using type = non_seq_tag;
        
        static_assert(HasTag == false && HasBegin == false,
                      "Overload Assertion Failed");
      };
      
      
      template <bool HasBegin, class T>
      struct sequence_tag_impl<true, HasBegin, T>
      {
        using type = typename T::tag;
      };
      
      
      template <class T>
      struct sequence_tag_impl<false, true, T>
      {
        using type = nested_begin_tag;
      };
      
    }                                                       // namespace detail
    
  //-------------------------------- sequence_tag ---------------------------// 
    
    template <class T>
    struct sequence_tag 
      : detail::sequence_tag_impl<
          detail::has_tag<T>::value
        , detail::has_begin<T>::value
        , T
        >
    {};
    
    template <class T>
    using sequence_tag_t = typename sequence_tag<T>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_SEQUENCE_TAG_HPP */