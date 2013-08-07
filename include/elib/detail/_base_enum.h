#ifndef ELIB__BASE_ENUM_H
#define ELIB__BASE_ENUM_H


#ifndef ELIB_BASE_ENUM_H
#   error this file should only be included via base_enum.h
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
    UNUSED(junk);
    enum_iterator curr = *this;
    ++m_iter;
    return curr;
}
    
template <typename Enum>
inline Enum
enum_iterator<Enum>::operator*()
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
inline bool
bad_enum(Enum e)
{
    typedef enum_traits<Enum> traits;
    return (! traits::good(e));
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
safe_enum_cast(const std::string & s)
{
    typedef enum_traits<Enum> traits;
    
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
    
    Enum e = static_cast<Enum>(x);
    if (traits::good(e))
        return e;
    
    return traits::BAD_ENUM;
}
    
    
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

/* Ret is one of std::string, or the underlying_type */
template <typename Ret, typename Enum>
inline Ret
lexical_enum_cast(Enum e)
{
    return lexical_cast_helper<Ret, Enum>::cast(e);
}

template <typename Enum>
typename enum_traits<Enum>::underlying_type
base_enum_cast(Enum e)
{
    typedef enum_traits<Enum> traits;
    
    return static_cast<typename traits::underlying_type>(e);
}


////////////////////////////////////////////////////////////////////////////////
//                          enum_traits definition
////////////////////////////////////////////////////////////////////////////////

template <typename Enum>
unsigned
enum_traits<Enum>::size()
{ return basic_traits::name_map.size(); }

template <typename Enum>
bool
enum_traits<Enum>::good(underlying_type val)
{
    Enum e = static_cast<Enum>(val);
    return good(e);
}

template <typename Enum>
bool
enum_traits<Enum>::good(Enum e)
{
    return (basic_traits::name_map.count(e) == 1);
}

template <typename Enum>
typename enum_traits<Enum>::iterator
enum_traits<Enum>::iterator_at(Enum e) 
{ return iterator(e); }

template <typename Enum>
typename enum_traits<Enum>::iterator
enum_traits<Enum>::iterator_at(iter_pos_e pos)
{ return iterator(pos); }

template <typename Enum>
typename enum_traits<Enum>::iterator
enum_traits<Enum>::begin()
{
    return iterator(iter_pos_e::begin);
}

template <typename Enum>    
typename enum_traits<Enum>::iterator 
enum_traits<Enum>::end()
{
    return iterator(iter_pos_e::end);
}
    
template <typename Enum>    
typename enum_traits<Enum>::const_iterator
enum_traits<Enum>::cbegin() const
{
    return const_iterator(basic_traits::first_value);
}
    
template <typename Enum>
typename enum_traits<Enum>::const_iterator
enum_traits<Enum>::cend() const
{
    return const_iterator(iter_pos_e::end);
}
    
} /* namespace elib */
#endif /* ELIB__BASE_ENUM_H */