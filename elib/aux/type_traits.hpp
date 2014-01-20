#ifndef ELIB_AUX_TYPE_TRAITS_HPP
#define ELIB_AUX_TYPE_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/aux/static_const.hpp>
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
        using is_arith = std::is_arithmetic<T>;
        
        template <class T>
        using is_ref = std::is_reference<T>;
        
        template <class T>
        using is_mem_ptr = std::is_member_pointer<T>;
        
        ////////////////////////////////////////////////////////////////////////
        // Type Properties
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

        ////////////////////////////////////////////////////////////////////////
        // Supported operations
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
        
        ////////////////////////////////////////////////////////////////////////
        // Property Queries
        using std::alignment_of;
        using std::rank;
        using std::extent;
        
        ////////////////////////////////////////////////////////////////////////
        // Type Relationships
        using std::is_same;
        using std::is_base_of;
        using std::is_convertible;
                
        ////////////////////////////////////////////////////////////////////////
        // Const Volatile Specifiers
        template <class T>
        using remove_const = typename std::remove_const<T>::type;
      
        template <class T>
        using remove_volatile = typename std::remove_volatile<T>::type;
       
        template <class T>
        using remove_cv = typename std::remove_cv<T>::type;

        template <class T>
        using add_const = typename std::add_const<T>::type;
        
        template <class T>
        using add_volatile = typename std::add_volatile<T>::type;
        
        template <class T>
        using add_cv = add_volatile< add_const<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // References
        template <class T>
        using remove_reference = typename std::remove_reference<T>::type;
        
        template <class T>
        using remove_ref = remove_reference<T>;
        
        template <class T>
        using remove_const_ref = remove_const< remove_ref<T> >;
        
        template <class T>
        using remove_volatile_ref = remove_volatile< remove_ref<T> >;
        
        template <class T>
        using remove_cv_ref = remove_cv< remove_ref<T> >;
        
        template <class T>
        using add_lvalue_reference = typename std::add_lvalue_reference<T>::type;
        
        template <class T>
        using add_lvalue_ref = add_lvalue_reference<T>;
        
        template <class T>
        using add_rvalue_reference = typename std::add_rvalue_reference<T>::type;
        
        template <class T>
        using add_rvalue_ref = add_rvalue_reference<T>;
        
        template <class T>
        using add_reference = add_lvalue_ref<T>;
        
        template <class T>
        using add_ref = add_lvalue_ref<T>;
        
        template <class T>
        using add_const_lvalue_ref = add_const< add_lvalue_ref<T> >;
        
        template <class T>
        using add_volatile_lvalue_ref = add_volatile< add_lvalue_ref<T> >;
        
        template <class T>
        using add_cv_lvalue_ref = add_cv< add_lvalue_ref<T> >;
        
        template <class T>
        using add_const_rvalue_ref = add_const< add_rvalue_ref<T> >;
        
        template <class T>
        using add_volatile_rvalue_ref = add_volatile< add_rvalue_ref<T> >;
        
        template <class T>
        using add_cv_rvalue_ref = add_cv< add_rvalue_ref<T> >;
        
        template <class T>
        using add_const_ref = add_const< add_ref<T> >;
        
        template <class T>
        using add_volatile_ref = add_volatile< add_ref<T> >;
        
        template <class T>
        using add_cv_ref = add_cv< add_ref<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // Pointers
        template <class T>
        using remove_pointer = typename std::remove_pointer<T>::type;
        
        template <class T>
        using remove_ptr = remove_pointer<T>;
        
        template <class T>
        using remove_const_ptr = remove_ptr< remove_const<T> >;
        
        template <class T>
        using remove_volatile_ptr = remove_ptr< remove_volatile<T> >;
        
        template <class T>
        using remove_cv_ptr = remove_ptr< remove_cv<T> >;
        
        template <class T>
        using add_pointer = typename std::add_pointer<T>::type;
        
        template <class T>
        using add_ptr = add_pointer<T>;
        
        template <class T>
        using add_const_ptr = add_const< add_ptr<T> >;
        
        template <class T>
        using add_volatile_ptr = add_volatile< add_ptr<T> >;
        
        template <class T>
        using add_cv_ptr = add_cv< add_ptr<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // Sign Modifiers
        template <class T>
        using make_signed = typename std::make_signed<T>::type;
        
        template <class T>
        using make_unsigned = typename std::make_unsigned<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // Arrays
        template <class T>
        using remove_extent = typename std::remove_extent<T>::type;
        
        template <class T>
        using remove_all_extents = typename std::remove_all_extents<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // Misc Tranformations
        namespace detail
        {
            template <std::size_t Len, std::size_t Align = 0>
            struct aligned_storage_impl;
            
            template <std::size_t Len, std::size_t Align>
            struct aligned_storage_impl
              : std::aligned_storage<Len, Align>
            {};
            
            template <std::size_t Len>
            struct aligned_storage_impl<Len, 0>
              : std::aligned_storage<Len>
            {};
        }                                                   // namespace detail
        
        template <std::size_t Len, std::size_t Align = 0>
        using aligned_storage = typename detail::aligned_storage_impl<Len, Align>::type;
        
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        template <std::size_t Len, class ...T>
        using aligned_union = typename std::aligned_union<Len, T...>::type;
# endif

        template <class T>
        using decay = typename std::decay<T>::type;
        
        template <bool Pred, class T = void>
        using enable_if = typename std::enable_if<Pred, T>::type;

        template <class Pred, class T = void>
        using lazy_enable_if = typename std::enable_if<Pred::type::value, T>::type;
        
        template <bool Pred, class T = void>
        using disable_if = typename std::enable_if<!Pred, T>::type;
        
        template <class Pred, class T = void>
        using lazy_disable_if = typename std::enable_if<!Pred::type::value, T>::type;
        
        template <bool Pred, class Then, class Else>
        using conditional = typename std::conditional<Pred, Then, Else>::type;
        
        template <class Pred, class Then, class Else>
        using lazy_conditional = conditional<Pred::type::value, Then, Else>;
        
        template <class ...T>
        using common_type = typename std::common_type<T...>::type;
        
        template <class T>
        using underlying_type = typename std::underlying_type<T>::type;
        
        template <class T>
        using result_of = typename std::result_of<T>::type;
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_TYPE_TRAITS_HPP */