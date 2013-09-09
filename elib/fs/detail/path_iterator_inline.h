#ifndef ELIB_FS_PATH_ITERATOR_INLINE_H
#define ELIB_FS_PATH_ITERATOR_INLINE_H

namespace elib {
namespace fs {

inline path::iterator::reference
path::iterator::operator*()
{
    return m_curr;
}

inline path::iterator &
path::iterator::operator++()
{
    next();
    return *this;
}
    
inline path::iterator
path::iterator::operator++(int)
{
    iterator it = *this;
    it.next();
    return it;
}
    
inline path::iterator &
path::iterator::operator--()
{
    prev();
    return *this;
}
    
inline path::iterator
path::iterator::operator--(int)
{
    path::iterator it = *this;
    it.prev();
    return it;
}
    
    
inline bool
path::iterator::operator==(const path::iterator & other) const
{
    return (m_path == other.m_path && m_pos == other.m_pos);
}
    
inline bool
path::iterator::operator!=(const path::iterator & other) const
{
    return ! (*this == other);
}

inline void
path::iterator::next()
{
    path_part p;
    
    if (m_pos != npos) {
        p = pp_helper::part(m_path->str(), m_pos);
        p = pp_helper::next(m_path->str(), p);
    } else {
        p = pp_helper::part(m_path->str(), 0);
    }
    
    if (p.type == pp_e::delim)
        p = pp_helper::next(m_path->str(), p);
    
    if (p.pos == npos)
        p.pos = m_path->str().size();
    
    set_part(p);
}

inline void
path::iterator::prev()
{
    if (m_pos == 0)
        return;
    
    auto new_pos = pp_helper::index_of_prev(m_path->str(), m_pos);
    if (new_pos == npos)
        return;
    
    auto p = pp_helper::part(m_path->str(), new_pos);
    if (p.type == pp_e::delim)
        p = pp_helper::prev(m_path->str(), p);
    
    set_part(p);
}

inline void
path::iterator::set_part(const path_part & p)
{
    
    m_pos = p.pos;
    m_curr = path(p.canon_part);
}

inline bool
path::iterator::is_end() const
{
    return m_pos == npos;
}


} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_PATH_ITERATOR_INLINE_H */