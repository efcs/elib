#ifndef ELIB_MP_SEQUENCE_RANGE_C_HPP
#define ELIB_MP_SEQUENCE_RANGE_C_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/size.hpp>
# include <elib/mp/iterator/iterator_fwd.hpp>
# include <elib/mp/iterator/iterator_tags.hpp>
# include <elib/mp/iterator/deref.hpp>
# include <elib/mp/metafunction/logical.hpp>
# include <elib/mp/metafunction/arithmetic.hpp>
# include <elib/mp/metafunction/increment.hpp>
# include <elib/mp/metafunction/decrement.hpp>
# include <elib/mp/metafunction/intc_cast.hpp>
# include <elib/mp/types/long.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
    //-------------------------------- range_c tags -------------------------// 
      struct range_c_tag {};
      struct range_c_iter_tag {};
    }                                                       // namespace detail
    
  //////////////////////////////////////////////////////////////////////////////
  //                            Range Iterator                                              
  //////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
    //-------------------------------- range_iter ---------------------------// 
      
      template <class IntC>
      struct range_iter
      {
        using type = IntC;
        using tag = range_c_iter_tag;
        using category = random_access_iterator_tag;
      };
      
    }                                                       // namespace detail
    
  //-------------------------------- next ------------------------------------// 
    
    template <class IntC>
    struct next< detail::range_iter<IntC> >
    {
      using type = detail::range_iter< increment_t<IntC> >;
    };
    
  //-------------------------------- prior --------------------------------// 
  
    template <class IntC>
    struct prior< detail::range_iter<IntC> >
    {
      using type = detail::range_iter< decrement_t<IntC> >;
    };
    
    
    namespace detail 
    {
    //-------------------------------- advance_impl -------------------------//
      
      template <>
      struct advance_impl< range_c_iter_tag >
      {
        template <class Iter, class N>
        struct apply
        {
          using item_ = deref_t<Iter>;
          using result_ = add_t<item_, N>;
          using type = intc_cast_t<result_, typename item_::value_type>;
        };
      };
    
    //-------------------------------- distance_impl ------------------------//
    
      template <>
      struct distance_impl< range_c_iter_tag >
      {
        template <class First, class Last>
        struct apply
        {
          using first_ = deref_t<First>;
          using last_ = deref_t<Last>;
          using result_ = subtract_t<last_, first_>;
          using type = intc_cast_t<result_, long>;
        };
      };
      
    }                                                       // namespace detail
      
    
    
  //////////////////////////////////////////////////////////////////////////////
  //                            Range_C                                              
  //////////////////////////////////////////////////////////////////////////////
    
    
    template <class T, T Start, T Finish>
    struct range_c 
    {
      using type = range_c;
      using tag = detail::range_c_tag;
      
      using start = std::integral_constant<T, Start>;
      using finish = std::integral_constant<T, Finish>;
      
      using begin = detail::range_iter<start>;
      using end = detail::range_iter<finish>;
    };
    
  //////////////////////////////////////////////////////////////////////////////
  //                      Range_C Intrinsic Metafunctions                                              
  //////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
    //-------------------------------- size ---------------------------------//
      template <>
      struct size_impl< range_c_tag >
      {
        template <class Range>
        struct apply 
          : long_<Range::finish::value - Range::start::value>
        {};
      };
    //-------------------------------- nested_size --------------------------//
      template <>
      struct nested_size_impl<range_c_tag>
      {
        template <class Range>
        struct apply
          : size_impl<range_c_tag> ::template apply<Range>
        {};
      };
    
    //-------------------------------- empty --------------------------------//
    
      template <>
      struct empty_impl<range_c_tag>
      {
        template <class Range>
        struct apply : not_< size<Range> >
        {};
      };
    
    //-------------------------------- front --------------------------------//
    
      template <>
      struct front_impl<range_c_tag>
      {
        template <class Range>
        struct apply
        { using type = typename Range::start; };
      };
    
    //-------------------------------- back ---------------------------------//
      
      template <>
      struct back_impl<range_c_tag>
      {
        template <class Range>  
        struct apply
        { using type = decrement_t<typename Range::finish>; };
      };
    
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_RANGE_C_HPP */