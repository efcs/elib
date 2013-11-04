#ifndef ELIB_ETL_LOGICAL_HPP
# define ELIB_ETL_LOGICAL_HPP

# include <elib/etl/config.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace etl
  {
    
    using true_ = std::true_type;
    using false_ = std::false_type;
    
    
    template <class T>
    struct not_ 
      : std::integral_constant<typename T::value_type, !T::value>
    {};
    
    
    template <class ...Args>
    struct and_ : true_
    {
      static_assert(sizeof...(Args) == 0, 
        "specialization must be empty param pack");
    };
    
    template <class P1>
    struct and_<P1> : P1
    {};
    
    template <class P1, class P2>
    struct and_<P1, P2> 
      : std::integral_constant<bool, P1::value && P2::value>
    {};
    
    template <class P1, class P2, class P3, class ...Rest>
    struct and_<P1, P2, P3, Rest...>
      : and_<
          and_<P1, P2>, 
          and_<P3, Rest...>
        >
    { };
    
    
    
    template <class ...Args>
    struct or_ : false_
    {
      static_assert(sizeof...(Args) == 0, 
        "specialization must be empty param pack");
    };
    
    template <class P1>
    struct or_<P1> : P1
    {};
    
    template <class P1, class P2>
    struct or_<P1, P2> 
      : std::integral_constant<bool, P1::value || P2::value>
    {};
    
    template <class P1, class P2, class P3, class ...Rest>
    struct or_<P1, P2, P3, Rest...>
      : or_<
          or_<P1, P2>, 
          or_<P3, Rest...>
        >
    { };
    
  }                                                         //  namespace etl
}                                                           // namespace elib
#endif /* ELIB_ETL_LOGICAL_HPP */