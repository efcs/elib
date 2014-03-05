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
        using to_string_type_valid = aux::is_same< Str, std::string >;
    }                                                       // namespace detail
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    ////////////////////////////////////////////////////////////////////////////
    //
    class bad_enum_cast 
      : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
    ////////////////////////////////////////////////////////////////////////////
    // enum_cast: Enum -> Integral (safe)
    template <
        class To, class From
      , ELIB_ENABLE_IF(aux::is_integral<To>::value
                    && aux::is_enum<From>::value)
    >
    inline bool enum_cast(From v, To & t) noexcept
    {
        t = static_cast<To>(v);
        return true;
    }

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
                    && has_range<To>::value)
    >
    inline bool enum_cast(From v, To & t) noexcept
    {
        if (enumeration::in_range(static_cast<To>(v)))
        {
            t = static_cast<To>(v);
            return true;
        }
        return false;
    }
    
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
    bool enum_cast(From v, To & t) noexcept
    {
        static_assert(has_name_map<From>::value, "must have name map");
        
        auto pos = basic_enum_traits<From>::name_map.find(v);
        if (pos != basic_enum_traits<From>::name_map.end())
        {
            t = pos->second;
            return true;
        }
        return false;
    }
    
    template <
        class To, class From
      , ELIB_ENABLE_IF(aux::is_enum<From>::value 
                    && detail::to_string_type_valid<To>::value
                    && has_name_map<From>::value)
    >
    To enum_cast(From v)
    {
        To s;
        if (!enum_cast<To>(v, s)) throw bad_enum_cast{"bad enum cast"};
        return s;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // enum_cast: String -> Enum
    template<
        class To, class From
      , ELIB_ENABLE_IF(aux::is_enum<To>::value
                    && aux::is_string_type<From>::value
                    && has_name_map<To>::value)
    >
    bool enum_cast(From && v, To & t) noexcept
    {
         for (auto& kv :  basic_enum_traits<To>::name_map)
        {
            if (kv.second == v)
            {
                t = kv.first;
                return true;
            }
        }
        return false;
    }
    
    template<
        class To, class From
      , ELIB_ENABLE_IF(aux::is_enum<To>::value
                    && aux::is_string_type<From>::value
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