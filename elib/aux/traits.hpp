#ifndef ELIB_AUX_TRAITS_HPP
#define ELIB_AUX_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>

# include <string> /* for is_string_type */
# include <type_traits>
# include <functional> /* for *strip_t */
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    namespace traits
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
        using is_integral_enum = bool_<
            is_integral<T>::value || is_enum<T>::value
          >;
        
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
        
# if __cplusplus >= 201303L
        using std::is_null_pointer;
# endif

# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_void_v = is_void<T>::value;
        
        template <class T>
        constexpr bool is_integral_v = is_integral<T>::value;
        
        template <class T>
        constexpr bool is_floating_point_v = is_floating_point<T>::value;
        
        template <class T>
        constexpr bool is_array_v = is_array<T>::value;
        
        template <class T>
        constexpr bool is_enum_v = is_enum<T>::value;
        
        template <class T>
        constexpr bool is_class_v = is_class<T>::value;
        
        template <class T>
        constexpr bool is_union_v = is_union<T>::value;
        
        template <class T>
        constexpr bool is_function_v = is_function<T>::value;
        
        template <class T>
        constexpr bool is_pointer_v = is_pointer<T>::value;
        
        template <class T>
        constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
        
        template <class T>
        constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
        
        template <class T>
        constexpr bool is_member_object_pointer_v = 
            is_member_object_pointer<T>::value;
        
        template <class T>
        constexpr bool is_member_function_pointer_v = 
            is_member_function_pointer<T>::value;
            
        template <class T>
        constexpr bool is_integral_enum_v = is_integral_enum<T>::value;
        
        template <class T>
        constexpr bool is_ptr_v = is_ptr<T>::value;
        
        template <class T>
        constexpr bool is_lvalue_ref_v = is_lvalue_ref<T>::value;
        
        template <class T>
        constexpr bool is_rvalue_ref_v = is_rvalue_ref<T>::value;
        
        template <class T>
        constexpr bool is_mem_obj_ptr_v = is_mem_obj_ptr<T>::value;
        
        template <class T>
        constexpr bool is_mem_fn_ptr_v = is_mem_fn_ptr<T>::value;

#   if __cplusplus >= 201303L
        template <class T>
        constexpr bool is_null_pointer_v = is_null_pointer<T>::value;
# endif
    
# endif /* ELIB_CONFIG_HAS_VARIABLE_TEMPLATES */
        
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
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_fundamental_v = is_fundamental<T>::value;
        
        template <class T>
        constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
        
        template <class T>
        constexpr bool is_scalar_v = is_scalar<T>::value;
        
        template <class T>
        constexpr bool is_object_v = is_object<T>::value;
        
        template <class T>
        constexpr bool is_compound_v = is_compound<T>::value;
        
        template <class T>
        constexpr bool is_reference_v = is_reference<T>::value;
        
        template <class T>
        constexpr bool is_member_pointer_v = is_member_pointer<T>::value;
        
        template <class T>
        constexpr bool is_ref_v = is_ref<T>::value;
        
        template <class T>
        constexpr bool is_mem_ptr_v = is_mem_ptr<T>::value;
# endif /* ELIB_CONFIG_HAS_VARIABLE_TEMPLATES */
        
        ////////////////////////////////////////////////////////////////////////
        // Type Information
        using std::is_const;
        using std::is_volatile;
        using std::is_trivial;
        
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
    
        using std::is_assignable;
        using std::is_copy_assignable;
        using std::is_move_assignable;
        
        using std::is_nothrow_constructible;
        using std::is_nothrow_default_constructible;
        using std::is_nothrow_copy_constructible;
        using std::is_nothrow_move_constructible;
     
        using std::is_nothrow_assignable;
        using std::is_nothrow_copy_assignable;
        using std::is_nothrow_move_assignable;
        
        using std::is_destructible;
        using std::is_trivially_destructible;
        using std::is_nothrow_destructible;

        using std::has_virtual_destructor;
        
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        using std::is_trivially_copyable;
        
        using std::is_trivially_constructible;
        using std::is_trivially_default_constructible;
        using std::is_trivially_copy_constructible;
        using std::is_trivially_move_constructible;
        
        using std::is_trivially_assignable;
        using std::is_trivially_copy_assignable;
        using std::is_trivially_move_assignable;
# endif

# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_const_v = is_const<T>::value;
        
        template <class T>
        constexpr bool is_volatile_v = is_volatile<T>::value;
        
        template <class T>
        constexpr bool is_trivial_v = is_trivial<T>::value;
        
        template <class T>
        constexpr bool is_standard_layout_v = is_standard_layout<T>::value;
        
        template <class T>
        constexpr bool is_pod_v = is_pod<T>::value;
        
        template <class T>
        constexpr bool is_literal_type_v = is_literal_type<T>::value;
        
        template <class T>
        constexpr bool is_empty_v = is_empty<T>::value;
        
        template <class T>
        constexpr bool is_polymorphic_v = is_polymorphic<T>::value;
        
        template <class T>
        constexpr bool is_abstract_v = is_abstract<T>::value;
        
        template <class T>
        constexpr bool is_signed_v = is_signed<T>::value;
        
        template <class T>
        constexpr bool is_unsigned_v = is_unsigned<T>::value;
        
        template <class T, class ...Args>
        constexpr bool is_constructible_v = is_constructible<T, Args...>::value;
        
        template <class T>
        constexpr bool is_default_constructible_v = 
            is_default_constructible<T>::value;
        
        template <class T>
        constexpr bool is_copy_constructible_v = 
            is_copy_constructible<T>::value;
        
        template <class T>
        constexpr bool is_move_constructible_v = 
            is_move_constructible<T>::value;
            
        template <class T, class ...Args>
        constexpr bool is_assignable_v = is_assignable<T, Args...>::value;
        
        template <class T>
        constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;
        
        template <class T>
        constexpr bool is_move_assignable_v = is_move_assignable<T>::value;
        
        template <class T, class ...Args>
        constexpr bool is_nothrow_constructible_v = 
            is_nothrow_constructible<T, Args...>::value;
        
        template <class T>
        constexpr bool is_nothrow_default_constructible_v = 
            is_nothrow_default_constructible<T>::value;
        
        template <class T>
        constexpr bool is_nothrow_copy_constructible_v = 
            is_nothrow_copy_constructible<T>::value;
        
        template <class T>
        constexpr bool is_nothrow_move_constructible_v = 
            is_nothrow_move_constructible<T>::value;
            
        template <class T, class ...Args>
        constexpr bool is_nothrow_assignable_v = 
            is_nothrow_assignable<T, Args...>::value;
        
        template <class T>
        constexpr bool is_nothrow_copy_assignable_v = 
            is_nothrow_copy_assignable<T>::value;
        
        template <class T>
        constexpr bool is_nothrow_move_assignable_v = 
            is_nothrow_move_assignable<T>::value;
        
        template <class T>
        constexpr bool is_destructible_v = is_destructible<T>::value;
        
        template <class T>
        constexpr bool is_nothrow_destructible_v = 
            is_nothrow_destructible<T>::value;
        
        template <class T>
        constexpr bool is_trivially_destructible_v = 
            is_trivially_destructible<T>::value;
        
        template <class T>
        constexpr bool has_virtual_destructor_v = 
            has_virtual_destructor<T>::value;
            
#   if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        template <class T>
        constexpr bool is_trivially_copyable_v = 
            is_trivially_copyable<T>::value;
        
        template <class T, class ...Args>
        constexpr bool is_trivially_constructible_v = 
            is_trivially_constructible<T, Args...>::value;
        
        template <class T>
        constexpr bool is_trivially_default_constructible_v = 
            is_trivially_default_constructible<T>::value;
        
        template <class T>
        constexpr bool is_trivially_copy_constructible_v = 
            is_trivially_copy_constructible<T>::value;
        
        template <class T>
        constexpr bool is_trivially_move_constructible_v = 
            is_trivially_move_constructible<T>::value;
        
        template <class T, class ...Args>
        constexpr bool is_trivially_assignable_v = 
            is_trivially_assignable<T, Args...>::value;
        
        template <class T>
        constexpr bool is_trivially_copy_assignable_v = 
            is_trivially_copy_assignable<T>::value;
        
        template <class T>
        constexpr bool is_trivially_move_assignable_v = 
            is_trivially_move_assignable<T>::value;
#   endif /* ELIB_WORKAROUND */
# endif /* ELIB_CONFIG_HAS_VARIABLE_TEMPLATES */
    
        using std::alignment_of;
        using std::rank;
        using std::extent;
        
        using std::is_same;
        using std::is_base_of;
        using std::is_convertible;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_same_v = is_same<T>::value;
        
        template <class T>
        constexpr bool is_base_of_v = is_base_of<T>::value;
        
        template <class T>
        constexpr bool is_convertible_v = is_convertible<T>::value;
# endif /* ELIB_CONFIG_HAS_VARIABLE_TEMPLATES */

        ////////////////////////////////////////////////////////////////////////
        // aux::remove_const, aux::remove_volatile, aux::remove_cv
        using std::remove_const;
        using std::remove_volatile;
        using std::remove_cv;
        
        template <class T>
        using remove_const_t = typename remove_const<T>::type;
      
        template <class T>
        using remove_volatile_t = typename remove_volatile<T>::type;
       
        template <class T>
        using remove_cv_t = typename remove_cv<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const, aux::add_volatile, aux::add_cv
        using std::add_const;
        using std::add_volatile;
        using std::add_cv;

        template <class T>
        using add_const_t = typename add_const<T>::type;
        
        template <class T>
        using add_volatile_t = typename add_volatile<T>::type;
        
        template <class T>
        using add_cv_t = typename add_cv<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_reference
        using std::remove_reference;
        
        template <class T>
        using remove_reference_t = typename remove_reference<T>::type;
        
        template <class T>
        using remove_ref = remove_reference<T>;
        
        template <class T>
        using remove_ref_t = typename remove_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_const_ref, aux::remove_volatile_ref, aux::remove_cv_ref
        template <class T>
        using remove_const_ref = remove_const< remove_ref_t<T> >;
        
        template <class T>
        using remove_const_ref_t = remove_const_t< remove_ref_t<T> >;
        
        template <class T>
        using remove_volatile_ref = remove_volatile< remove_ref_t<T> >;
        
        template <class T>
        using remove_volatile_ref_t = remove_volatile_t< remove_ref_t<T> >;
        
        template <class T>
        using remove_cv_ref = remove_cv< remove_ref_t<T> >;
        
        template <class T>
        using remove_cv_ref_t = remove_cv_t< remove_ref_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_lvalue_reference, aux::add_lvalue_ref
        using std::add_lvalue_reference;
        
        template <class T>
        using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
        
        template <class T>
        using add_lvalue_ref = add_lvalue_reference<T>;
        
        template <class T>
        using add_lvalue_ref_t = typename add_lvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_lvalue_ref, aux::add_volatile_lvalue_ref, aux::add_cv_lvalue_ref
        template <class T>
        using add_const_lvalue_ref = add_const< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_const_lvalue_ref_t = add_const_t< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_volatile_lvalue_ref = add_volatile< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_volatile_lvalue_ref_t = add_volatile_t< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_cv_lvalue_ref = add_cv< add_lvalue_ref_t<T> >;
        
        template <class T>
        using add_cv_lvalue_ref_t = add_cv_t< add_lvalue_ref_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_ref
        template <class T>
        using add_ref = add_lvalue_reference<T>;
        
        template <class T>
        using add_ref_t = typename add_lvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_ref, aux::add_volatile_ref, aux::add_cv_ref
        template <class T>
        using add_const_ref = add_const< add_ref_t<T> >;
        
        template <class T>
        using add_const_ref_t = add_const_t< add_ref_t<T> >;
        
        template <class T>
        using add_volatile_ref = add_volatile< add_ref_t<T> >;
        
        template <class T>
        using add_cv_ref = add_cv< add_ref_t<T> >;
        
        template <class T>
        using add_cv_ref_t = add_cv_t< add_ref_t<T> >;

        ////////////////////////////////////////////////////////////////////////
        // aux::add_rvalue_reference, aux::add_rvalue_ref
        using std::add_rvalue_reference;
        
        template <class T>
        using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
        
        template <class T>
        using add_rvalue_ref = add_rvalue_reference<T>;
        
        template <class T>
        using add_rvalue_ref_t = typename add_rvalue_reference<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_rvalue_ref, aux::add_volatile_rvalue_ref, aux::add_cv_rvalue_ref
        template <class T>
        using add_const_rvalue_ref = add_const< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_const_rvalue_ref_t = add_const_t< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_volatile_rvalue_ref = add_volatile< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_volatile_rvalue_ref_t = add_volatile_t< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_cv_rvalue_ref = add_cv< add_rvalue_ref_t<T> >;
        
        template <class T>
        using add_cv_rvalue_ref_t = add_cv_t< add_rvalue_ref_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_pointer, aux::remove_ptr
        using std::remove_pointer;
        
        template <class T>
        using remove_pointer_t = typename remove_pointer<T>::type;
        
        template <class T>
        using remove_ptr = remove_pointer<T>;
        
        template <class T>
        using remove_ptr_t = typename remove_pointer<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_const_ptr, aux::remove_volatile_ptr, aux::remove_cv_ptr
        template <class T>
        using remove_const_ptr = remove_const< remove_ptr_t<T> >;
        
        template <class T>
        using remove_const_ptr_t = remove_const_t< remove_ptr_t<T> >;
        
        template <class T>
        using remove_volatile_ptr = remove_volatile< remove_ptr_t<T> >;
        
        template <class T>
        using remove_volatile_ptr_t = remove_volatile_t< remove_ptr_t<T> >;
        
        template <class T>
        using remove_cv_ptr = remove_cv< remove_ptr_t<T> >;
        
        template <class T>
        using remove_cv_ptr_t = remove_cv_t< remove_ptr_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_pointer, aux::add_ptr
        using std::add_pointer;
        
        template <class T>
        using add_pointer_t = typename add_pointer<T>::type;
        
        template <class T>
        using add_ptr = add_pointer<T>;
        
        template <class T>
        using add_ptr_t = typename add_pointer<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::add_const_ptr, aux::add_volatile_ptr, aux::add_cv_ptr
        template <class T>
        using add_const_ptr = add_const< add_ptr_t<T> >;
        
        template <class T>
        using add_const_ptr_t = add_const_t< add_ptr_t<T> >;
        
        template <class T>
        using add_volatile_ptr = add_volatile< add_ptr_t<T> >;
        
        template <class T>
        using add_volatile_ptr_t = add_volatile_t< add_ptr_t<T> >;
        
        template <class T>
        using add_cv_ptr = add_cv< add_ptr_t<T> >;
        
        template <class T>
        using add_cv_ptr_t = add_cv_t< add_ptr_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::make_signed, aux::make_unsigned
        using std::make_signed;
        
        template <class T>
        using make_signed_t = typename make_signed<T>::type;
        
        using std::make_unsigned;
        
        template <class T>
        using make_unsigned_t = typename make_unsigned<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::remove_extent, aux::remove_all_extents
        using std::remove_extent;
        
        template <class T>
        using remove_extent_t = typename remove_extent<T>::type;
        
        using std::remove_all_extents;
        
        template <class T>
        using remove_all_extents_t = typename remove_all_extents<T>::type;
        
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
        using aligned_storage_t = typename aligned_storage<Len, Align>::type;
        
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        using std::aligned_union;
        
        template <std::size_t Len, class ...T>
        using aligned_union_t = typename aligned_union<Len, T...>::type;
# endif
    
        using std::conditional;
        
        template <bool Pred, class Then, class Else>
        using conditional_t = typename conditional<Pred, Then, Else>::type;
        
        ///////////////////////////////////////////////////////////////////////
        // aux::decay
        using std::decay;
        
        template <class T>
        using decay_t = typename decay<T>::type;

        ////////////////////////////////////////////////////////////////////////
        // aux::common_type
        using std::common_type;
        
        template <class ...T>
        using common_type_t = typename common_type<T...>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::underlying_type
        using std::underlying_type;
        
        template <class T>
        using underlying_type_t = typename underlying_type<T>::type;
        
        namespace traits_detail
        {
            template <
                class T
              , bool IsEnum = is_enum<T>::value
              , bool IsIntegral = is_integral<T>::value
            >
            struct sfinae_underlying_type_impl;
            
            template <class T>
            struct sfinae_underlying_type_impl<T, true, false>
            {
                using type = underlying_type_t<T>;
            };
            
            template <class T>
            struct sfinae_underlying_type_impl<T, false, true>
            {
                using type = T;
            };
        }
        
        template <class T>
        struct sfinae_underlying_type
          : traits_detail::sfinae_underlying_type_impl<T>
        {};
        
        template <class T>
        using sfinae_underlying_type_t = typename
            traits_detail::sfinae_underlying_type_impl<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::result_of
        using std::result_of;
        
        template <class T>
        using result_of_t = typename result_of<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::uncvref
        template <class T>
        using uncvref = remove_cv_t< remove_ref_t<T> >;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::decay_uncvref
        template <class T>
        using decay_uncvref = remove_cv_t< remove_ref_t< decay_t<T> >>;
        
        ////////////////////////////////////////////////////////////////////////
        // same_type
        namespace traits_detail
        {
            template <class T, class U>
            struct same_type_impl : false_ {};
            
            template <class T>
            struct same_type_impl<T, T> : true_ {};
        }                                                   // namespace traits_detail
        
        template <class T, class U>
        struct same_type 
          : traits_detail::same_type_impl< uncvref<T>, uncvref<U> >
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // same_intc
        namespace traits_detail
        {
            template <class T0, T0 V0, class T1, T1 V1>
            struct same_intc_impl : false_ {};
            
            template <class T, T V>
            struct same_intc_impl<T, V, T, V> : true_ {};
        }                                                   // namespace traits_detail
        
        template <class T, class U>
        struct same_inc 
          : traits_detail::same_intc_impl<
              typename T::value_type, T::value
            , typename U::value_type, U::value
            >
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // aux::strip_ref_wrapper
        template <class T>
        struct strip_ref_wrapper 
        { 
            using type = T; 
        };

        template <class T>
        struct strip_ref_wrapper< std::reference_wrapper<T> >
        {
            using type = T&;
        };

        template <class T>
        using strip_ref_wrapper_t = typename strip_ref_wrapper<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // aux::decay_strip
        template <class T>
        struct decay_strip
        {
            using type = strip_ref_wrapper_t< typename decay<T>::type >;
        };

        template <class T>
        using decay_strip_t = strip_ref_wrapper_t< typename decay<T>::type >;
        
        ////////////////////////////////////////////////////////////////////////
        //
        namespace traits_detail
        {
            // to avoid deps, implement own declval
            template <class T>
            add_rvalue_ref_t<T> declval();

            auto is_string_type_impl(const volatile char* const) -> true_;
            auto is_string_type_impl(std::string) -> true_;
            auto is_string_type_impl(...) -> false_;
            
            template <class T>
            using is_c_string_impl = elib::bool_<
                   is_same<char*, T>::value
                or is_same<const char*, T>::value
                or is_same<volatile char*, T>::value
                or is_same<const volatile char*, T>::value
              >;
        }
               
        template <class T>
        using is_c_string = traits_detail::is_c_string_impl<decay_t<T>>;
        
        template <class T>
        using is_string_type = decltype(
            traits_detail::is_string_type_impl(
                traits_detail::declval<T>()
              )
          );
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_c_string_v = is_c_string<T>::value;
        
        template <class T>
        constexpr bool is_string_type_v = is_string_type<T>::value;
# endif /* ELIB_CONFIG_HAS_VARIABLE_TEMPLATES */

        template <class T>
        using is_nullptr = is_same<decltype(nullptr), uncvref<T>>;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_nullptr_v = is_nullptr<T>::value;
# endif

        namespace traits_adl_barrier
        {
            using std::swap;
            
            template <class T>
            using has_noexcept_swap = elib::bool_<
                noexcept( swap(std::declval<T &>(), std::declval<T &>()) )
            >;
        }
        
        using traits_adl_barrier::has_noexcept_swap;

    }                                                       // namespace traits
    
    using namespace ::elib::aux::traits;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_HPP */