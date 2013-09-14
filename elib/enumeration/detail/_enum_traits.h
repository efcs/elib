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
#ifndef ELIB_ENUMERATION__ENUM_TRAITS_H
#define ELIB_ENUMERATION__ENUM_TRAITS_H

#ifndef ELIB_ENUMERATION_ENUM_TRAITS_H
#   error this file should only be included via enum_traits.h
#endif

namespace elib {
namespace enumeration {

////////////////////////////////////////////////////////////////////////////////
//                          enum function definitions & helpers
////////////////////////////////////////////////////////////////////////////////


template <typename Enum>
inline constexpr Enum
default_enum()
{
    typedef enum_traits<Enum> traits;
    return traits::default_value;
}


template <typename Enum>
inline bool
is_valid_enum(Enum e)
{
    typedef basic_enum_traits<Enum> traits;
    
    if (is_contiguous<Enum>())
        return (e >= traits::first_value && e <= traits::last_value);
    
    return (traits::name_map.contains(e));
}

template <typename Enum>
inline bool
is_contiguous()
{
    typedef basic_enum_traits<Enum> traits;
    unsigned diff = base_enum_cast(traits::last_value) - 
                    base_enum_cast(traits::first_value) + 1;
                    
    return (diff == traits::name_map.size());
}



////////////////////////////////////////////////////////////////////////////////
//                          enum_traits definition
////////////////////////////////////////////////////////////////////////////////

template <typename Enum>
constexpr Enum
enum_traits<Enum>::NPOS_ENUM;

template <typename Enum>
inline unsigned
enum_traits<Enum>::size()
{ 
    return basic_traits::name_map.size(); 
}

template <typename Enum>
inline bool
enum_traits<Enum>::good(underlying_type val)
{
    Enum e = static_cast<Enum>(val);
    return good(e);
}

template <typename Enum>
inline bool
enum_traits<Enum>::good(Enum e)
{
    return (basic_traits::name_map.count(e) == 1);
}

template <typename Enum>
inline typename enum_traits<Enum>::iterator
enum_traits<Enum>::iterator_at(Enum e) 
{ return iterator(e); }

template <typename Enum>
inline typename enum_traits<Enum>::iterator
enum_traits<Enum>::iterator_at(iter_pos_e pos)
{ return iterator(pos); }

template <typename Enum>
inline typename enum_traits<Enum>::iterator
enum_traits<Enum>::begin()
{
    return iterator(iter_pos_e::begin);
}

template <typename Enum>    
inline typename enum_traits<Enum>::iterator 
enum_traits<Enum>::end()
{
    return iterator(iter_pos_e::end);
}
    
template <typename Enum>    
inline typename enum_traits<Enum>::const_iterator
enum_traits<Enum>::cbegin() const
{
    return const_iterator(basic_traits::first_value);
}
    
template <typename Enum>
inline typename enum_traits<Enum>::const_iterator
enum_traits<Enum>::cend() const
{
    return const_iterator(iter_pos_e::end);
}

template <typename Enum>
inline bool
enum_traits<Enum>::verify_enum_traits()
{
    bool ret = true;
    
    ret &= (basic_traits::last_value >= basic_traits::first_value); 
    
    ret &= ( (basic_traits::default_value >= basic_traits::first_value &&
              basic_traits::default_value <= basic_traits::last_value) ||
             basic_traits::default_value == NPOS_ENUM);
    
    ret &= (size() != 0);
    ret &= (size() == basic_traits::name_map.size());
    
    Enum enum_val = basic_traits::first_value;
    ret &= (basic_traits::name_map.count(enum_val) == 1);
    
    enum_val = basic_traits::last_value;
    ret &= (basic_traits::name_map.count(enum_val) == 1);
    
    enum_val = basic_traits::default_value;
    ret &= (enum_val == NPOS_ENUM || 
            basic_traits::name_map.count(enum_val) == 1);
    
    
    for (auto e : enum_traits<Enum>() ) {
        try {
            std::string s = lexical_enum_cast<std::string>(e);
            Enum tmp_e = enum_cast<Enum>(s);
            ret &= (tmp_e == e);
            
            underlying_type b = lexical_enum_cast<underlying_type>(e);
            tmp_e = enum_cast<Enum>(b);
            ret &= (tmp_e == e);
            
            ret &= (basic_traits::name_map.count(e) == 1);
            
        } catch (elib::enumeration::bad_enum_cast & ex) {
            ret = false;
            break;
        }
    }
    
    for (auto & kv : basic_traits::name_map) {
        ret &= (basic_traits::name_map.count(kv.first) == 1);
    }
    
    return ret;
}


} /* namespace enumeration */
} /* namespace elib */
#endif /* ELIB_ENUMERATION__ENUM_TRAITS_H */