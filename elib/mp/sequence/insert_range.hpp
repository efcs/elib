#ifndef ELIB_MP_SEQUENCE_INSERT_RANGE_HPP
#define ELIB_MP_SEQUENCE_INSERT_RANGE_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- insert_range ---------------------------// 
  
    template <class Seq, class Pos, class Range>
    struct insert_range
      : detail::insert_range_impl<sequence_tag_t<Seq>>
          ::template apply<Seq, Pos, Range>
    {};
    
      
    template <class Seq, class Pos, class Range>
    using insert_range_t = typename insert_range<Seq, Pos, Range>::type;
  
    
    namespace detail
    {
    //-------------------------------- insert_range_impl --------------------// 
      
      //TODO
      template <class Tag>
      struct insert_range_impl
      {
        template <class Seq, class Pos, class Range>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_INSERT_RANGE_HPP */