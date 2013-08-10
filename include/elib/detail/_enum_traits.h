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
#ifndef ELIB__ENUM_TRAITS_H
#define ELIB__ENUM_TRAITS_H

#ifndef ELIB_ENUM_TRAITS_H
#   error this file should only be included via enum_traits.h
#endif

namespace elib {
    
    
////////////////////////////////////////////////////////////////////////////////
//                      lexical cast helper declarations                                                                       
////////////////////////////////////////////////////////////////////////////////
    
    
template <typename Ret, typename Enum>
struct lexical_cast_helper;


template <typename Enum>
struct lexical_cast_helper<std::string, Enum>;


template <typename Enum>
struct lexical_cast_helper<typename enum_traits<Enum>::underlying_type, Enum>;
  

////////////////////////////////////////////////////////////////////////////////
//                              enum iterator definition                                                                          
////////////////////////////////////////////////////////////////////////////////


template <typename Enum>
inline
enum_iterator<Enum>::enum_iterator(Enum e)
{
    m_iter = basic_traits::name_map.begin();
    while (m_iter != basic_traits::name_map.end() &&
           m_iter->first != e) {
        ++m_iter;
    }
}

template <typename Enum>
inline
enum_iterator<Enum>::enum_iterator(iter_pos_e pos)
{
    if (pos == iter_pos_e::begin) 
        m_iter = basic_traits::name_map.begin();
    else
        m_iter = basic_traits::name_map.end();
}

    
template <typename Enum>
inline enum_iterator<Enum> &
enum_iterator<Enum>::operator++()
{
    ++m_iter;
    return *this;
}
    
template <typename Enum>
inline enum_iterator<Enum>
enum_iterator<Enum>::operator++(int junk)
{
    //UNUSED
    ((void)junk); 
    
    enum_iterator curr = *this;
    ++m_iter;
    return curr;
}
    
template <typename Enum>
inline typename enum_iterator<Enum>::const_reference
enum_iterator<Enum>::operator*() const
{ 
    return m_iter->first;
}
    
template <typename Enum>
inline bool 
enum_iterator<Enum>::operator==(const enum_iterator & other)
{ 
    return m_iter == other.m_iter; 
}

template <typename Enum>
inline bool 
enum_iterator<Enum>::operator!=(const enum_iterator & other)
{ 
    return m_iter != other.m_iter;
}


////////////////////////////////////////////////////////////////////////////////
//                          enum function definitions & helpers
////////////////////////////////////////////////////////////////////////////////

template <typename Enum>
inline constexpr Enum
bad_enum()
{
    typedef typename std::underlying_type<Enum>::type underlying_type;
    typedef std::numeric_limits<underlying_type> limits;
    
    return static_cast<Enum>(limits::max());
}

template <typename Ret, typename Enum>
struct lexical_cast_helper {
    static Ret
    cast(Enum e);
};


template <typename Enum>
struct lexical_cast_helper<std::string, Enum> {
    inline static std::string
    cast(Enum e)
    {
        typedef enum_traits<Enum> traits;
        
        if (traits::name_map.count(e))
            return traits::name_map.at(e);
        
        throw bad_enum_cast();
    }
};


template <typename Enum>
struct lexical_cast_helper<typename enum_traits<Enum>::underlying_type, Enum> {
    inline static typename enum_traits<Enum>::underlying_type
    cast(Enum e)
    {
        return static_cast<typename enum_traits<Enum>::underlying_type>(e);
    }
};



template <typename Enum>
inline Enum
enum_cast(const std::string & s)
{
    typedef enum_traits<Enum> traits;
    
    for (auto & kv : traits::name_map) {
        if (kv.second == s)
            return kv.first;
    }
    
    throw bad_enum_cast(s);
}


template <typename Enum>
inline Enum
enum_cast(typename enum_traits<Enum>::underlying_type x)
{
    typedef enum_traits<Enum> traits;
    
    Enum test = static_cast<Enum>(x);
    if (traits::good(test))
        return test;
    
    throw bad_enum_cast();
}


template <typename Enum>
inline Enum
safe_enum_cast(const std::string & s)
{
    typedef enum_traits<Enum> traits;
    static_assert(traits::last_value != traits::BAD_ENUM,
                  "safe_enum_cast cannot be called when "
                  "basic_traits<Enum>::BAD_ENUM == enum_traits<Enum>::last_value");
    
    for (auto & kv : traits::name_map) {
        if (kv.second == s)
            return kv.first;
    }
    
    return traits::BAD_ENUM;
}


template <typename Enum>
inline Enum
safe_enum_cast(typename enum_traits<Enum>::underlying_type x)
{
    typedef enum_traits<Enum> traits;
    static_assert(traits::last_value != traits::BAD_ENUM,
                  "safe_enum_cast cannot be called when "
                  "basic_traits<Enum>::BAD_ENUM == enum_traits<Enum>::last_value");
    
    Enum e = static_cast<Enum>(x);
    if (traits::good(e))
        return e;
    
    return traits::BAD_ENUM;
}


template <typename Enum>
inline constexpr bool
is_bad_enum(Enum e)
{
    typedef enum_traits<Enum> traits;
    
    static_assert(traits::last_value != traits::BAD_ENUM,
                  "is_bad_enum cannot be used when " 
                  "basic_enum_traits<Enum>::last_value = BAD_ENUM");
    
    return (traits::BAD_ENUM == e);
}

/* Ret is one of std::string, or the underlying_type */
template <typename Ret, typename Enum>
inline Ret
lexical_enum_cast(Enum e)
{
    return lexical_cast_helper<Ret, Enum>::cast(e);
}

template <typename Enum>
inline constexpr typename enum_traits<Enum>::underlying_type
base_enum_cast(Enum e) noexcept
{
    typedef enum_traits<Enum> traits;
    
    return static_cast<typename traits::underlying_type>(e);
}


////////////////////////////////////////////////////////////////////////////////
//                          enum_traits definition
////////////////////////////////////////////////////////////////////////////////

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
             basic_traits::default_value == BAD_ENUM);
    
    ret &= (size() != 0);
    ret &= (size() == basic_traits::name_map.size());
    
    Enum enum_val = basic_traits::first_value;
    ret &= (basic_traits::name_map.count(enum_val) == 1);
    
    enum_val = basic_traits::last_value;
    ret &= (basic_traits::name_map.count(enum_val) == 1);
    
    enum_val = basic_traits::default_value;
    ret &= (enum_val == BAD_ENUM || 
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
            
        } catch (elib::bad_enum_cast & ex) {
            ret = false;
            break;
        }
    }
    
    for (auto & kv : basic_traits::name_map) {
        ret &= (basic_traits::name_map.count(kv.first) == 1);
    }
    
    return ret;
}


} /* namespace elib */
#endif /* ELIB__ENUM_TRAITS_H */