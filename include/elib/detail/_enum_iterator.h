#ifndef ELIB__ENUM_ITERATOR_H
#define ELIB__ENUM_ITERATOR_H

#ifndef ELIB_ENUM_ITERATOR_H
#   error do not include this file directly
#endif

namespace elib {
    

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


} /* namespace elib */
#endif /* ELIB__ENUM_ITERATOR_H */