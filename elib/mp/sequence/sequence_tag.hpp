#ifndef ELIB_MP_SEQUENCE_SEQUENCE_TAG_HPP
#define ELIB_MP_SEQUENCE_SEQUENCE_TAG_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/detail/has_tag.hpp>
# include <elib/mp/detail/has_begin.hpp>

# if ELIB_MP_SEQUENTIAL_INTEGRAL_CONSTANT
#   include <elib/CXX14/type_traits.hpp>
# endif

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
    
# if ELIB_MP_SEQUENTIAL_INTEGRAL_CONSTANT

    namespace detail { struct integral_constant_tag {}; }

    template <class T, T Val>
    struct sequence_tag< std::integral_constant<T, Val> >
    {
      using type = detail::integral_constant_tag;
    };

# endif
    
    template <class T>
    using sequence_tag_t = typename sequence_tag<T>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib


#endif /* ELIB_MP_SEQUENCE_SEQUENCE_TAG_HPP */