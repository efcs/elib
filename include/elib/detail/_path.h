#ifndef ELIB__PATH_H
#define ELIB__PATH_H


#ifndef ELIB_PATH_H
#   error only include this file through path.h
#endif


namespace elib {
    
    
inline 
path::path()
    : m_pathname{}
{ }

inline 
path::path(const std::string & s)
    : m_pathname{s}
{ }

inline const std::string & 
path::str() const
{
    return m_pathname;
}

inline void
path::clear()
{
    m_pathname.clear();
}

inline path::iterator
path::begin() const
{
    iterator it;
    //TODO
    return it;
}

inline path::iterator
path::end() const
{
    iterator it;
    //TODO
    return it;
}



////////////////////////////////////////////////////////////////////////////////
//                            decomp                                              
////////////////////////////////////////////////////////////////////////////////

path
path::root_name() const
{
    path_part p = pp_helper::part(m_pathname, 0);
    if (p.type == pp_e::root_name)
        return path(p.canon_part);
    return path();
}
    
path
path::root_directory() const
{
    path_part p = pp_helper::part(m_pathname, 0);
    if (p.type == pp_e::root_delim) {
        return path(p.canon_part);
    }
    else if (p.type == pp_e::root_name) {
        p = pp_helper::part(m_pathname, p.raw_part.size());
        if (p.type == pp_e::root_delim)
            return path(p.canon_part);
    }
    
    return path();
}
    
path
path::root_path() const
{
    path p = root_name();
    path other = root_directory();
    p.m_pathname += other.m_pathname;
    return p;
}
    
path
path::relative_path() const
{
    path_part p;
    pp_helper::part(m_pathname, 0, p);
    
    if (p.type == pp_e::root_name)
        pp_helper::part(m_pathname, p.raw_part.size(), p);
    
    if (p.type == pp_e::root_delim) {
        return path(m_pathname.substr(p.pos + p.raw_part.size()));
    }
    else if (p.type == pp_e::name || p.type == pp_e::dot || 
             p.type == pp_e::double_dot) {
        return path(m_pathname.substr(p.pos));
    }
    else if (p.type == pp_e::none) {
        return path();
    } 
    
    throw;
}
    
path
path::parent_path() const
{
    unsigned index = pp_helper::index_of_last(m_pathname);
    return path(m_pathname.substr(0, index));
}
    
path
path::stem() const
{
    using namespace ::elib::detail;
    path p = filename();
    const std::string & str = p.str();
    if (is_path_dot(str) || is_path_double_dot(str))
        return p;
    
    size_type pos = m_pathname.find_last_of('.');
    if (pos == npos)
        return p;
    
    return path(str.substr(0, pos));
}
    
path
path::filename() const
{
    unsigned index = pp_helper::index_of_last(m_pathname);
    return path(m_pathname.substr(index));
}
    
path
path::extension() const
{
    using namespace ::elib::detail;
    path p = filename();
    const std::string & str = p.str();
    
    if (is_path_dot(str) || is_path_double_dot(str))
        return path();
    
    size_type pos = str.find_last_of('.');
    if (pos == npos)
        return path();
    
    return path(str.substr(pos));
    
}

////////////////////////////////////////////////////////////////////////////////
//                          check parts                                                 
////////////////////////////////////////////////////////////////////////////////

inline bool
path::empty() const
{
    return m_pathname.empty();
}

inline bool
path::has_root_name() const
{
    return ! root_name().empty();
}

inline bool
path::has_root_directory() const
{
    return ! root_directory().empty();
}

inline bool
path::has_root_path() const
{
    return ! root_path().empty();
}

inline bool
path::has_parent_path() const
{
    return ! parent_path().empty();
}

inline bool
path::has_filename() const
{
    return ! filename().empty();
}

inline bool
path::has_stem() const
{
    return ! stem().empty();
}

inline bool
path::has_extension() const
{
    return ! extension().empty();
}

inline bool
path::is_absolute() const
{
    //TODO
    return false;
}

inline bool
path::is_relative() const
{
    return ! is_absolute();
}


////////////////////////////////////////////////////////////////////////////////
//                             path::iterator                                             
////////////////////////////////////////////////////////////////////////////////


path::iterator::reference
path::iterator::operator*()
{
    return m_curr_path;
}

inline path::iterator &
path::iterator::operator++()
{
    //TODO
    return *this;
}
    
inline path::iterator
path::iterator::operator++(int)
{
    //TODO
    return *this;
}
    
path::iterator &
path::iterator::operator--()
{
    //TODO
    return *this;
}
    
inline path::iterator
path::iterator::operator--(int)
{
    //TODO
    return *this;
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
    
    
} /* namespace elib */
#endif /* ELIB__PATH_H */