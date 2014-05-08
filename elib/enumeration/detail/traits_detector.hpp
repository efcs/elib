#ifndef ELIB_ENUMERATION_DETAIL_TRAITS_DETECTOR_HPP
#define ELIB_ENUMERATION_DETAIL_TRAITS_DETECTOR_HPP

# include <elib/enumeration/basic_traits.hpp>
# include <elib/aux/integral_constant.hpp>

namespace elib { namespace enumeration
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        template <bool Found, class FieldT>
        struct extracted_field 
        {
            using type = extracted_field;
            using value_type = typename FieldT::value_type;
            
            static constexpr bool found = Found;
            static constexpr value_type value = FieldT::value;
        };
        
        template <bool Found, class FieldT>
        constexpr bool extracted_field<Found, FieldT>::found;
        
        template <bool Found, class FieldT>
        constexpr typename FieldT::value_type extracted_field<Found, FieldT>::value;
        
        ////////////////////////////////////////////////////////////////////////
        template <class Type, template <class> class FieldType, class Default>
        struct field_extractor_impl
        {
            template <class T, class = typename FieldType<T>::type>
            static extracted_field<true, typename FieldType<T>::type> test(int);
            
            template <class>
            static extracted_field<false, Default> test(...);
            
            using type = decltype(test<Type>(0));
        };
        
        
        template <class T, template <class> class FieldType, class Default>
        using field_extractor = typename field_extractor_impl<T, FieldType, Default>::type;
        
# if !defined(ELIB_CONFIG_COVERITY_SCAN)
        // TODO: For some reason EDG's frontend used by coverity scan
        // blows up on the decltype's
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

# else /* ELIB_CONFIG_COVERITY_SCAN */
        template <class T, class Enum = decltype(T::ELIB_ENUM_DEFAULT_VALUE)>
        struct default_value_field : integral_constant<Enum, T::ELIB_ENUM_DEFAULT_VALUE> {};
        
        template <class T, class Enum = decltype(T::ELIB_ENUM_ERROR_VALUE)>
        struct error_value_field : integral_constant<Enum, T::ELIB_ENUM_ERROR_VALUE> {};
            
        template <class T, class Enum = decltype(T::ELIB_ENUM_FIRST_VALUE)>
        struct first_value_field : integral_constant<Enum, T::ELIB_ENUM_FIRST_VALUE> {};
        
        template <class T, class Enum = decltype(T::ELIB_ENUM_LAST_VALUE)>
        struct last_value_field : integral_constant<Enum, T::ELIB_ENUM_LAST_VALUE> {};
        
        template <class T, class Base = bool_<static_cast<bool>(T::ELIB_ENUM_IS_CONTIGIOUS)>>
        struct is_contigious_field : Base {};
            
        template <class T>
        using default_value_field_t = default_value_field<T>;
        
        template <class T>
        using error_value_field_t = error_value_field<T>;
            
        template <class T>
        using first_value_field_t = first_value_field<T>;
        
        template <class T>
        using last_value_field_t = last_value_field<T>;
        
        template <class T>
        using is_contigious_field_t = is_contigious_field<T>;
# endif


        ////////////////////////////////////////////////////////////////////////
        template <class Enum, class From>
        struct traits_detector
        {
        private:
            using bad_enum_t = ELIB_AUTO_INTC(static_cast<Enum>(-1));

            using m_default_value = field_extractor<From,
                                        default_value_field_t, bad_enum_t>;
                                        
            using m_error_value = field_extractor<From,
                                        error_value_field_t, bad_enum_t>;
                                        
            using m_first_value = field_extractor<From,
                                        first_value_field_t, bad_enum_t>;
                                        
            using m_last_value = field_extractor<From,
                                        last_value_field_t, bad_enum_t>;
                                        
            using m_is_contigious = field_extractor<From,
                                        is_contigious_field_t, aux::false_>;
            
        public:
            
            static constexpr bool has_default_value = m_default_value::found;
            static constexpr Enum default_value = m_default_value::value;
            
            static constexpr bool has_error_value = m_error_value::found;
            static constexpr Enum error_value = m_error_value::value;
            
            static constexpr bool has_first_value = m_first_value::found;
            static constexpr Enum first_value = m_first_value::value;
            
            static constexpr bool has_last_value = m_last_value::found;
            static constexpr Enum last_value = m_last_value::value;
            
            static constexpr bool has_is_contigious = m_is_contigious::found;
            static constexpr bool is_contigious = m_is_contigious::value;
            
        };                                                  // struct traits_detector
        
        template <class Enum, class From>
        constexpr const bool traits_detector<Enum, From>::has_default_value;
        
        template <class Enum, class From>
        constexpr const Enum traits_detector<Enum, From>::default_value;
        
        template <class Enum, class From>
        constexpr const bool traits_detector<Enum, From>::has_error_value;
        
        template <class Enum, class From>
        constexpr const Enum traits_detector<Enum, From>::error_value;
        
        template <class Enum, class From>
        constexpr const bool traits_detector<Enum, From>::has_first_value;
        
        template <class Enum, class From>
        constexpr const Enum traits_detector<Enum, From>::first_value;
        
        template <class Enum, class From>
        constexpr const bool traits_detector<Enum, From>::has_last_value;
        
        template <class Enum, class From>
        constexpr const Enum traits_detector<Enum, From>::last_value;
        
        template <class Enum, class From>
        constexpr const bool traits_detector<Enum, From>::has_is_contigious;
        
        template <class Enum, class From>
        constexpr const bool traits_detector<Enum, From>::is_contigious;
        
        template <class Enum>
        using basic_enum_traits_detector = traits_detector<Enum, basic_enum_traits<Enum>>;
        
        template <class Enum>
        using intrusive_traits_detector = traits_detector<Enum, Enum>;
      
    }                                                       // namespace detail
}}                                                          // namespace elib::enumeration
#endif /* ELIB_ENUMERATION_DETAIL_TRAITS_DETECTOR_HPP */