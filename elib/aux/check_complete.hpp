#ifndef ELIB_AUX_CHECK_COMPLETE_HPP
#define ELIB_AUX_CHECK_COMPLETE_HPP

/// A traits that checks that a list of types are complete.
/// It causes a compile error if a given type is not complete
# include <elib/config.hpp>

namespace elib { namespace aux
{
    template <class ...Args>
    struct check_complete;
    
    template <>
    struct check_complete<>
    {
    };
    
    template <class First, class ...Rest>
    struct check_complete<First, Rest...>
      : check_complete<First>
      , check_complete<Rest...>
    {
    };
    
    template <class T>
    struct check_complete<T>
    {
        static_assert(sizeof(T) > 0, "Type must be complete");
    };
    
    template <class T>
    struct check_complete<T &> : check_complete<T> {};
    
    template <class T>
    struct check_complete<T &&> : check_complete<T> {};
    
    template <class Ret, class ...Args>
    struct check_complete<Ret(Args...)> : check_complete<Ret> {};
    
    template <class Ret, class ...Args>
    struct check_complete<Ret(*)(Args...)> : check_complete<Ret> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...)> : check_complete<Class> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) const> 
      : check_complete<Class> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) volatile> 
      : check_complete<Class> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) const volatile> 
      : check_complete<Class> {};
    
# if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) &> 
      : check_complete<Class> {};

    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) const &> 
      : check_complete<Class> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) volatile &> 
      : check_complete<Class> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) const volatile &> 
      : check_complete<Class> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) &&> 
      : check_complete<Class> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) const &&> 
      : check_complete<Class> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) volatile &&> 
      : check_complete<Class> {};
    
    template <class Ret, class Class, class ...Args>
    struct check_complete<Ret(Class::*)(Args...) const volatile &&> 
      : check_complete<Class> {};
# endif
    
    template <class Ret, class Class>
    struct check_complete<Ret Class::*> : check_complete<Class> {};
}}                                                          // namespace elib
#endif /* ELIB_AUX_CHECK_COMPLETE_HPP */