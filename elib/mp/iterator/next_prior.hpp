#ifndef ELIB_MP_ITERATOR_NEXT_PRIOR_HPP
#define ELIB_MP_ITERATOR_NEXT_PRIOR_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/iterator/iterator_fwd.hpp>

# if ELIB_MP_SEQUENTIAL_INTEGRAL_CONSTANT
#   include <elib/CXX14/type_traits.hpp>
# endif

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
    
    
# if ELIB_MP_SEQUENTIAL_INTEGRAL_CONSTANT
  //------------------------- integral_constant overloads --------------------// 

    template <class T, T Val>
    struct next< std::integral_constant<T, Val> >
    {
      using type = std::integral_constant<T, Val + 1>;
    };
    
    template <class T, T Val>
    struct prior< std::integral_constant<T, Val> >
    {
      using type = std::integral_constant<T, Val-1>;
    };

# endif 

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_NEXT_PRIOR_HPP */