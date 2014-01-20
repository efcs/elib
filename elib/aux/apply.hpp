#ifndef ELIB_AUX_APPLY_HPP
#define ELIB_AUX_APPLY_HPP

namespace elib 
{
    namespace aux
    {
        template <class T, class ...Args>
        struct _apply
          : T::template apply<Args...>
        {};
        
        template <class T, class ...Args>
        using apply_ = typename _apply<T, Args...>::type;
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_APPLY_HPP */