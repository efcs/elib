#ifndef ELIB_FS__PATH_H
#define ELIB_FS__PATH_H


#ifndef ELIB_FS_PATH_H
#   error only include this file through path.h
#endif


namespace elib {
namespace fs {
    
inline 
path::path()
    : m_pathname{}
{ }

inline 
path::path(const std::string & s)
    : m_pathname{s}
{ }


inline
path::path(const char* s)
    : m_pathname{s}
{ }

inline const std::string & 
path::str() const
{
    return m_pathname;
}

inline const char*
path::c_str() const
{
    return m_pathname.c_str();
}

////////////////////////////////////////////////////////////////////////////////
//                             modifiers                                             
////////////////////////////////////////////////////////////////////////////////

inline void
path::clear()
{
    m_pathname.clear();
}

inline path &
path::remove_filename()
{
    *this = parent_path();
    return *this;
}

inline path&
path::replace_filename(const path & replace)
{
    *this = (parent_path() /= replace);
    return *this;
}

inline path &
path::replace_extension(const path & new_ext)
{
    auto p = extension();
    if (! p.empty())
        m_pathname = m_pathname.substr(0, m_pathname.size() - p.str().size());
    
    if (new_ext.empty())
        return *this;
    
    if (new_ext.str()[0] != '.')
        m_pathname += '.';
    
    m_pathname += new_ext.str();
    return *this;
}

inline void
path::swap(path & other)
{
    m_pathname.swap(other.m_pathname);
}

////////////////////////////////////////////////////////////////////////////////
//                              append                                           
////////////////////////////////////////////////////////////////////////////////

inline path &
path::operator/=(const path & p)
{
    return append(p);
}

inline path &
path::operator/=(const std::string & s)
{
    return append(s);
}

inline path &
path::append(const path & p)
{
    return append(p.str());
}

inline path &
path::append(const std::string & s)
{
    bool no_sep = empty() || s.empty() ||
                  detail::is_path_delim((*--end()).str()) ||
                  s[0] == path_separator;
                  
    if (! no_sep)
        m_pathname += path_separator;
    
    m_pathname += s;
    return *this;
}

template <typename InputIter>
inline path &
path::append(InputIter begin, InputIter end)
{
    for (; begin != end; ++begin) {
        append(*begin);
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
//                            concat                                              
////////////////////////////////////////////////////////////////////////////////

inline path &
path::operator+=(const path & p)
{
    return concat(p);
}

inline path &
path::operator+=(const std::string & s)
{
    return concat(s);
}

inline path &
path::operator+=(char ch)
{
    return concat(ch);
}

inline path &
path::concat(const path & p)
{
    m_pathname += p.str();
    return *this;
}

inline path &
path::concat(const std::string & s)
{
    m_pathname += s;
    return *this;
}

inline path &
path::concat(char ch)
{
    m_pathname += ch;
    return *this;
}

template <typename InputIter>
inline path &
path::concat(InputIter begin, InputIter end)
{
    for (; begin != end; ++begin)
        concat(*begin);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
//                              compare                                                 
////////////////////////////////////////////////////////////////////////////////


inline int
path::compare(const path & other) const 
{
    return m_pathname.compare(other.str());
}

inline int
path::compare(const std::string & other) const
{
    return m_pathname.compare(other);
}


////////////////////////////////////////////////////////////////////////////////
//                            decomp                                              
////////////////////////////////////////////////////////////////////////////////

inline path
path::root_name() const
{
    path_part p = pp_helper::part(m_pathname, 0);
    if (p.type == pp_e::root_name)
        return path(p.canon_part);
    return path();
}
    
inline path
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
    
inline path
path::root_path() const
{
    path p = root_name();
    path other = root_directory();
    p.m_pathname += other.m_pathname;
    return p;
}
    
inline path
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
    
inline path
path::parent_path() const
{
    if (empty() || begin() == --end())
        return path();
    
    auto it = --end();
    --it;
    
    return path(m_pathname.substr(0, it.m_pos + (*it).str().size()));
}
    
inline path
path::stem() const
{
    using namespace ::elib::fs::detail;
    path p = filename();
    const std::string & str = p.str();
    if (str == "." || str == "..")
        return p;
    
    size_type pos = m_pathname.find_last_of('.');
    if (pos == npos)
        return p;
    
    return path(str.substr(0, pos));
}
    
inline path
path::filename() const
{
    if (empty())
        return path();
    
    auto it = --end();
    return *it;
}
    
inline path
path::extension() const
{
    using namespace ::elib::fs::detail;
    path p = filename();
    const std::string & str = p.str();
    
    if (str == "." || str == "..")
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
    return  (! root_directory().empty());
}

inline bool
path::is_relative() const
{
    return ! is_absolute();
}

////////////////////////////////////////////////////////////////////////////////
//                          iterator                                                  
////////////////////////////////////////////////////////////////////////////////

inline path::iterator
path::begin() const
{
    iterator it;
    it.m_path = this;
    it.m_pos = 0;
    auto p = pp_helper::part(m_pathname, 0);
    it.m_curr = path(p.canon_part);
    return it;
}

inline path::iterator
path::end() const
{
    iterator it;
    it.m_path = this;
    it.m_pos = m_pathname.size();
    it.m_curr = path("");
    return it;
}

/*
inline path::reverse_iterator
path::rbegin() const
{
    iterator it;
    it.m_path = this;
    it.m_pos = pp_helper::index_of_last(m_pathname);
    auto p = pp_helper::part(m_pathname, it.m_pos);
    it.m_curr = path(p.canon_part);
    
    return reverse_iterator(it);
}

inline path::reverse_iterator
path::rend() const
{
    iterator it;
    it.m_path = this;
    it.m_pos = npos;
    it.m_curr = path("");
    return reverse_iterator(it);
}
*/

} /* namespace fs */    
} /* namespace elib */
#endif /* ELIB_FS__PATH_H */