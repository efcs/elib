#ifndef ELIB_ENUMERATION_DETAIL_ENUM_FIELDS_HPP
#define ELIB_ENUMERATION_DETAIL_ENUM_FIELDS_HPP

# include <elib/aux/integral_constant.hpp>

namespace elib { namespace enumeration
{
    namespace detail
    {
        template <bool Found, class FieldT>
        struct extracted_field 
        {
            using value_type = typename FieldT::value_type;
            
            static constexpr const bool found = Found;
            static constexpr const value_type value = FieldT::value;
        };
        
        template <bool Found, class FieldT>
        constexpr const bool extracted_field<Found, FieldT>::found;
        
        template <bool Found, class FieldT>
        constexpr const typename FieldT::value_type extracted_field<Found, FieldT>::value;
        
    
        template <class T, template <class> class FieldType, class Default>
        struct field_extractor_
        {
        private:
            template <class U>
            static extracted_field<true, FieldType<U>> test(int);
            
            template <class>
            static extracted_field<false, Default> test(long);
            
        public:
            using type = decltype(test<T>(0));
        };
        
        template <class T, template <class> class FieldType, class Default>
        using field_extractor = typename field_extractor_<T, FieldType, Default>::type;
        
        template <class T>
        using default_value_field_t = ELIB_AUTO_INTC(T::ELIB_ENUM_DEFAULT_VALUE);
        
        template <class T>
        using error_value_field_t = ELIB_AUTO_INTC(T::ELIB_ENUM_ERROR_VALUE);
            
        template <class T>
        using first_value_field_t = ELIB_AUTO_INTC(T::ELIB_ENUM_FIRST_VALUE);
        
        template <class T>
        using last_value_field_t = ELIB_AUTO_INTC(T::ELIB_ENUM_LAST_VALUE);
        
        template <class T>
        using is_contigious_field_t = 
            bool_<static_cast<bool>(T::ELIB_ENUM_IS_CONTIGIOUS)>;
                
        template <class T>
        using is_bitmask_field_t = 
            bool_<static_cast<bool>(T::ELIB_ENUM_IS_BITMASK)>;
            
        template <class T>
        using is_arithmetic_field_t =
            bool_<static_cast<bool>(T::ELIB_ENUM_IS_ARITHMETIC)>;
            
        template <class T>
        using is_logical_field_t = 
            bool_<static_cast<bool>(T::ELIB_ENUM_IS_LOGICAL)>;
            
        template <class T>
        using is_mixed_comparible_field_t = 
            bool_<static_cast<bool>(T::ELIB_ENUM_IS_MIXED_COMPARIBLE)>;
       
    }                                                       // namespace detail
}}                                               // namespace elib::enumeration
#endif /* ELIB_ENUMERATION_DETAIL_ENUM_FIELDS_HPP */
