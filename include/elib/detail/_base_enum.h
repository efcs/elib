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
struct lexical_cast_helper<BASE_ENUM, Enum>;
  

////////////////////////////////////////////////////////////////////////////////
//                              enum iterator definition                                                                          
////////////////////////////////////////////////////////////////////////////////


template <typename Enum>
inline constexpr
enum_iterator<Enum>::enum_iterator(Enum e)
    : m_e(e)
{ }
    
template <typename Enum>
inline enum_iterator<Enum>
enum_iterator<Enum>::operator++()
{
    enum_iterator curr = *this;
    BASE_ENUM e = static_cast<BASE_ENUM>(m_e);
    ++e;
    m_e = static_cast<Enum>(e);
    return curr;
}
    
template <typename Enum>
inline enum_iterator<Enum>
enum_iterator<Enum>::operator++(int junk)
{
    BASE_ENUM e = static_cast<BASE_ENUM>(m_e);
    ++e;
    m_e = static_cast<Enum>(e);
    return *this;
}
    
template <typename Enum>
inline typename enum_iterator<Enum>::reference 
enum_iterator<Enum>::operator*()
{ 
    return m_e; 
}
    
template <typename Enum>
inline typename enum_iterator<Enum>::pointer 
enum_iterator<Enum>::operator->()
{ 
    return &m_e;
}
    
template <typename Enum>
inline bool 
enum_iterator<Enum>::operator==(const enum_iterator & other)
{ 
    return m_e == other.m_e; 
}

template <typename Enum>
inline bool 
enum_iterator<Enum>::operator!=(const enum_iterator & other)
{ 
    return m_e != other.m_e; 
}


////////////////////////////////////////////////////////////////////////////////
//                          enum function definitions & helpers
////////////////////////////////////////////////////////////////////////////////


/* get the size of an enum, for use in defining size in enum_traits */
template <typename Enum>
inline constexpr unsigned
enum_size(Enum f, Enum l)
{
    return static_cast<BASE_ENUM>(l) - static_cast<BASE_ENUM>(f) + 1;
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
struct lexical_cast_helper<BASE_ENUM, Enum> {
    inline static BASE_ENUM
    cast(Enum e)
    {
        return static_cast<BASE_ENUM>(e);
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
    
    for (auto & kv : traits::name_map ) {
        
        if (kv.second == s)
            return kv.first;
    }
    
    throw bad_enum_cast(s);
}


template <typename Enum>
inline Enum
enum_cast(BASE_ENUM x)
{
    typedef enum_traits<Enum> traits;
    
    Enum test = static_cast<Enum>(x);
    /* BASE_ENUM should be unsigned, 
     * so you only need to test one boundry */
    if (test <= traits::last_value)
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


////////////////////////////////////////////////////////////////////////////////
//                      enum_iter definition                                                    
////////////////////////////////////////////////////////////////////////////////


template <typename Enum>
inline typename enum_iter<Enum>::iterator 
enum_iter<Enum>::begin() 
{ 
    return iterator(traits::first_value); 
}
   
template <typename Enum>
inline typename enum_iter<Enum>::iterator 
enum_iter<Enum>::end()
{ 
    BASE_ENUM tmp = static_cast<BASE_ENUM>(traits::last_value);
    ++tmp;
    return iterator(static_cast<Enum>(tmp));
}
    
template <typename Enum>
inline typename enum_iter<Enum>::const_iterator 
enum_iter<Enum>::cbegin() const
{ 
    return const_iterator(traits::first_value); 
}
    
template <typename Enum>
inline typename enum_iter<Enum>::const_iterator 
enum_iter<Enum>::cend() const
{ 
    BASE_ENUM tmp = static_cast<BASE_ENUM>(traits::last_value);
    ++tmp;
    return const_iterator(static_cast<Enum>(tmp));
}


////////////////////////////////////////////////////////////////////////////////
//                          enum_traits definition
////////////////////////////////////////////////////////////////////////////////


template <typename Enum>
const typename enum_traits<Enum>::iterator
enum_traits<Enum>::begin = iterator(basic_traits::first_value);

template <typename Enum>    
const typename enum_traits<Enum>::iterator 
enum_traits<Enum>::end = iterator(static_cast<Enum>(
                   static_cast<BASE_ENUM>(basic_traits::last_value) + 1));
    
template <typename Enum>    
const typename enum_traits<Enum>::const_iterator
enum_traits<Enum>::cbegin = const_iterator(basic_traits::first_value);
    
template <typename Enum>
const typename enum_traits<Enum>::const_iterator
enum_traits<Enum>::cend = const_iterator(static_cast<Enum>(
                          static_cast<BASE_ENUM>(basic_traits::last_value) + 1));
    
    
} /* namespace elib */
#endif /* ELIB__BASE_ENUM_H */