#ifndef ELIB_ENUMERATION_DETAIL_META_TRAITS_HPP
#define ELIB_ENUMERATION_DETAIL_META_TRAITS_HPP

# include <elib/enumeration/detail/enum_fields.hpp>
# include <elib/enumeration/basic_enum_traits.hpp>
# include <elib/aux.hpp>



namespace elib { namespace enumeration
{
    namespace detail
    {
        template <class Enum, class From>
        struct meta_traits
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
                                        
            using m_is_bitmask = field_extractor<From,
                                        is_bitmask_field_t, aux::false_>;
                                        
            using m_is_arithmetic = field_extractor<From,
                                        is_arithmetic_field_t, aux::false_>;
                                    
            using m_is_logical = field_extractor<From,
                                        is_logical_field_t, aux::false_>;
                                        
            using m_is_mixed_comparible = field_extractor<From, 
                                    is_mixed_comparible_field_t, aux::false_>;
            
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
            
            static constexpr bool has_is_bitmask = m_is_bitmask::found;
            static constexpr bool is_bitmask = m_is_bitmask::value;
            
            static constexpr bool has_is_arithmetic = m_is_arithmetic::found;
            static constexpr bool is_arithmetic = m_is_arithmetic::value;
            
            static constexpr bool has_is_logical = m_is_logical::found;
            static constexpr bool is_logical = m_is_logical::value;
            
            static constexpr bool has_is_mixed_comparible = 
                m_is_mixed_comparible::found;
            static constexpr bool is_mixed_comparible = 
                m_is_mixed_comparible::value;
            
        };                                                  // struct meta_traits
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::has_default_value;
        
        template <class Enum, class From>
        constexpr const Enum meta_traits<Enum, From>::default_value;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::has_error_value;
        
        template <class Enum, class From>
        constexpr const Enum meta_traits<Enum, From>::error_value;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::has_first_value;
        
        template <class Enum, class From>
        constexpr const Enum meta_traits<Enum, From>::first_value;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::has_last_value;
        
        template <class Enum, class From>
        constexpr const Enum meta_traits<Enum, From>::last_value;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::has_is_contigious;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::is_contigious;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::has_is_bitmask;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::is_bitmask;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::has_is_arithmetic;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::is_arithmetic;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::has_is_logical;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::is_logical;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::has_is_mixed_comparible;
        
        template <class Enum, class From>
        constexpr const bool meta_traits<Enum, From>::is_mixed_comparible;
        
        
        template <class Enum>
        using meta_basic_enum_traits = meta_traits<Enum, basic_enum_traits<Enum>>;
        
        template <class Enum>
        using meta_intrusive_traits = meta_traits<Enum, Enum>;
      
    }                                                       // namespace detail
}}                                                          // namespace elib::enumeration
#endif /* ELIB_ENUMERATION_DETAIL_META_TRAITS_HPP */