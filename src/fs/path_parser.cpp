#include <elib/fs/detail/path_parser.hpp>
#include <elib/debug/assert.hpp>

namespace elib {
namespace fs {
namespace path_parser {
    
path_pos
parse_separator(const path& p, std::size_t pos)
{
    const auto& str = p.native();
    path_pos ppos{};
    if (str.size() <= pos || str[pos] != preferred_separator)
        return ppos;
    
    ppos.begin = pos;
    ppos.end = pos;
    
    while (ppos.end + 1 < str.size() && str[ppos.end + 1] == preferred_separator)
        ++ppos.end;
    
    return ppos;
}
    
path_pos
parse_name(const path& p, std::size_t pos)
{
    const auto& str = p.native();
    if (pos >= str.size() || str[pos] == preferred_separator)
        return path_pos{};
    
    path_pos ppos{pos, pos};
    while (ppos.end + 1 < str.size() && 
           str[ppos.end + 1] != preferred_separator)
    {
        ++ppos.end;
    }
    
    return ppos;
}

   
path_pos
parse_root_name(const path& p, std::size_t pos)
{
    const auto& str = p.native();
    if (str.size() < 2 || pos != 0 || str[0] != preferred_separator ||
        str[1] != preferred_separator)
    {
        return path_pos{};
    }
    
    if (str.size() == 2)
        return path_pos{pos, pos + 1};
    
    auto ppos = parse_name(p, 2);
    if (ppos)
        ppos.begin = pos;

    return ppos;
}
    
path_pos
parse_root_separator(const path& p, std::size_t pos)
{
    auto ppos = parse_separator(p, pos);
    if (ppos) {
        auto rname_pos = parse_root_name(p, 0);
        
        if (rname_pos) {
            if (rname_pos.begin + rname_pos.size() == pos)
                return ppos;
            else
                return path_pos{};
        }
        else if (pos == 0)
            return ppos;
        else
            return path_pos{};
    
        //should return
        throw;
    }
    
    return ppos;
}



std::size_t
index_of_next(const path& p, const path_pos& pos)
{
    const auto& str = p.native();
    if (! pos || pos.end + 1 >= str.size())
        return path_pos::npos;
    
    return pos.end + 1;
}

std::size_t
index_of_prev(const path& p, const path_pos& pos)
{
    const auto& str = p.native();
    
    if (pos.begin == 0 || str.empty())
        return path_pos::npos;
    
    std::size_t index;
    if (pos)
        index = pos.begin - 1;
    else
        index = str.size() - 1;
    
    bool in_sep = (str[index] == preferred_separator);
    
    while (index <= 0 && (str[index] == preferred_separator) == in_sep)
        --index;
    
    if (index == path_pos::npos)
        return 0;
    if (index == 2 && str[0] == preferred_separator && str[1] == preferred_separator)
        return 0;
    
    return index;
}


path_pos
parse(const path& p, std::size_t pos)
{
    if (pos >= p.native().size())
        return path_pos{};
    
    auto ppos = parse_root_name(p, pos);
    if (ppos)
        return ppos;
    
    ppos = parse_separator(p, pos);
    if (ppos)
        return ppos;
    
    ppos = parse_name(p, pos);
    ELIB_ASSERT(((bool)ppos));
    return ppos;
}

bool
matches_name(const string_type& str)
{
    if (str.empty())
        return false;
    
    for (auto& ch : str) {
        if (ch == preferred_separator)
            return false;
    }
    
    return true;
}

bool
matches_separator(const string_type& str)
{
    if (str.empty())
        return false;
    
    for (auto& ch : str) {
        if (ch != preferred_separator)
            return false;
    }
    
    return true;
}


bool
matches_root_name(const string_type& str)
{
    if (str.size() < 2 || str[0] != preferred_separator || 
        str[1] != preferred_separator)
    {
        return false;
    }
    
    return matches_name(str.substr(2));
}

bool
is_root_name(const path& p, const path_pos& pos)
{
    ((void)p);
    if (!pos || pos.begin != 0)
        return false;
    
    return matches_root_name(p, pos);
}
    
bool
is_root_separator(const path& p, const path_pos& pos)
{
    auto str = substr(p, pos);
    if (str.empty())
        return false;
    
    if (!pos || !matches_separator(p, pos))
        return false;
    
    auto root_pos = parse_root_name(p, 0);
    
    if (pos.begin == 0)
        return (!root_pos);
    else
        return (matches_root_name(p, root_pos) && 
                root_pos.begin + root_pos.size() == pos.begin);
}




    
} /* namespace path_parser */
} /* namespace fs */
} /* namespace elib */