#ifndef ELIB_MP_VARIADIC_FWD_HPP
#define ELIB_MP_VARIADIC_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct pack;
    
    
    template <class T>
    struct is_pack;
    
    template <class T>
    using is_pack_t = typename is_pack<T>::type;
    
    
    template <class T>
    struct make_pack;
    
    template <class T>
    using make_pack_t = typename make_pack<T>::type;
    
    
    template <class FirstPack, class SecondPack>
    struct concat;
    
    template <class F, class S>
    using concat_t = typename concat<F, S>::type;
    
    
    template <class Pack, class ...ToAppend>
    struct append;
    
    template <class Pack, class ...ToAppend>
    using append_t = typename append<Pack, ToAppend...>::type;
    
    
    template <class Pack, class ...ToPrepend>
    struct prepend;
    
    template <class Pack, class ...ToPrepend>
    using prepend_t = typename prepend<Pack, ToPrepend...>::type;
    
    
    template <std::size_t N, class T>
    struct make_pack_of;
    
    template <std::size_t N, class T>
    using make_pack_of_t = typename make_pack_of<N, T>::type;
    
    
    namespace detail
    {
      template <std::size_t N, class T>
      struct make_pack_of_impl;
    }                                                       // namespace detail
    
    
    template <std::size_t N, class ...Args>
    struct get_nth;
    
    template <std::size_t N, class ...Args>
    using get_nth_t = typename get_nth<N, Args...>::type;
    
    
    template <std::size_t N, class ...Args>
    struct drop_n;
    
    template <std::size_t N, class ...Args>
    using drop_n_t = typename drop_n<N, Args...>::type;
    
    
    namespace detail
    {
      
      template <class = decltype(nullptr)>
      struct eat_pod;
      
      template <class PtrSeq>
      struct get_nth_impl;
      
      template <class PtrSeq>
      struct drop_n_impl;
    }                                                       // namespace detail
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_FWD_HPP */