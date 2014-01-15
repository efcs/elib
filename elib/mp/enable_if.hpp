#ifndef ELIB_MP_ENABLE_IF_HPP
#define ELIB_MP_ENABLE_IF_HPP

namespace elib 
{
  namespace mp
  {
    
    template <bool Pred, class Ret=void>
    struct enable_if_c
    {
      static_assert(!Pred, "overload resolution check");
    };
    
    template <class Ret>
    struct enable_if_c<true, Ret>
    {
      using type = Ret;
    };
    
    template <bool Pred, class Ret=void>
    using enable_if_c_t = typename enable_if_c<Pred, Ret>::type;
    
    template <class Pred, class Ret=void>
    using enable_if = enable_if_c< static_cast<bool>(Pred::type::value), Ret>;
    
    template <class Pred, class Ret=void>
    using enable_if_t = typename enable_if<Pred, Ret>::type;
    
    template <class Pred, class Ret = void>
    using disable_if = enable_if_c<!Pred::type::value, Ret>;
    
    template <class Pred, class Ret = void>
    using disable_if_t = enable_if_c_t<!Pred::type::value, Ret>;
    
    template <bool Pred, class Ret = void>
    using disable_if_c = enable_if_c<!Pred, Ret>;
    
    template <bool Pred, class Ret = void>
    using disable_if_c_t = enable_if_c_t<!Pred, Ret>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ENABLE_IF_HPP */