#ifndef ELIB_MP_LIST_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_LIST_ITERATOR_INTRINSICS_HPP

# include <elib/mp/list/fwd.hpp>
# include <elib/mp/list/list.hpp>
# include <elib/mp/list/iterator.hpp>
# include <elib/mp/list/intrinsics.hpp>
# include <elib/mp/iterator.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      struct list_iterator_intrinsics
      {
        
        template <class Iter> struct deref;
        template <class Iter> struct next;
        template <class Iter, class N> struct advance;
        template <class Iter, std::size_t N> struct advance_c;
        template <class First, class Last> struct distance;
        
        template <class First, class ...Rest>
        struct deref< list_iterator<list<First, Rest...>> >
        {
          using type = First;
        };
        
        template <class First, class ...Rest>
        struct next< list_iterator<list<First, Rest...>> >
        {
          using type = list_iterator< list<Rest...> >;
        };
        
        template <class Iter, std::size_t N>
        struct advance_c : advance_c<typename next<Iter>::type, N-1>
        {};
        
        template <class Iter>
        struct advance_c<Iter, 0>
        {
          using type = Iter;
        };
        
        template <class Iter, class N>
        struct advance : advance_c<Iter, N::type::value>
        {};
        
        template <class ...Left, class ...Right>
        struct distance< 
            list_iterator<list<Left...>>
          , list_iterator<list<Right...>>
          >
        {
          using type = long_< 
            static_cast<long>(
              sizeof...(Left) - sizeof...(Right)
            )>;
        };
        
      };                                     // struct list_iterator_intrinsics
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_ITERATOR_INTRINSICS_HPP */