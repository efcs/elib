#ifndef ELIB_MP_INDEX_SEQUENCE_HPP
#define ELIB_MP_INDEX_SEQUENCE_HPP

# include <elib/mp/fwd/index_sequence.hpp>
# include <cstddef>

/* Thanks to ericniebler/proto-0x for implementation */
namespace elib 
{
  namespace mp
  {
    
    template <std::size_t ...Indexes>
    struct index_seq
    {
      using type = index_seq;
      using next = index_seq<Indexes..., sizeof...(Indexes)>;
      
      static constexpr std::size_t size = sizeof...(Indexes);
    };
    
    
    namespace detail
    {      
      
      template <std::size_t ...LHS, std::size_t ...RHS>
      struct append_index_seq< 
        index_seq<LHS...>, index_seq<RHS...> 
      >
      {
        using type = index_seq<LHS..., (sizeof...(LHS) + RHS)...>;
      };
      
      template <std::size_t N>
      struct make_index_seq_impl
        : append_index_seq<
            typename make_index_seq_impl< N / 2>::type
          , typename make_index_seq_impl< N - (N / 2)>::type
          >
      {};
      
      
      template <>
      struct make_index_seq_impl<0>
      { using type = index_seq<>; };
      
      template <>
      struct make_index_seq_impl<1>
      { using type = index_seq<0>; };
      
      template <>
      struct make_index_seq_impl<2>
      { using type = index_seq<0, 1>; };
      
      template <>
      struct make_index_seq_impl<3>
      { using type = index_seq<0, 1, 2>; };
      
      template <>
      struct make_index_seq_impl<4>
      { using type = index_seq<0, 1, 2, 3>; };
      
      template <>
      struct make_index_seq_impl<5>
      { using type = index_seq<0, 1, 2, 3, 4>; };
      
      template <>
      struct make_index_seq_impl<6>
      { using type = index_seq<0, 1, 2, 3, 4, 5>; };
      
      template <>
      struct make_index_seq_impl<7>
      { using type = index_seq<0, 1, 2, 3, 4, 5, 6>; };
      
      template <>
      struct make_index_seq_impl<8>
      { using type = index_seq<0, 1, 2, 3, 4, 5, 6, 7>; };
      
      template <>
      struct make_index_seq_impl<9>
      { using type = index_seq<0, 1, 2, 3, 4, 5, 6, 7, 8>; };
      
      template <>
      struct make_index_seq_impl<10>
      { using type = index_seq<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>; };
      
    }                                                       // namespace detail    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INDEX_SEQUENCE_HPP */