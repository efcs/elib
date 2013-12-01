#ifndef ELIB_MP_NEXT_PRIOR_HPP
#define ELIB_MP_NEXT_PRIOR_HPP

# include <elib/mp/iterator_fwd.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- next -----------------------------------// 
    
    template <class Iter>
    struct next
    { using type = typename Iter::next; };
    
    
    template <class Iter>
    using next_t = typename next<Iter>::type;
      
  //-------------------------------- prior ----------------------------------// 
    
    template <class Iter>
    struct prior
    { using type = typename Iter::prior; };
    
    
    template <class Iter>
    using prior_t = typename prior<Iter>::type;
    
    
  //------------------------- integral_constant overloads --------------------// 

    template <class T, T Val>
    struct next< integral_c<T, Val> >
    {
      using type = integral_c<T, Val + 1>;
    };
    
    template <class T, T Val>
    struct prior< integral_c<T, Val> >
    {
      using type = integral_c<T, Val - 1>;
    };


  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_NEXT_PRIOR_HPP */