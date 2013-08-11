#ifndef ELIB__ENUM_CAST_H
#define ELIB__ENUM_CAST_H

#ifndef ELIB_ENUM_CAST_H
#   error do not include this file directly
#endif



namespace elib {
namespace detail {
////////////////////////////////////////////////////////////////////////////////
//                      lexical cast helpers                                                                  
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

} /* namespace detail */

////////////////////////////////////////////////////////////////////////////////
//                              enum_cast definitions                                             
////////////////////////////////////////////////////////////////////////////////

template <typename Enum>
inline Enum
enum_cast(const std::string & s)
{
    typedef basic_enum_traits<Enum> traits;
    
    for (auto & kv : traits::name_map) {
        if (kv.second == s)
            return kv.first;
    }
    
    throw bad_enum_cast(s);
}


template <typename Enum>
inline Enum
enum_cast(typename std::underlying_type<Enum>::type x)
{
    typedef basic_enum_traits<Enum> traits;
    
    Enum test = static_cast<Enum>(x);
    if (traits::name_map.count(test))
        return test;
    
    throw bad_enum_cast();
}


template <typename Enum>
bool
enum_cast(const std::string & s, Enum & dest)
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

template <typename Enum>
bool
enum_cast(typename std::underlying_type<Enum>::type x, Enum & dest)
{
    typedef basic_enum_traits<Enum> traits;
    
    Enum test = static_cast<Enum>(x);
    if (traits::name_map.count(test)) {
        dest = test;
        return true;
    }
    
    return false;
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
