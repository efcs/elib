#ifndef ELIB_UTILITY_INTEGER_SEQUENCE_HPP
#define ELIB_UTILITY_INTEGER_SEQUENCE_HPP

/* Conforms to C++14 proposal for compile-time integer_seq */
# include <cstddef>
# include <type_traits>

namespace elib 
{
  
//-------------------------------- integer_seq ------------------------------// 
  
  template<class T, T ...Seq> 
  struct integer_seq
  {
    static constexpr T size = sizeof...(Seq);
    
    template <T N>
    using append = integer_seq<T, Seq..., N>;
    
    // Extension
    template <T N>
    using prepend = integer_seq<T, N, Seq...>;
    
    using next = append<sizeof...(Seq)>;
  };
  
  template<int... I>
  using int_seq = integer_seq<int, I...>;
  
  template<unsigned... I>
  using uint_seq = integer_seq<unsigned, I...>;
  
  template<size_t... I>
  using index_seq = integer_seq<std::size_t, I...>;

  
//---------------------------- make_integer_seq_impl ----------------------// 
  
  namespace detail
  {
    
    template <class T, class Count, class Seq>
    struct make_seq_impl;
    
    template <class T, class Seq>
    struct make_seq_impl<T, std::integral_constant<T, 0>, Seq>
    { 
      using type = Seq;
    };
    
    template <class T, class Count, class Seq>
    struct make_seq_impl
      : make_seq_impl<
            T
          , std::integral_constant<T, Count::value-1>
          , typename Seq::next
        >
    {};
    
    
  }                                                        // namespace detail
  

//-------------------------------- make_seq --------------------------------// 
  
  template<class T, T N>
  using make_integer_seq = 
    typename detail::make_seq_impl<
        T
      , std::integral_constant<T, N>
      , integer_seq<T>
    >::type;
  
  template<int N>
  using make_int_seq = make_integer_seq<int, N>;
  
  template<unsigned N>
  using make_uint_seq = make_integer_seq<unsigned, N>;
  
  template<size_t N>
  using make_index_seq = make_integer_seq<std::size_t, N>;

//-------------------------------- to_seq --------------------------------// 
     
  template<class... T>
  using to_int_seq = make_int_seq<sizeof...(T)>;
  
  template<class... T>
  using to_uint_seq = make_uint_seq<sizeof...(T)>;
  
  template<class... T>
  using to_index_seq = make_index_seq<sizeof...(T)>;
}                                                           // namespace elib
#endif /* ELIB_UTILITY_INTEGER_SEQUENCE_HPP */