#ifndef ELIB__PATH_HELPER_H
#define ELIB__PATH_HELPER_H

#include "elib/fs_delim.h"

#include <string>
#include <stdexcept>


namespace elib {
namespace detail {
    

constexpr bool
is_path_delim(char ch);

bool
is_path_delim(const std::string & s);

bool
is_path_dot(char ch);

bool
is_path_dot(const std::string & s);

bool
is_path_double_dot(const std::string & s);

bool
is_path_name(const std::string & s);

bool
is_path_root_name(const std::string & s);
    

enum class path_part_e {
    none,
    
    name,
    root_name,
    
    delim,
    root_delim,
    trailing_delim,
    
    dot,
    double_dot
};    


struct path_part {
    unsigned pos;
    path_part_e type;
    std::string raw_part;
    std::string canon_part;
};


class parse_part_error : std::runtime_error {
public:
    inline
    parse_part_error()
        : std::runtime_error("failure parsing part")
    { }
    
    inline
    parse_part_error(const std::string & what)
        : std::runtime_error(std::string("failure parsing part: ") + what)
    { }
};
    

class path_helper {
public:
    static void
    part(const std::string & s, unsigned pos, path_part & dest);
    
    static path_part
    part(const std::string & s, unsigned pos);
    
    static path_part
    next(const std::string & s, const path_part & p);
    
    static path_part
    prev(const std::string & s, const path_part & p);
    
    static path_part
    last(const std::string & s);
    
    static unsigned
    index_of_next(const std::string & s, unsigned last_pos);
    
    static unsigned
    index_of_prev(const std::string & s, unsigned last_pos);
    
    static unsigned
    index_of_last(const std::string & s);
private:
    static void
    _first_part(const std::string & s, path_part & dest);
    
    static void
    _part(const std::string & s, unsigned pos, path_part & dest);
    
    static void
    _process_part(path_part & part);
    
private:
    path_helper() = delete;
};


////////////////////////////////////////////////////////////////////////////////
//                            path_helper definition
////////////////////////////////////////////////////////////////////////////////


inline void
path_helper::part(const std::string & s, unsigned pos, path_part & dest)
{
    dest.pos = pos;
    dest.type = path_part_e::none;
    dest.raw_part.clear();
    dest.canon_part.clear();
    
    if (pos >= s.size())
        return;
    
    if (pos == 0)
        _first_part(s, dest);
    else
        _part(s, pos, dest);
    
    _process_part(dest);
}

inline path_part
path_helper::part(const std::string & s, unsigned pos)
{
    path_part p;
    part(s, pos, p);
    return p;
}


inline path_part
path_helper::next(const std::string & s, const path_part & p)
{
    path_part dest{0, path_part_e::none, "", ""};
    unsigned pos = p.pos + p.raw_part.size();
    part(s, pos, dest);
    return dest;
}
    
inline path_part
path_helper::prev(const std::string & s, const path_part & p)
{
    path_part dest{0, path_part_e::none, "", ""};
    unsigned pos = index_of_prev(s, p.pos);
    part(s, pos, dest);
    return dest;
}

inline path_part
path_helper::last(const std::string & s)
{
    path_part dest{0, path_part_e::none, "", ""};
    unsigned pos = index_of_last(s);
    part(s, pos, dest);
    return dest;
}

inline unsigned
path_helper::index_of_next(const std::string & s, unsigned last_pos)
{
    if (last_pos >= s.size())
        return -1;
    
    auto p = part(s, last_pos);
    if (p.type == path_part_e::none)
        return -1;
    
    unsigned pos = last_pos + p.raw_part.size();
    if (pos >= s.size())
        return -1;
    
    return pos;
}


inline unsigned
path_helper::index_of_prev(const std::string & s, unsigned last_pos)
{
    if (last_pos == 0 || last_pos > s.size())
        return -1;
    
    auto iter = s.rbegin() + (s.size() - last_pos);
    bool in_delim = is_path_delim(*iter);
    
    unsigned size = 0;
    while (iter < s.rend()) {
        if (in_delim != is_path_delim(*iter))
            break;
        ++size;
        ++iter;
    }
    
    unsigned i = static_cast<unsigned>(last_pos) - size;
    if (i == 2 && is_path_delim(s[0]) && is_path_delim(s[1]))
        i = 0;
    
    return i;
}


inline unsigned
path_helper::index_of_last(const std::string & s)
{
    return index_of_prev(s, s.size());
}


inline void
path_helper::_first_part(const std::string & s, path_part & dest)
{
    bool in_delim;
    unsigned pos = 0;
    
    if (is_path_root_name(s.substr(0, 3))) {
        dest.raw_part = s.substr(0, 3);
        dest.type = path_part_e::root_name;
        in_delim = false;
        pos = 3;
    }
    else if (is_path_delim(s[0])) {
        dest.type = path_part_e::root_delim;
        in_delim = true;
    } 
    else {
        in_delim = false;
    }
    
    
    auto iter = s.begin() + pos;
    while (iter < s.end()) {
        if (in_delim != is_path_delim(*iter))
            break;
        dest.raw_part += *iter;
        ++iter;
    }
    
    if (dest.type == path_part_e::root_name)
        dest.canon_part = dest.raw_part;
    else if (dest.type == path_part_e::root_delim)
        dest.canon_part = fs_delim;
}

inline void
path_helper::_part(const std::string & s, unsigned pos, path_part & dest)
{
    auto iter = s.begin() + pos;
    bool in_delim = is_path_delim(*iter);
    
    while (iter < s.end()) {
        if (in_delim != is_path_delim(*iter))
            break;
        
        dest.raw_part += *iter;
        ++iter;
    }
    
    if (is_path_delim(dest.raw_part)) {
        path_part p;
        part(s, 0, p);
        if (p.raw_part.size() == pos && p.type == path_part_e::root_name) {
            dest.type = path_part_e::root_delim;
            dest.canon_part = fs_delim;
        }
        else if (dest.pos + dest.raw_part.size() >= s.size()) {
            dest.type = path_part_e::trailing_delim;
            dest.canon_part = fs_dot;
        } else {
            dest.type = path_part_e::delim;
            dest.canon_part = fs_delim;
        }
    }
    
}

inline void
path_helper::_process_part(path_part & p)
{
    if (p.type != path_part_e::none)
        return;
    
    if (is_path_delim(p.raw_part)) {
        p.type = path_part_e::delim;
        p.canon_part = fs_delim;
    }
    else if (is_path_dot(p.raw_part)) {
        p.type = path_part_e::dot;
        p.canon_part = fs_dot;
    }
    else if (is_path_double_dot(p.raw_part)) {
        p.type = path_part_e::double_dot;
        p.canon_part = fs_double_dot;
    }
    else if (is_path_name(p.raw_part)) {
        p.type = path_part_e::name;
        p.canon_part = p.raw_part;
    } else {
        throw parse_part_error(p.raw_part);
    }
}


////////////////////////////////////////////////////////////////////////////////
//                              function definitions                                            
////////////////////////////////////////////////////////////////////////////////
    
    
inline constexpr bool
is_path_delim(char ch)
{
    return (ch == fs_delim_char);
}

inline bool
is_path_delim(const std::string & s)
{
    if (s.empty())
        return false;
    
    for (auto & ch : s) {
        if (! is_path_delim(ch))
            return false;
    }
    
    return true;
}

inline bool
is_path_dot(char ch)
{
    return (ch == fs_dot[0]);
}

inline bool
is_path_dot(const std::string & s)
{
    return (s == fs_dot);
}

inline bool
is_path_double_dot(const std::string & s)
{
    return (s == fs_double_dot);
}

inline bool
is_path_name(const std::string & s)
{
    if (s.empty())
        return false;
    
    for (auto & ch : s) {
        if (is_path_delim(ch))
            return false;
    }
    
    if (is_path_dot(s) || is_path_double_dot(s))
        return false;
    
    return true;
}

inline bool
is_path_root_name(const std::string & s)
{
    if (s.size() < 2)
        return false;
    
    if (! is_path_delim(s[0]) || ! is_path_delim(s[1]))
        return false;
    
    auto iter = s.begin() + 2;
    while (iter < s.end()) {
        if (is_path_delim(*iter))
            return false;
        
        ++iter;
    }
    
    return true;
}


} /* namespace detail */
} /* namespace elib */
#endif /* ELIB__PATH_HELPER_H */
