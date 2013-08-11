#ifndef ELIB_ENUM_CAST_H
#define ELIB_ENUM_CAST_H

#include "basic_enum_traits.h"

#include <stdexcept>
#include <string>
#include <type_traits>

namespace elib {
    
    
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
template <typename Enum>
Enum
enum_cast(const std::string & s);

template <typename Enum>
Enum
enum_cast(typename std::underlying_type<Enum>::type x);

/* these versions are nothrow
 * on success they return true, and write to dest,
 * otherwise dest is ignored and false is return */
template <typename Enum>
bool
enum_cast(const std::string & s, Enum & dest);

template <typename Enum>
bool
enum_cast(typename std::underlying_type<Enum>::type x, Enum & dest);


/* Cast Enum values to std::string or the underlying_type */
template <typename Ret, typename Enum>
Ret
lexical_enum_cast(Enum e);

/* cast to base type,
 * may be used without defining basic_enum_traits */
template <typename Enum>
constexpr typename std::underlying_type<Enum>::type
base_enum_cast(Enum e) noexcept;


    
} /* namespace elib */


#include "detail/_enum_cast.h"

#endif /* ELIB_ENUM_CAST_H */