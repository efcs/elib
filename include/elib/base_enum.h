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
#include <string>
#include <map>


/* these functions should be implemented for each 
 * enum class */

namespace elib {

    
/* Another way to define a enumeration class,
 * this macro ensures proper subclassing of BASE_ENUM */
#define ELIB_ENUM(TypeName) \
    enum class TypeName : BASE_ENUM

    
/* all enum classes should derived from BASE_ENUM
 * so that they can be be used with casting functions and iterators */
typedef unsigned BASE_ENUM;


class bad_enum_cast : public std::logic_error {
public:
    bad_enum_cast()
        : std::logic_error("bad enum cast")
    { }
    
    bad_enum_cast(const std::string & what)
        : std::logic_error("bad enum cast: " + what)
    { }
};


/* get the size of an enum, for use in defining size in enum_traits */
template <typename Enum>
constexpr unsigned
enum_size(Enum first, Enum last);


template <typename Enum>
unsigned
enum_size();


/* cast strings and BASE_ENUM to Enum values */
template <typename Enum>
Enum
enum_cast(const std::string & s);


template <typename Enum>
Enum
enum_cast(BASE_ENUM x);


/* Cast Enum values to an std::string or to
 * BASE_ENUM */
template <typename Ret, typename Enum>
Ret
lexical_enum_cast(Enum e);


/* A iterator class for enumerations */
template <typename Enum>
class enum_iterator {
public:
    typedef Enum value_type;
    typedef Enum& reference;
    typedef Enum* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef unsigned difference_type;
    
    constexpr
    enum_iterator(Enum e);
    
    enum_iterator
    operator++();
    
    enum_iterator
    operator++(int);
    
    reference operator*();
    pointer operator->();
    
    bool operator==(const enum_iterator & other);
    bool operator!=(const enum_iterator & other);
private:
    Enum m_e;
};


/* each enumeration must implement this in order
 * to use enum_cast and lexical_enum_cast */
template <typename Enum>
struct basic_enum_traits {
    static constexpr const Enum none_value = 0;
    static constexpr const Enum default_value = 0;
    static constexpr const Enum first_value = 0;
    static constexpr const Enum last_value = 0;
    
    typedef const std::map<Enum, std::string> map_type;
    static map_type name_map;
};


/* Allow for static access to begin and end iterator objects 
 * for an enumeration, as well as its size. This struct should be used
 * to access values in basic_enum_traits */
template <typename Enum>
struct enum_traits : public basic_enum_traits<Enum> {
    typedef basic_enum_traits<Enum> basic_traits;
    
    static constexpr const unsigned
    size = enum_size(basic_traits::first_value, basic_traits::last_value);
    
    typedef enum_iterator<Enum> iterator;
    typedef enum_iterator<Enum> const_iterator;
    
    static const iterator begin;
    static const iterator end;
    
    static const const_iterator cbegin;
    static const const_iterator cend;
};


/* Allow for enums to be iterated over using for each loops
 *     for (auto i : enum_iter<Enum>())  */
template <typename Enum>
class enum_iter {
public:
    typedef enum_iterator<Enum> iterator;
    typedef enum_iterator<Enum> const_iterator;
    typedef enum_traits<Enum> traits;
    
    iterator begin();
    iterator end();
    
    const_iterator cbegin() const;
    const_iterator cend() const;
};


} /* namespace elib */


/* Include the inline definitions */
#include <elib/detail/_base_enum.h>


#endif /*ELIB_BASE_ENUM_H */