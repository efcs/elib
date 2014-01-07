#ifndef ELIB_MP_VARIADIC_FWD_HPP
#define ELIB_MP_VARIADIC_FWD_HPP

# include <elib/mp/iterator/fwd.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    { 
      template <class ...> struct basic_pack {};
    }
    
    template <
        class Seq
      , std::size_t N
      , template <class...> class Pack = detail::basic_pack
      >
    struct variadic_at;
    
    
    template <
        class Seq, std::size_t N
      , template <class...> class Pack = detail::basic_pack
      >
    struct variadic_drop;
    
    
    template <
      class Seq, std::size_t N
      >
    struct variadic_take;
    
    
    template <
        class Seq
      , std::size_t First
      , std::size_t Last
      >
    struct variadic_slice;
    
    
    template <
        class LHS
      , class RHS
      >
    struct variadic_join;
    
    
    template <
        class Seq
      , class ...Args
      >
    struct variadic_append;
    
    
    template <
        class Seq
      , class ...Args
      >
    struct variadic_prepend;
    
    
    template <template <class...> class Seq, class T, std::size_t N>
    struct fill_variadic;
    
    
    namespace detail
    {
      template <class Seq> struct variadic_at_impl;
      
      template <class Seq, template <class...> class To> 
      struct variadic_drop_impl;
      
      template <class To, std::size_t N, bool = (N > 4)> 
      struct variadic_take_impl;
    }
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            Sequence                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    // implementations are not in namespace detail since they
    // are meant to be generic for any variadic template
    template <
        template <class, std::size_t> class IteratorType
          = default_random_access_iterator
      >
    struct variadic_pack_intrinsics;
    
    struct variadic_pack_iterator_intrinsics;
  
  
  ////////////////////////////////////////////////////////////////////////////////
  //                            List                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    template <class ...Args> 
    struct variadic_list_iterator;
    
    template <
      template <class...> class IteratorType = variadic_list_iterator 
      >
    struct variadic_list_intrinsics;
    
    
    struct variadic_list_iterator_intrinsics;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_FWD_HPP */