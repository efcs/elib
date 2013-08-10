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
#ifndef ELIB_ENUM_TRAITS_H
#define ELIB_ENUM_TRAITS_H

#include "basic_enum_traits.h"

#include <stdexcept>
#include <iterator>
#include <limits>
#include <string>
#include <map>


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

/* bad_enum is a value that:
 *   a) is the numeric max for Enum's underlying type
 *   b) should not be a member of Enum (if it is used) */
template <typename Enum>
constexpr Enum
bad_enum();

/* used to construct iterators for an enum class at a givin position 
 * enum_traits not provided for this */
enum class iter_pos_e {
    begin,
    end
};

/* A iterator class for enumerations */
template <typename Enum>
class enum_iterator {
public:
    /* required typedefs for iterator_traits */
    typedef Enum value_type;
    typedef Enum& reference;
    typedef const Enum& const_reference;
    typedef Enum* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef unsigned difference_type;
    
    /* construct an iterator with the current position at e */
    enum_iterator(Enum e);
    /* construct an iterator with the current position at the
     * begining or end */
    enum_iterator(iter_pos_e place = iter_pos_e::begin);
    
    enum_iterator &
    operator++();
    
    enum_iterator
    operator++(int);
    
    const_reference
    operator*() const;
    
    bool operator==(const enum_iterator & other);
    bool operator!=(const enum_iterator & other);
    
private:
    /* various typedefs used in implementation */
    typedef basic_enum_traits<Enum> basic_traits;
    typedef typename basic_traits::map_type map_type;
    typedef typename map_type::iterator map_iterator;
    typedef typename map_type::const_iterator map_const_iterator;
private:
    /* really we just adapt the maps key-value iterator,
     * so we just implement it using a map iterator */
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
    
    /* underlying type is used for 
     * casting integral values to and from enums */
    typedef typename std::underlying_type<Enum>::type underlying_type;
    
    /* BAD_ENUM is to be used like string::npos or iterator::end()
     * When using safe_enum_cast, BAD_ENUM is returned when a cast fails */
    static constexpr Enum
    BAD_ENUM = bad_enum<Enum>();
    
    /* basic assumption checking */
    static_assert(basic_traits::first_value <= basic_traits::last_value, 
                  "first_value must be <= last_value");
    
    /* default_value may either be a valid member of Enum, or it may be
     * BAD_ENUM so that default_value may be used for uninitalized enums */
    static_assert((basic_traits::default_value >= basic_traits::first_value && 
                   basic_traits::default_value <= basic_traits::last_value) || 
                   basic_traits::default_value == BAD_ENUM,
                  "default value must be >= first_value && <= last_value"
                  "or BAD_ENUM");
    
    /* return the # of members in Enum
     * (really just basic_traits::name_map.size()) */
    static unsigned
    size();
    
    /* check if value of the Enum's underlying_type can
     * safely be casted to Enum */
    static bool
    good(underlying_type val);
    
    /* Same as above, but check a value of type Enum */
    static bool
    good(Enum e);
    
    /* return an iterator for Enum at a given position */
    static iterator
    iterator_at(Enum e);
    
    static iterator
    iterator_at(iter_pos_e pos);
    
    /* basic iteratable methods */
    iterator begin();
    iterator end();
    
    const_iterator cbegin() const;
    const_iterator cend() const;
    
    /* this can be used to verify assumptions about Enum
     * if it returns false, an assumption has failed */
    static bool
    verify_enum_traits();
};


/* cast strings and underlying_types to Enum values */
template <typename Enum>
Enum
enum_cast(const std::string & s);

template <typename Enum>
Enum
enum_cast(typename enum_traits<Enum>::underlying_type x);

/* attempt to cast to Enum, 
 * return BAD_ENUM if casting fails */
template <typename Enum>
Enum
safe_enum_cast(const std::string & s);

template <typename Enum>
Enum
safe_enum_cast(typename enum_traits<Enum>::underlying_type x);

/* return (e == enum_traits<Enum>::BAD_ENUM) 
 * note: this function may only be used with Enum classes
 * that do not contain a member that is equal to BAD_ENUM */
template <typename Enum>
constexpr bool
is_bad_enum(Enum e);

/* Cast Enum values to an std::string or to
 * BASE_ENUM */
template <typename Ret, typename Enum>
Ret
lexical_enum_cast(Enum e);

/* cast to base type */
template <typename Enum>
constexpr typename enum_traits<Enum>::underlying_type
base_enum_cast(Enum e) noexcept;


} /* namespace elib */


/* Include the inline definitions */
#include "elib/detail/_enum_traits.h" 


#endif /* ELIB_ENUM_TRAITS_H */