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
#ifndef ELIB_UTIL_BASEENUM_H
#define ELIB_UTIL_BASEENUM_H

#include <stdexcept>
#include <string>
#include <map>


/* these functions should be implemented for each 
 * enum class */

namespace elib {

/* all enum classes should derived from BASE_ENUM
 * so that they can be forward declared properly */ 
typedef unsigned BASE_ENUM;


class bad_enum_cast : public std::logic_error {
public:
    bad_enum_cast()
        : std::logic_error("bad_enum_cast")
    { }
    
    bad_enum_cast(const std::string & what)
        : std::logic_error("bad enum cast: " + what)
    { }
};



/* get the size of an enum, for use in defining size in enum_traits */
template <typename Enum>
inline constexpr unsigned
enum_size(Enum f, Enum l)
{
    return static_cast<BASE_ENUM>(l) - static_cast<BASE_ENUM>(f) + 1;
}


/* each enumeration must implement this in order
 * to use enum_cast and lexical_enum_cast */
template <typename Enum>
struct enum_traits {
    static constexpr Enum none_value = 0;
    static constexpr Enum default_value = 0;
    static constexpr Enum first_value = 0;
    static constexpr Enum last_value = 0;
    static constexpr unsigned size = 0;
    
    typedef const std::map<Enum, std::string> map_type;
    static map_type name_map;
};


template <typename Ret, typename Enum>
struct lexical_cast_helper {
    static Ret
    cast(Enum e);
};


template <typename Enum>
struct lexical_cast_helper<std::string, Enum> {
    static std::string
    cast(Enum e)
    {
        typedef enum_traits<Enum> traits;
        
        if (traits::name_map.count(e))
            return traits::name_map.at(e);
        
        throw bad_enum_cast();
    }
};


template <typename Enum>
struct lexical_cast_helper<BASE_ENUM, Enum> {
    static BASE_ENUM
    cast(Enum e)
    {
        try {
            return static_cast<BASE_ENUM>(e);
        } catch (...) {
            throw bad_enum_cast();
        }
    }
};


template <typename Enum>
inline unsigned
enum_size()
{
    return enum_traits<Enum>::size;
}
    
    
template <typename Enum>
inline Enum
enum_cast(const std::string & s)
{
    typedef enum_traits<Enum> traits;
    
    for (auto it=traits::name_map.begin(); 
         it != traits::name_map.end(); ++it) {
        
        if (it->second == s)
            return it->first;
    }
    
    throw bad_enum_cast(s);
}


template <typename Enum>
inline Enum
enum_cast(BASE_ENUM x)
{
    typedef enum_traits<Enum> traits;
    
    Enum test = static_cast<Enum>(x);
    if (test >= traits::first_value && test <= traits::last_value)
        return test;
    
    throw bad_enum_cast();
}


/* Ret is one of BASE_ENUM, std::string */
template <typename Ret, typename Enum>
inline Ret
lexical_enum_cast(Enum e)
{
    return lexical_cast_helper<Ret, Enum>::cast(e);
}





} /* namespace elib */
#endif /* UTIL_BASEENUM_H */
