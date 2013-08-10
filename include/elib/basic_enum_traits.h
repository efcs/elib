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
    
    
/* each enumeration must implement this in order
 * to use anything in the enum_traits header */
template <typename Enum>
struct basic_enum_traits {
    /* Currently unused, definition not required */
    static constexpr bool contiguous = false;
    
    /* default_value may be a valid member of Enum
     * or it may be the value of bad_enum<Enum>() */
    static constexpr Enum default_value = 0;
    
    /* the lowest value member of Enum */
    static constexpr Enum first_value = 0;
    
    /* the highest value member of Enum */
    static constexpr Enum last_value = 0;
    
    /* name_map is used for checking the validity of casts
     * iterating over keys (enum_iterator<Enum>) and
     * casting to and from std::string */
    typedef const std::map<Enum, std::string> map_type;
    static map_type name_map;
};
    
    
} /* namespace elib */
#endif /* ELIB_BASIC_ENUM_TRAITS_H */