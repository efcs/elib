#ifndef ELIB__ENUM_CAST_H
#define ELIB__ENUM_CAST_H

#ifndef ELIB_ENUM_CAST_H
#   error do not include this file directly
#endif

#include <utility>
#include <type_traits>


namespace elib {
namespace detail {
////////////////////////////////////////////////////////////////////////////////
//                     lexical cast helpers                                                                  
////////////////////////////////////////////////////////////////////////////////

    
template <typename Ret, typename Enum>
struct lexical_cast_helper;


template <typename Enum>
struct lexical_cast_helper<std::string, Enum>;


template <typename Enum>
struct lexical_cast_helper<typename std::underlying_type<Enum>::type, Enum>;


template <typename Ret, typename Enum>
struct lexical_cast_helper {
    static Ret
    cast(Enum e);
};


template <typename Enum>
struct lexical_cast_helper<std::string, Enum> {
    inline static std::string
    cast(Enum e)
    {
        typedef basic_enum_traits<Enum> traits;
        
        if (traits::name_map.count(e))
            return traits::name_map.at(e);
        
        throw bad_enum_cast();
    }
};


template <typename Enum>
struct lexical_cast_helper<typename std::underlying_type<Enum>::type, Enum> {
    inline static typename std::underlying_type<Enum>::type
    cast(Enum e)
    {
        typedef typename std::underlying_type<Enum>::type under_type;
        return static_cast<under_type>(e);
    }
};


////////////////////////////////////////////////////////////////////////////////
//                         enum_cast helpers                                                 
////////////////////////////////////////////////////////////////////////////////


template <typename Enum, typename From>
struct enum_cast_helper;

template <typename Enum>
struct enum_cast_helper<Enum, std::string>;

template <typename Enum>
struct enum_cast_helper<Enum, typename std::underlying_type<Enum>::type>;

template <typename Enum>
struct enum_cast_helper<Enum, std::string> {
    inline static bool
    cast(const std::string & s, Enum & dest)
    {
        typedef basic_enum_traits<Enum> traits;
    
        for (auto & kv : traits::name_map) {
            if (kv.second == s) {
                dest = kv.first;
                return true;
            }
        }
    
        return false;
    }
};

template <typename Enum>
struct enum_cast_helper<Enum, typename std::underlying_type<Enum>::type> {
    typedef typename std::underlying_type<Enum>::type underlying_type;
    
    inline static bool
    cast(const underlying_type & v, Enum & dest)
    {
        typedef basic_enum_traits<Enum> traits;
    
        Enum test = static_cast<Enum>(v);
        if (traits::name_map.count(test)) {
            dest = test;
            return true;
        }
    
        return false;
    }
};

} /* namespace detail */

////////////////////////////////////////////////////////////////////////////////
//                              enum_cast definitions                                             
////////////////////////////////////////////////////////////////////////////////


template <typename Enum, typename From>
inline Enum
enum_cast(From&& f)
{
    Enum dest;
    if (! detail::enum_cast_helper<Enum, 
                                   typename std::decay<From>::type
                                  >::cast(std::forward<From>(f), dest)) {
        throw bad_enum_cast();
    }
    return dest;
}

template <typename Enum, typename From>
inline bool
enum_cast(From&& f, Enum & dest)
{
    return detail::enum_cast_helper<Enum, 
                                    typename std::decay<From>::type
                                   >::cast(std::forward<From>(f), dest);
}


template <typename Enum>
inline Enum
enum_cast_string(const std::string & s)
{
    return enum_cast<Enum>(s);
}

template <typename Enum>
inline Enum
enum_cast_base(typename std::underlying_type<Enum>::type v)
{
    return enum_cast<Enum>(v);
}

/* Ret is one of std::string, or the underlying_type */
template <typename Ret, typename Enum>
inline Ret
lexical_enum_cast(Enum e)
{
    return detail::lexical_cast_helper<Ret, Enum>::cast(e);
}

template <typename Enum>
inline constexpr typename std::underlying_type<Enum>::type
base_enum_cast(Enum e) noexcept
{
    typedef typename std::underlying_type<Enum>::type under_type;
    return static_cast<under_type>(e);
}

} /* namespace elib */
#endif /* ELIB__ENUM_CAST_H */
