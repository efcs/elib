#ifndef ELIB_ENUMERATION_ENUM_CAST_HPP
#define ELIB_ENUMERATION_ENUM_CAST_HPP

# include <elib/enumeration/enum_helper.hpp>
# include <elib/enumeration/enum_traits.hpp>
# include <elib/aux.hpp>
# include <string>
# include <stdexcept>

namespace elib { namespace enumeration
{
    namespace detail
    {
        template <class Str>
        using from_string_type_valid =
            aux::or_<
                aux::is_same< aux::decay_uncvref<Str>, const char*>
              , aux::is_same< aux::decay_uncvref<Str>, std::string>
            >;
        
        template <class Str>
        using to_string_type_valid = aux::is_same< Str, std::string >;
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class bad_enum_cast 
      : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    // enum_cast: Enum -> Integral
    template <
        class To, class From
      , ELIB_ENABLE_IF(aux::is_integral<To>::value
                    && aux::is_enum<From>::value)
    >
    constexpr To enum_cast(From v) noexcept
    {
        return static_cast<To>(v);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // enum_cast: Integral -> Enum, Enum -> Enum
    template <
        class To, class From
      , ELIB_ENABLE_IF(aux::is_enum<To>::value 
                    && aux::is_integral_enum<From>::value
                    && has_constexpr_range<To>::value)
    >
    constexpr To enum_cast(From v)
    {
        return (in_range(static_cast<To>(v)) 
                    ? static_cast<To>(v)
                    : throw bad_enum_cast{"bad enum cast"} );
    }
    
    
    template <
        class To, class From
      , ELIB_ENABLE_IF(aux::is_enum<To>::value 
                    && aux::is_integral_enum<From>::value
                    && has_range<To>::value 
                    && !has_constexpr_range<To>::value)
    >
    To enum_cast(From v)
    {
        return ( in_range(static_cast<To>(v))
                    ? static_cast<To>(v)
                    : throw bad_enum_cast{"bad enum cast"} );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // enum_cast: Enum -> String
    template <
        class To, class From
      , ELIB_ENABLE_IF(aux::is_enum<From>::value 
                    && detail::to_string_type_valid<To>::value
                    && has_name_map<From>::value)
    >
    To enum_cast(From v)
    {
        static_assert(has_name_map<From>::value, "must have name map");
        
        auto pos = basic_enum_traits<From>::name_map.find(v);
        if (pos != basic_enum_traits<From>::name_map.end())
            return pos->second;
        throw bad_enum_cast{"bad enum cast"};
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // enum_cast: String -> Enum
    template<
        class To, class From
      , ELIB_ENABLE_IF(aux::is_enum<To>::value
                    && detail::from_string_type_valid<From>::value
                    && has_name_map<To>::value)
    >
    To enum_cast(From && v)
    {
        for (auto& kv :  basic_enum_traits<To>::name_map)
        {
            if (kv.second == v) return kv.first;
        }
        throw bad_enum_cast{"bad_enum_cast"};
    }

}}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_CAST_HPP */