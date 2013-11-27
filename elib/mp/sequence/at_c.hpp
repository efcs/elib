#ifndef ELIB_MP_SEQUENCE_AT_C_HPP
# define ELIB_MP_SEQUENCE_AT_C_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/at.hpp>
# include <elib/mp/types.hpp>

# include <cstddef>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
      
      template <class Tag>
      struct at_c_impl
      {
        template <class Seq, std::size_t N>
        struct apply 
          : detail::at_impl<Tag> ::template apply< Seq, size_type<N> >
        {};
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_AT_C_HPP */