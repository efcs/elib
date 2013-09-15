#include <elib/fs/path.hpp>
#include <elib/fs/detail/path_parser.hpp>

namespace elib {
namespace fs {
    
int
path::compare(const path& rhs) const noexcept
{
    //TODO
    return m_pathname.compare(rhs);
}

path 
path::root_name() const
{
    auto ppos = path_parser::parse_root_name(*this, 0);
    if (!ppos)
        return path{};
    
    return path_parser::subpath(*this, ppos);
}
    
path
path::root_directory() const
{
    auto ppos = path_parser::parse_root_name(*this, 0);
    if (!ppos)
        ppos = path_parser::parse_separator(*this, 0);
    else {
        auto sec_ppos = path_parser::parse_separator(*this, ppos.end + 1);
        if (sec_ppos)
            return path_parser::subpath(*this, sec_ppos);
        else
            return path{};
    }
    
    //parse_separator(*this, 0) failed
    if (!ppos)
        return path{};
    
    return path_parser::subpath(*this, ppos);
}
    
path
path::root_path() const
{
    path p{};
    p /= root_name();
    p /= root_directory();
    return p;
}
    
path
path::relative_path() const
{
    path p = root_path();
    return path{m_pathname.substr(p.native().size())};
    
}
    
path
path::parent_path() const
{
    auto ppos = path_parser::back(*this);
    if (ppos && ppos.begin != 0)
        return path{m_pathname.substr(0, ppos.begin)};
    else
        return path{};
}
    
path
path::filename() const
{
    auto ppos = path_parser::back(*this);
    if (ppos && ppos.begin != 0)
        return path_parser::subpath(*this, ppos);
    else
        return path{};
}
    
path
path::stem() const
{
    auto p = filename();
    if (p.empty() || p == "." || p == "..")
        return path{};
    
    auto index = m_pathname.find('.');
    if (index == string_type::npos)
        return path{};
    else
        return path{m_pathname.substr(0, index)};
}
    
path
path::extension() const
{
    auto p = filename();
    if (p.empty() || p == "." || p == "..")
        return path{};
    
    auto index = m_pathname.find(".");
    if (index == string_type::npos)
        return path{};
    else
        return path{m_pathname.substr(index)};
}


path::iterator
path::begin() const
{
    iterator it;
    it.m_path = *this;
    it.m_pos = path_parser::front(*this);
    it.m_curr_path = path_parser::subpath(*this, it.m_pos);
    return it;
}

path::iterator
path::end() const
{
    iterator it;
    it.m_path = *this;
    it.m_pos = path_parser::path_pos{};
    return it;
}


////////////////////////////////////////////////////////////////////////////////
//                         path::iterator                                                 
////////////////////////////////////////////////////////////////////////////////
    
    
path::iterator&
path::iterator::next()
{
    if (m_pos) {
        m_pos = path_parser::next(m_path, m_pos);
        m_curr_path = path_parser::subpath(m_path, m_pos);
    }

    return *this;
}

path::iterator&
path::iterator::prev()
{
    if (m_pos.begin != 0) {
        m_pos = path_parser::prev(m_path, m_pos);
        m_curr_path = path_parser::subpath(m_path, m_pos);
    }
    
    return *this;
}
    
} /* namespace fs */
} /* namespace elib */