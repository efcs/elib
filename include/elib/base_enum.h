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
#ifndef ELIB_BASE_ENUM_H
#define ELIB_BASE_ENUM_H

#include <stdexcept>
#include <iterator>
#include <limits>
#include <string>
#include <map>


/* these functions should be implemented for each 
 * enum class */

namespace elib {


class bad_enum_cast : public std::logic_error {
public:
    bad_enum_cast()
        : std::logic_error("bad enum cast")
    { }
    
    bad_enum_cast(const std::string & what)
        : std::logic_error("bad enum cast: " + what)
    { }
};


/* each enumeration must implement this in order
 * to use enum_cast and lexical_enum_cast */
template <typename Enum>
struct basic_enum_traits {
    static constexpr const bool contiguous = false;
    
    static constexpr const Enum default_value = 0;
    static constexpr const Enum first_value = 0;
    static constexpr const Enum last_value = 0;
    
    typedef const std::map<Enum, std::string> map_type;
    static map_type name_map;
};


enum class iter_pos_e {
    begin,
    end
};

/* A iterator class for enumerations */
template <typename Enum>
class enum_iterator {
public:
    typedef Enum value_type;
    typedef Enum& reference;
    typedef Enum* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef unsigned difference_type;
    
    enum_iterator(Enum e);
    enum_iterator(iter_pos_e place = iter_pos_e::begin);
    
    enum_iterator &
    operator++();
    
    enum_iterator
    operator++(int);
    
    Enum operator*();
    
    bool operator==(const enum_iterator & other);
    bool operator!=(const enum_iterator & other);
private:
    typedef basic_enum_traits<Enum> basic_traits;
    typedef typename basic_traits::map_type map_type;
    typedef typename map_type::iterator map_iterator;
    typedef typename map_type::const_iterator map_const_iterator;
private:
    map_const_iterator m_iter;
};


/* Allow for static access to begin and end iterator objects 
 * for an enumeration, as well as its size. This struct should be used
 * to access values in basic_enum_traits */
template <typename Enum>
struct enum_traits : public basic_enum_traits<Enum> {
    static_assert(std::is_enum<Enum>::value, "Enum must be an enumeration");
    
    typedef basic_enum_traits<Enum> basic_traits;
    typedef enum_iterator<Enum> iterator;
    typedef enum_iterator<Enum> const_iterator;
    
    typedef typename std::underlying_type<Enum>::type underlying_type;
    
    static_assert(std::is_integral<underlying_type>::value,
                  "underlying type must be integral");
    
    static constexpr const Enum
    BAD_ENUM = static_cast<Enum>(std::numeric_limits<underlying_type>::max());
    
    
    static_assert(basic_traits::first_value <= basic_traits::last_value, 
                  "first_value must be <= last_value");
    
    static_assert(basic_traits::last_value != BAD_ENUM,
                  "last value cannot be BAD_ENUM");
    
    static_assert((basic_traits::default_value >= basic_traits::first_value && 
                   basic_traits::default_value <= basic_traits::last_value) || 
                   basic_traits::default_value == BAD_ENUM,
                  "default value must be >= first_value && <= last_value"
                  "or BAD_ENUM");
    
    static unsigned
    size();
    
    static bool
    good(underlying_type val);
    
    static bool
    good(Enum e);
    
    static iterator
    iterator_at(Enum e);
    
    static iterator
    iterator_at(iter_pos_e pos);
    
    iterator begin();
    iterator end();
    
    const_iterator cbegin() const;
    const_iterator cend() const;
};

template <typename Enum>
bool
bad_enum(Enum e);

/* cast strings and underlying_types to Enum values */
template <typename Enum>
Enum
enum_cast(const std::string & s);

template <typename Enum>
Enum
enum_cast(typename enum_traits<Enum>::underlying_type x);

template <typename Enum>
Enum
safe_enum_cast(const std::string & s);

template <typename Enum>
Enum
safe_enum_cast(typename enum_traits<Enum>::underlying_type x);

template <typename Enum>
bool
safe_cast_failed(Enum e);

/* Cast Enum values to an std::string or to
 * BASE_ENUM */
template <typename Ret, typename Enum>
Ret
lexical_enum_cast(Enum e);

/* cast to base type */
template <typename Enum>
typename enum_traits<Enum>::underlying_type
base_enum_cast(Enum e);


} /* namespace elib */


/* Include the inline definitions */
#include <elib/detail/_base_enum.h>


#endif /*ELIB_BASE_ENUM_H */