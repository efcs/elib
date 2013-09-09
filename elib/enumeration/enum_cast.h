#ifndef ELIB_ENUMERATION_ENUM_CAST_H
#define ELIB_ENUMERATION_ENUM_CAST_H

#include <elib/enumeration/basic_enum_traits.h>

#include <stdexcept>
#include <string>
#include <type_traits>
#include <functional>

namespace elib {
namespace enumeration {
    
    
/* the exception thrown when any of the non-safe casts fail */
class bad_enum_cast : public std::logic_error {
public:
    bad_enum_cast()
        : std::logic_error("bad enum cast")
    { }
    
    bad_enum_cast(const std::string & what)
        : std::logic_error("bad enum cast: " + what)
    { }
};


/* cast strings and underlying_types to Enum values */
template <typename Enum, typename From>
Enum
enum_cast(From&& from);

/* these versions are nothrow
 * on success they return true, and write to dest,
 * otherwise dest is ignored and false is return */
template <typename Enum, typename From>
bool
enum_cast(From&& from, Enum & dest);

/* since enum cast is overloaded, use this to access enum_cast 
 * via non-overloaded methods */
template <typename Enum>
Enum
enum_cast_string(const std::string & s);

template <typename Enum>
Enum
enum_cast_base(typename std::underlying_type<Enum>::type v);


/* Cast Enum values to std::string or the underlying_type */
template <typename Ret, typename Enum>
Ret
lexical_enum_cast(Enum e);

/* cast to base type,
 * may be used without defining basic_enum_traits */
template <typename Enum>
constexpr typename std::underlying_type<Enum>::type
base_enum_cast(Enum e) noexcept;


template <typename T>
using base_t = typename std::underlying_type<T>::type;

    
} /* namespace enumeration */
} /* namespace elib */


#include "detail/_enum_cast.h"


#endif /* ELIB_ENUMERATION_ENUM_CAST_H */