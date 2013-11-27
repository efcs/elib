#ifndef ELIB_MP_SEQUENCE_INSERT_HPP
#define ELIB_MP_SEQUENCE_INSERT_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- insert ---------------------------------// 
  
    template <class Seq, class Pos, class T>
    struct insert
      : detail::insert_impl<sequence_tag_t<Seq>>
          ::template apply<Seq, Pos, T>
    {};
    
    
    template <class Seq, class Pos, class T>
    using insert_t = typename insert<Seq, Pos, T>::type;
 
    
    namespace detail
    {
    //-------------------------------- insert_impl --------------------------// 
      
      //TODO
      template <class Tag>
      struct insert_impl
      {
        template <class Seq, class Pos, class T>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_INSERT_HPP */
