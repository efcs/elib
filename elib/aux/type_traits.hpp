#ifndef ELIB_AUX_TYPE_TRAITS_HPP
#define ELIB_AUX_TYPE_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/aux/static_const.hpp>
# include <elib/aux/no_decay.hpp>
# include <type_traits>

/* thanks to Matt Calabrese for new style enable if 
* and eric neibler for macro impl
*/
# define ELIB_ENABLE_IF(...)                                              \
  typename ::std::enable_if<static_cast<bool>(__VA_ARGS__)>::type* const& = \
    ::elib::aux::static_const<void*>::value
# 
# 
# define ELIB_ENABLE_IF_VALID_EXPR(...)              \
  decltype(static_cast<void>(__VA_ARGS__))* const& = \
    ::elib::aux::static_const<void*>::value
#

namespace elib 
{
    namespace aux
    {
        ////////////////////////////////////////////////////////////////////////
        // Primary Type Categories
        using std::is_void;
        using std::is_integral;
        using std::is_floating_point;
        using std::is_array;
        using std::is_enum;
        using std::is_union;
        using std::is_class;
        using std::is_function;
        using std::is_pointer;
        using std::is_lvalue_reference;
        using std::is_rvalue_reference;
        using std::is_member_object_pointer;
        using std::is_member_function_pointer;
        
        template <class T>
        using is_ptr = std::is_pointer<T>;
        
        template <class T>
        using is_lvalue_ref = std::is_lvalue_reference<T>;
        
        template <class T>
        using is_rvalue_ref = std::is_rvalue_reference<T>;
        
        template <class T>
        using is_mem_obj_ptr = std::is_member_object_pointer<T>;
        
        template <class T>
        using is_mem_fn_ptr = std::is_member_function_pointer<T>;
        
# if ELIB_CONFIG_CXX1Y || ELIB_CONFIG_CXX14
        using std::is_null_pointer;
        
        template <class T>
        using is_null_ptr = std::is_null_pointer<T>;
# endif
        
        ////////////////////////////////////////////////////////////////////////
        // Composite Type Categories
        using std::is_fundamental;
        using std::is_arithmetic;
        using std::is_scalar;
        using std::is_object;
        using std::is_compound;
        using std::is_reference;
        using std::is_member_pointer;
        
        template <class T>
        using is_ref = std::is_reference<T>;
        
        template <class T>
        using is_mem_ptr = std::is_member_pointer<T>;
        
        ////////////////////////////////////////////////////////////////////////
        // Type Information
        using std::is_const;
        using std::is_volatile;
        using std::is_trivial;
        
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        using std::is_trivially_copyable;
# endif
   
        using std::is_standard_layout;
        using std::is_pod;
        using std::is_literal_type;
        using std::is_empty;
        
        using std::is_polymorphic;
        using std::is_abstract;
        
        using std::is_signed;
        using std::is_unsigned;

        using std::is_constructible;
        using std::is_default_constructible;
        using std::is_copy_constructible;
        using std::is_move_constructible;

        using std::is_copy_assignable;
        using std::is_move_assignable;
        
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        using std::is_trivially_constructible;
        using std::is_trivially_default_constructible;
        using std::is_trivially_copy_constructible;
        using std::is_trivially_move_constructible;
        
        using std::is_trivially_copy_assignable;
        using std::is_trivially_move_assignable;
# endif
        using std::is_nothrow_constructible;
        using std::is_nothrow_default_constructible;
        using std::is_nothrow_copy_constructible;
        using std::is_nothrow_move_constructible;
     
        using std::is_nothrow_copy_assignable;
        using std::is_nothrow_move_assignable;
        
        using std::is_destructible;
        using std::is_trivially_destructible;
        using std::is_nothrow_destructible;

        using std::has_virtual_destructor;
    
        using std::alignment_of;
        using std::rank;
        using std::extent;
        
        using std::is_same;
        using std::is_base_of;
        using std::is_convertible;

        ////////////////////////////////////////////////////////////////////////
        // aux::remove_const, aux::remove_volatile, aux::remove_cv
        using std::remove_const;
        using std::remove_volatile;
        using std::remove_cv;
        
        template <class T>
        using remove_const_ = typename remove_const<T>::type;
      
        template <class T>
        using remove_volatile_ = typename remove_volatile<T>::type;
       
        template <class T>
        using remove_cv_ = typename remove_cv<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const, aux::add_volatile, aux::add_cv
        using std::add_const;
        using std::add_volatile;
        using std::add_cv;

        template <class T>
        using add_const_ = typename add_const<T>::type;
        
        template <class T>
        using add_volatile_ = typename add_volatile<T>::type;
        
        template <class T>
        using add_cv_ = typename add_cv<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_reference
        using std::remove_reference;
        
        template <class T>
        using remove_reference_ = typename remove_reference<T>::type;
        
        template <class T>
        using remove_ref = remove_reference<T>;
        
        template <class T>
        using remove_ref_ = typename remove_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_const_ref, aux::remove_volatile_ref, aux::remove_cv_ref
        template <class T>
        using remove_const_ref = remove_const< remove_ref_<T> >;
        
        template <class T>
        using remove_const_ref_ = remove_const_< remove_ref_<T> >;
        
        template <class T>
        using remove_volatile_ref = remove_volatile< remove_ref_<T> >;
        
        template <class T>
        using remove_volatile_ref_ = remove_volatile_< remove_ref_<T> >;
        
        template <class T>
        using remove_cv_ref = remove_cv< remove_ref_<T> >;
        
        template <class T>
        using remove_cv_ref_ = remove_cv_< remove_ref_<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_lvalue_reference, aux::add_lvalue_ref
        using std::add_lvalue_reference;
        
        template <class T>
        using add_lvalue_reference_ = typename add_lvalue_reference<T>::type;
        
        template <class T>
        using add_lvalue_ref = add_lvalue_reference<T>;
        
        template <class T>
        using add_lvalue_ref_ = typename add_lvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_lvalue_ref, aux::add_volatile_lvalue_ref, aux::add_cv_lvalue_ref
        template <class T>
        using add_const_lvalue_ref = add_const< add_lvalue_ref_<T> >;
        
        template <class T>
        using add_const_lvalue_ref_ = add_const_< add_lvalue_ref_<T> >;
        
        template <class T>
        using add_volatile_lvalue_ref = add_volatile< add_lvalue_ref_<T> >;
        
        template <class T>
        using add_volatile_lvalue_ref_ = add_volatile_< add_lvalue_ref_<T> >;
        
        template <class T>
        using add_cv_lvalue_ref = add_cv< add_lvalue_ref_<T> >;
        
        template <class T>
        using add_cv_lvalue_ref_ = add_cv_< add_lvalue_ref_<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_ref
        template <class T>
        using add_ref = add_lvalue_reference<T>;
        
        template <class T>
        using add_ref_ = typename add_lvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_ref, aux::add_volatile_ref, aux::add_cv_ref
        template <class T>
        using add_const_ref = add_const< add_ref_<T> >;
        
        template <class T>
        using add_const_ref_ = add_const_< add_ref_<T> >;
        
        template <class T>
        using add_volatile_ref = add_volatile< add_ref_<T> >;
        
        template <class T>
        using add_cv_ref = add_cv< add_ref_<T> >;
        
        template <class T>
        using add_cv_ref_ = add_cv_< add_ref_<T> >;

        ////////////////////////////////////////////////////////////////////////
        // aux::add_rvalue_reference, aux::add_rvalue_ref
        using std::add_rvalue_reference;
        
        template <class T>
        using add_rvalue_reference_ = typename add_rvalue_reference<T>::type;
        
        template <class T>
        using add_rvalue_ref = add_rvalue_reference<T>;
        
        template <class T>
        using add_rvalue_ref_ = typename add_rvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_rvalue_ref, aux::add_volatile_rvalue_ref, aux::add_cv_rvalue_ref
        template <class T>
        using add_const_rvalue_ref = add_const< add_rvalue_ref_<T> >;
        
        template <class T>
        using add_const_rvalue_ref_ = add_const_< add_rvalue_ref_<T> >;
        
        template <class T>
        using add_volatile_rvalue_ref = add_volatile< add_rvalue_ref_<T> >;
        
        template <class T>
        using add_volatile_rvalue_ref_ = add_volatile_< add_rvalue_ref_<T> >;
        
        template <class T>
        using add_cv_rvalue_ref = add_cv< add_rvalue_ref_<T> >;
        
        template <class T>
        using add_cv_rvalue_ref_ = add_cv_< add_rvalue_ref_<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_pointer, aux::remove_ptr
        using std::remove_pointer;
        
        template <class T>
        using remove_pointer_ = typename remove_pointer<T>::type;
        
        template <class T>
        using remove_ptr = remove_pointer<T>;
        
        template <class T>
        using remove_ptr_ = typename remove_pointer<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_const_ptr, aux::remove_volatile_ptr, aux::remove_cv_ptr
        template <class T>
        using remove_const_ptr = remove_const< remove_ptr_<T> >;
        
        template <class T>
        using remove_const_ptr_ = remove_const_< remove_ptr_<T> >;
        
        template <class T>
        using remove_volatile_ptr = remove_volatile< remove_ptr_<T> >;
        
        template <class T>
        using remove_volatile_ptr_ = remove_volatile_< remove_ptr_<T> >;
        
        template <class T>
        using remove_cv_ptr = remove_cv< remove_ptr_<T> >;
        
        template <class T>
        using remove_cv_ptr_ = remove_cv_< remove_ptr_<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_pointer, aux::add_ptr
        using std::add_pointer;
        
        template <class T>
        using add_pointer_ = typename add_pointer<T>::type;
        
        template <class T>
        using add_ptr = add_pointer<T>;
        
        template <class T>
        using add_ptr_ = typename add_pointer<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_ptr, aux::add_volatile_ptr, aux::add_cv_ptr
        template <class T>
        using add_const_ptr = add_const< add_ptr_<T> >;
        
        template <class T>
        using add_const_ptr_ = add_const_< add_ptr_<T> >;
        
        template <class T>
        using add_volatile_ptr = add_volatile< add_ptr_<T> >;
        
        template <class T>
        using add_volatile_ptr_ = add_volatile_< add_ptr_<T> >;
        
        template <class T>
        using add_cv_ptr = add_cv< add_ptr_<T> >;
        
        template <class T>
        using add_cv_ptr_ = add_cv_< add_ptr_<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::make_signed, aux::make_unsigned
        using std::make_signed;
        
        template <class T>
        using make_signed_ = typename make_signed<T>::type;
        
        using std::make_unsigned;
        
        template <class T>
        using make_unsigned_ = typename make_unsigned<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_extent, aux::remove_all_extents
        using std::remove_extent;
        
        template <class T>
        using remove_extent_ = typename remove_extent<T>::type;
        
        using std::remove_all_extents;
        
        template <class T>
        using remove_all_extents_ = typename remove_all_extents<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::aligned_storage, aux::aligned_union
        template <
            std::size_t Len
          , std::size_t Align = static_cast<std::size_t>(-1)
        >
        struct aligned_storage;
            
        template <std::size_t Len, std::size_t Align>
        struct aligned_storage
            : std::aligned_storage<Len, Align>
        {};
            
        template <std::size_t Len>
        struct aligned_storage<Len, static_cast<std::size_t>(-1)>
            : std::aligned_storage<Len>
        {};
        
        template <
            std::size_t Len
          , std::size_t Align = static_cast<std::size_t>(-1)
        >
        using aligned_storage_ = typename aligned_storage<Len, Align>::type;
        
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        using std::aligned_union;
        
        template <std::size_t Len, class ...T>
        using aligned_union_ = typename aligned_union<Len, T...>::type;
# endif

        ////////////////////////////////////////////////////////////////////////
        // aux::decay
        using std::decay;
        
        template <class T>
        using decay_ = typename decay<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::enable_if, aux::enable_if_c
        template <class Pred, class T = void>
        using enable_if = typename 
            std::enable_if<
                static_cast<bool>(Pred::type::value), T
            >::type;
            
        template <class Pred, class T = void>
        using enable_if_ = typename enable_if<Pred, T>::type;
        
        template <bool Pred, class T = void>
        using enable_if_c = std::enable_if<Pred, T>;
        
        template <bool Pred, class T = void>
        using enable_if_c_ = typename std::enable_if<Pred, T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::lazy_enable_if, aux::lazy_enable_if_c
        template <class Pred, class T = no_decay<void>>
        using lazy_enable_if = enable_if_<Pred, T>;
        
        template <class Pred, class T = no_decay<void>>
        using lazy_enable_if_ = typename enable_if_<Pred, T>::type;
        
        template <bool Pred, class T = no_decay<void>>
        using lazy_enable_if_c = enable_if_c_<Pred, T>;
        
        template <bool Pred, class T = no_decay<void>>
        using lazy_enable_if_c_ = typename enable_if_c_<Pred, T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::disable_if, aux::disable_if_c
        template <class Pred, class T = void>
        using disable_if = std::enable_if<!static_cast<bool>(Pred::type::value), T>;
        
        template <class Pred, class T = void>
        using disable_if_ = typename 
            std::enable_if<!static_cast<bool>(Pred::type::value), T>::type;
        
        template <bool Pred, class T = void>
        using disable_if_c = std::enable_if<!Pred, T>;
        
        template <bool Pred, class T = void>
        using disable_if_c_ = typename std::enable_if<!Pred, T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::lazy_disable_if, aux::lazy_disable_if_c
        template <class Pred, class T = no_decay<void>>
        using lazy_disable_if = disable_if_<Pred, T>;
        
        template <class Pred, class T = no_decay<void>>
        using lazy_disable_if_ = typename disable_if_<Pred, T>::type;
        
        template<bool Pred, class T = no_decay<void>>
        using lazy_disable_if_c = disable_if_c_<Pred, T>;
        
        template <bool Pred, class T = no_decay<void>>
        using lazy_disable_if_c_ = typename disable_if_c_<Pred, T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::conditional, aux::conditional_c
        template <class Pred, class Then, class Else>
        using conditional = 
            std::conditional<
                static_cast<bool>(Pred::type::value)
              , Then, Else
            >;
            
        template <class Pred, class Then, class Else>
        using conditional_ = typename conditional<Pred, Then, Else>::type;
        
        template <bool Pred, class Then, class Else>
        using conditional_c = std::conditional<Pred, Then, Else>;
        
        template <bool Pred, class Then, class Else>
        using conditional_c_ = typename std::conditional<Pred, Then, Else>::type;
        
        
        ////////////////////////////////////////////////////////////////////////
        // aux::lazy_conditional, aux::lazy_conditional_c
        template <class Pred, class Then, class Else>
        using lazy_conditional = conditional_<Pred, Then, Else>;
        
        template <class Pred, class Then, class Else>
        using lazy_conditional_ = typename conditional_<Pred, Then, Else>::type;
        
        template <bool Pred, class Then, class Else>
        using lazy_conditional_c = conditional_c_<Pred, Then, Else>;
        
        template <bool Pred, class Then, class Else>
        using lazy_conditional_c_ = typename conditional_c_<Pred, Then, Else>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::common_type, aux::underlying_type, aux::result_of
        using std::common_type;
        
        template <class ...T>
        using common_type_ = typename common_type<T...>::type;
        
        using std::underlying_type;
        
        template <class T>
        using underlying_type_ = typename underlying_type<T>::type;
        
        using std::result_of;
        
        template <class T>
        using result_of_ = typename result_of<T>::type;
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_TYPE_TRAITS_HPP */