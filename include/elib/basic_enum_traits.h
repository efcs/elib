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
#ifndef ELIB_BASIC_ENUM_TRAITS_H
#define ELIB_BASIC_ENUM_TRAITS_H

#include <string>
#include <map>

namespace elib {
    
    
namespace detail {
    constexpr decltype(nullptr) BAD_ENUM_VALUE = nullptr;
    typedef decltype(BAD_ENUM_VALUE) BAD_ENUM_TYPE;
    
} /* namespace detail */

    
    
/* each enumeration must implement this in order
 * to use anything in the enum_traits header 
 * 
 * NOTE: for this definition BAD_ENUM_TYPE has
 *       been substituted wherever Enum should occur,
 *       this is done so we can use BAD_ENUM_TYPE to see
 *       if there is a definition for basic_enum_traits<Type>
 * 
 * the required fields for use of enum_traits are:
 *     static constexpr Enum default_value;
 *     static constexpr Enum first_value;
 *     static constexpr Enum last_value;
 * 
 *      typedef const std::map<Enum, std::string> map_type;
 *      static map_type name_map */
template <typename Enum>
struct basic_enum_traits {
    /* Currently unused, definition not required */
    static constexpr bool contiguous = false;
    
    /* default_value may be a valid member of Enum
     * or it may be the value of bad_enum<Enum>() */
    static constexpr detail::BAD_ENUM_TYPE default_value = 
                                    detail::BAD_ENUM_VALUE;
    
    /* the lowest value member of Enum */
    static constexpr detail::BAD_ENUM_TYPE first_value =
                                    detail::BAD_ENUM_VALUE;
    
                                    
    /* the highest value member of Enum */
    static constexpr detail::BAD_ENUM_TYPE last_value =
                                        detail::BAD_ENUM_VALUE;
    
    /* name_map is used for checking the validity of casts
     * iterating over keys (enum_iterator<Enum>) and
     * casting to and from std::string 
     * 
     * NOTE: the typedef is unneeded, and so is the const */
    typedef const std::map<detail::BAD_ENUM_TYPE, std::string> map_type;
    static map_type name_map;
};
    
    
} /* namespace elib */
#endif /* ELIB_BASIC_ENUM_TRAITS_H */