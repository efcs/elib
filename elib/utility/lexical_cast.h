/* 
 * Copyright (C) 2013  Eric Fiselier
 * 
 * This file is part of elib.
 *
 * elib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * elib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elib.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ELIB_LEXICAL_CAST_H
#define ELIB_LEXICAL_CAST_H

#include <stdexcept>
#include <string>
#include <type_traits>

namespace elib {
    
    
/* bad_cast error for lexical casts */
class bad_lexical_cast : public std::runtime_error {
public:
    inline
    bad_lexical_cast()
        : std::runtime_error("bad lexical cast")
    { }
};


/* static type-traits style struct to
 * check if a type is convertible using a lexical cast */
template <typename T>
struct is_lexical {
    static constexpr bool value = 
        std::is_integral<T>::value ||
        std::is_floating_point<T>::value;
};

/* specializations needed for strings
 *  C strings can only be used as the source type
 * in a lexical cast, so is_lexical is allowed to fail */
template <>
struct is_lexical<std::string>
{
    static constexpr bool value = true;
};

/* cast one lexical type to another, generally either to or from a string 
 * ex: string -> float
 *     bool -> string
 *     int -> string
 *     string -> bool */
template <typename ToType, typename FromType>
ToType
lexical_cast(const FromType & from);

    
} /* namespace elib */


#include "detail/_lexical_cast.h"


#endif /* ELIB_LEXICAL_CAST_H */