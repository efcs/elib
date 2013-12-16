#ifndef ELIB_MP_VARIADIC_EXTENSIBLE_SEQUENCE_HPP
#define ELIB_MP_VARIADIC_EXTENSIBLE_SEQUENCE_HPP

# include <elib/mp/front_extensible_sequence.hpp>
# include <elib/mp/back_extensible_sequence.hpp>
# include <elib/mp/get_impl.hpp>
# include <cstddef>


namespace elib 
{
  namespace mp
  {
    
    template <class Pack, std::size_t N>
    struct drop : typename get_impl_t<Pack>::template drop<Pack, N>;
    
    template <class Pack, std::size_t N>
    using drop_t = typename drop<Pack, N>::type;
    
    
    template <class Pack, std::size_t N>
    struct take = typename get_impl_t<Pack>::template take<Pack, N>;
    
    template <class Pack, std::size_t N>
    struct take_t = typename take<Pack, N>::type;
    
    
    template <class Pack, std::size_t First, std::size_t Last>
    struct slice = typename get_impl_t<Pack>::template slice<Pack, First, Last>;
    
    template <class Pack, std::size_t First, std::size_t Second>
    using slice_t = typename slice<Pack, First, Second>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_EXTENSIBLE_SEQUENCE_HPP */