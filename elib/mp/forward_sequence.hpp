#ifndef ELIB_MP_FORWARD_SEQUENCE_HPP
#define ELIB_MP_FORWARD_SEQUENCE_HPP

# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class S>
    using begin = get_impl_t<S>::template begin<S>;

    template <class S >
    using begin_t = typename begin<S>::type;
    
    
    template <class S>
    using end = typename get_impl_t<S>::template end<S>;

    template <class S>
    using end_t = typename end<S>::type;
    
    
    template <class S>
    using size = typename get_impl_t<S>::template size<S>;

    template <class S>
    using size_t = typename size<S>::type;
    
    
    template <class S>
    using empty = typename get_impl_t<S>::template empty<S>;

    template <class S>
    using empty_t = typename empty<S>::type;
    
    
    template <class S>
    using front = typename get_impl_t<S>::template front<S>;

    template <class S>
    using front_t = typename front<S>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_FORWARD_SEQUENCE_HPP */