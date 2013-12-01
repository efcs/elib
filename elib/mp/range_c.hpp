#ifndef ELIB_MP_RANGE_C_HPP
#define ELIB_MP_RANGE_C_HPP

# include <elib/mp/range_c_fwd.hpp>
# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/size.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/arithmetic.hpp>
# include <elib/mp/intc_cast.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
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
      using type = detail::range_iter< next_t<IntC> >;
    };
    
  //-------------------------------- prior --------------------------------// 
  
    template <class IntC>
    struct prior< detail::range_iter<IntC> >
    {
      using type = detail::range_iter< prior_t<IntC> >;
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
          using result_ = long_< add_t<item_, N>::value >;
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
          using type = long_< subtract_t<last_, first_>::value >;
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
      
      using start = integral_c<T, Start>;
      using finish = integral_c<T, Finish>;
      
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
        { using type = prior_t<typename Range::finish>; };
      };
    
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_RANGE_C_HPP */