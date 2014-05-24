#ifndef ELIB_AUX_TRAITS_MEMBER_POINTER_TRAITS_HPP
#define ELIB_AUX_TRAITS_MEMBER_POINTER_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/type_list.hpp>
# include <elib/aux/traits/is_member_function_pointer.hpp>
# include <elib/aux/traits/is_member_object_pointer.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        template <
            class MPtr
          , bool IsFunc   = is_member_function_pointer<MPtr>::value
          , bool IsObject = is_member_object_pointer<MPtr>::value
          >
        struct member_pointer_traits_impl
        {
            static_assert(
                not IsObject && not IsFunc
              , "Wrong overload selected"
              );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<Ret(ClassType::*)(Args...), true, false>
        {
            using type = Ret(ClassType::*)(Args...);
            using result = Ret;
            using class_type = ClassType;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) const
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) const;
            using result = Ret;
            using class_type = ClassType const;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) volatile
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) volatile;
            using result = Ret;
            using class_type = ClassType volatile;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) const volatile
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) const volatile;
            using result = Ret;
            using class_type = ClassType const volatile;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
# if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) &
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) &;
            using result = Ret;
            using class_type = ClassType &;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };

        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) const &
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) const &;
            using result = Ret;
            using class_type = ClassType const &;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) volatile &
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) volatile &;
            using result = Ret;
            using class_type = ClassType volatile &;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) const volatile &
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) const volatile &;
            using result = Ret;
            using class_type = ClassType const volatile &;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) &&
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) &&;
            using result = Ret;
            using class_type = ClassType &&;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) const &&
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) const &&;
            using result = Ret;
            using class_type = ClassType const &&;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) volatile &&
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) volatile &&;
            using result = Ret;
            using class_type = ClassType volatile &&;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class Ret, class ClassType, class ...Args>
        struct member_pointer_traits_impl<
            Ret(ClassType::*)(Args...) const volatile &&
          , true, false
          >
        {
            using type = Ret(ClassType::*)(Args...) const volatile &&;
            using result = Ret;
            using class_type = ClassType const volatile &&;
            using param_list = type_list<Args...>;
            using arity = ELIB_AUTO_INTC( sizeof...(Args) );
        };
# endif

        template <class Ret, class ClassType>
        struct member_pointer_traits_impl<Ret ClassType::*, false, true>
        {
            using type = Ret ClassType::*;
            using result = Ret;
            using class_type = ClassType;
            using arity = integral_constant<std::size_t, 0>;
        };

    }                                                      // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <class MemPtr>
    struct member_pointer_traits
      : detail::member_pointer_traits_impl<MemPtr>
    {};
}}                                                          // namespace elib
#endif /* ELIB_AUX_MEMBER_POINTER_TRAITS_HPP */