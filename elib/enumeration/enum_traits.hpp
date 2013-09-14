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
#ifndef ELIB_ENUMERATION_ENUM_TRAITS_HPP
#define ELIB_ENUMERATION_ENUM_TRAITS_HPP

#include <elib/enumeration/basic_enum_traits.hpp>
#include <elib/enumeration/enum.hpp>
#include <elib/enumeration/enum_cast.hpp>

#include <string>
#include <type_traits>
#include <iterator>
#include <cstddef>


namespace elib {
namespace enumeration {



/* Allow for static access to begin and end iterator objects 
 * for an enumeration, as well as its size. This struct should be used
 * to access values in basic_enum_traits */
template <typename Enum>
struct enum_traits : public basic_enum_traits<Enum> {
public:
    static_assert(std::is_enum<Enum>::value, "Enum must be an enumeration");
    
    typedef Enum enum_type;
    typedef basic_enum_traits<Enum> basic_traits;
     
    /* check values is basic_traits */
    static_assert(basic_traits::first_value <= basic_traits::last_value, 
                  "first_value must be <= last_value");
    
    /* default_value may either be a valid member of Enum, or it may be
     * BAD_ENUM so that default_value may be used for uninitalized enums */
    static_assert((basic_traits::default_value >= basic_traits::first_value && 
                   basic_traits::default_value <= basic_traits::last_value) 
                  || basic_traits::default_value == npos_enum<Enum>(),
                  "default value must be >= first_value && <= last_value"
                  "or NPOS_ENUM");
    
    /* underlying type is used for 
     * casting integral values to and from enums */
    typedef typename std::underlying_type<Enum>::type underlying_type;
    
    /* NPOS_ENUM is to be used like string::npos or iterator::end()
     * When using safe_enum_cast, NPOS_ENUM is returned when a cast fails */
    static constexpr Enum
    NPOS_ENUM = npos_enum<Enum>();
    
    /* return the # of members in Enum
     * (really just basic_traits::name_map.size()) */
    static unsigned
    size()
    {
        return basic_traits::name_map.size();
    }
    
    /* check if value of the Enum's underlying_type can
     * safely be casted to Enum */
    static bool
    good(underlying_type val)
    {
        Enum e = static_cast<Enum>(val);
        return good(e);
    }
    
    /* Same as above, but check a value of type Enum */
    static bool
    good(Enum e)
    {
        return (basic_traits::name_map.count(e) != 0);
    }
    
    class iterator;
    typedef iterator const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    
    /* return an iterator for Enum at a given position */
    static iterator
    iterator_at(Enum e)
    {
        iterator it{};
        it.m_iter = basic_traits::name_map.begin();
        iterator end_it{};
        while (it != end_it && *it != e)
            ++it;
        
        return it;
    }
    
    static iterator
    sbegin()
    {
        iterator it{};
        it.m_iter = basic_traits::name_map.begin();
        return it;
    }
    
    static iterator
    send()
    {
        iterator it{};
        it.m_iter = basic_traits::name_map.end();
        return it;
    }
    
    /* basic iteratable methods */
    iterator 
    begin() const
    {
        return sbegin();
    }
    
    iterator 
    end() const
    {
        return send();
    }
    
    const_iterator
    cbegin() const
    {
        return sbegin();
    }
    
    const_iterator
    cend() const
    {
        return send();
    }
    
    /* this can be used to verify assumptions about Enum
     * if it returns false, an assumption has failed */
    static bool
    verify_enum_traits();
};


template <typename Enum>
constexpr Enum
enum_traits<Enum>::NPOS_ENUM;


////////////////////////////////////////////////////////////////////////////////
//                        enum_traits::iterator                                                  
////////////////////////////////////////////////////////////////////////////////

template <typename EnumT>
class enum_traits<EnumT>::iterator : 
    public std::iterator<std::bidirectional_iterator_tag, const EnumT> {
    
    friend class enum_traits<EnumT>;
    typedef enum_traits<EnumT> traits;
    typedef decltype(basic_enum_traits<EnumT>::name_map) map_type;
    typedef typename map_type::const_iterator iterator_type;

public:
    iterator() = default;
    
    iterator(const iterator&) = default;
    iterator(iterator&&) = default;
    
    ~iterator() = default;
    
    iterator&
    operator=(const iterator&) = default;
    
    iterator&
    operator=(iterator&&) = default;
    
    const EnumT&
    operator*() const
    { return m_iter->first; }
    
    const EnumT*
    operator->() const
    { return &(m_iter->first); }
    
    iterator&
    operator++()
    {
        ++m_iter;
        return *this;
    }
    
    iterator
    operator++(int)
    {
        iterator tmp{*this};
        ++m_iter;
        return tmp;
    }
    
    iterator&
    operator--()
    {
        --m_iter;
        return *this;
    }
    
    iterator
    operator--(int)
    {
        iterator tmp{*this};
        --m_iter;
        return tmp;
    }
    
    bool
    operator==(const iterator& other) const
    {
        return (m_iter == other.m_iter);
    }
    
    bool
    operator!=(const iterator& other) const
    {
        return (m_iter != other.m_iter);
    }
private:
    iterator_type m_iter{};
};


////////////////////////////////////////////////////////////////////////////////
//                       enum_traits::verify_enum                                                   
////////////////////////////////////////////////////////////////////////////////

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
#endif /* ELIB_ENUMERATION_ENUM_TRAITS_HPP */