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
    
    template <class Seq>
    struct variadic_size;
    
    template <class Seq>
    struct variadic_empty;
    
    template <class Seq, std::size_t N, class Pack = detail::basic_pack<>>
    struct variadic_at;
    
    template <class Seq>
    struct variadic_front;
    
    template <class Seq>
    struct variadic_back;
    
    template <class Seq>
    struct variadic_pop_back;
    
    template <class Seq>
    struct variadic_pop_front;
    
    template <class Seq, std::size_t N, class Pack = detail::basic_pack<>>
    struct variadic_drop;
    
    template <class Seq, std::size_t N>
    struct variadic_take;
    
    template <class Seq, std::size_t First, std::size_t Last>
    struct variadic_slice;

    template <class LHS, class RHS>
    struct variadic_concat;
    
    template <class Seq, class T>
    struct variadic_push_back;
    
    template <class Seq, class T>
    struct variadic_push_front;
    
    template <class Seq, class ...Args>
    struct variadic_append;
    
    template <class Seq, class ...Args>
    struct variadic_prepend;
    
    template <std::size_t N, class T, class List = detail::basic_pack<>>
    struct variadic_fill;
    
    
    namespace detail
    {
      template <class Seq> struct variadic_at_impl;
      
      template <class Seq, class To> 
      struct variadic_drop_impl;
      
      template <class List, class Ret>
      struct variadic_drop_function_helper;
      
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