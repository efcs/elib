#ifndef ELIB_MP_ALGORITHM_DETAIL_REVERSE_BEGIN_HPP
#define ELIB_MP_ALGORITHM_DETAIL_REVERSE_BEGIN_HPP

# include <elib/mp/identity.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      
      template <class Seq>
      struct reverse_begin
      {
        using begin_ = begin_t<Seq>;
        using end_ = end_t<Seq>;
        
        using type = 
          eval_if_t<
              aux::same_type<begin_, end_>
            , identity< end_ >
            , prior< end_ >
          >;
      };
      
      
      template <class Seq>
      using reverse_begin_t = typename reverse_begin<Seq>::type;
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_REVERSE_BEGIN_HPP */
