#ifndef ELIB_FS_PATH_HELPER_H
#define ELIB_FS_PATH_HELPER_H

#include <elib/fs/config.h>
#include <elib/utility/size_type.h>
#include <elib/enumeration/basic_enum_traits.h>

#include <string>
#include <stdexcept>


namespace elib {
namespace fs {
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


class path_part;
    

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
    typedef typename elib_size_type::size_type size_type;
    static constexpr size_type npos = elib_size_type::npos;
    
    static void
    part(const std::string & s, size_type pos, path_part & dest);
    
    static path_part
    part(const std::string & s, size_type pos);
    
    static path_part
    next(const std::string & s, const path_part & p);
    
    static path_part
    prev(const std::string & s, const path_part & p);
    
    static path_part
    last(const std::string & s);
    
    static size_type
    index_of_next(const std::string & s, size_type last_pos);
    
    static size_type
    index_of_prev(const std::string & s, size_type last_pos);
    
    static size_type
    index_of_last(const std::string & s);
    
    static bool
    is_last(const std::string & s, unsigned pos);
    
    static bool
    is_last(const std::string & s, const path_part & p);
    
    static bool
    is_root_delim(const std::string & s, const path_part & p);
    
    static bool
    is_trailing_delim(const std::string & s, const path_part & p);
    
    static bool
    set_delim_type(const std::string & s, path_part & p);
private:
    static void
    _first_part(const std::string & s, path_part & dest);
    
    static void
    _part(const std::string & s, size_type pos, path_part & dest);
    
    static void
    _process_part(const std::string & s, path_part & part);
    
private:
    path_helper() = delete;
};


struct path_part {
    typedef path_helper::size_type size_type;
    size_type pos;
    path_part_e type;
    std::string raw_part;
    std::string canon_part;
};


} /* namespace detail */
} /* namespace fs */

template <>
struct basic_enum_traits<fs::detail::path_part_e> {
private:
    using pp_e = fs::detail::path_part_e;
public:
    typedef fs::detail::path_part_e type;

    static constexpr pp_e default_value = pp_e::none;
    static constexpr pp_e first_value = pp_e::none;
    static constexpr pp_e last_value = pp_e::double_dot;
    
    typedef const std::map<pp_e, std::string> map_type;
    static map_type name_map;
};


////////////////////////////////////////////////////////////////////////////////
//                            path_helper definition
////////////////////////////////////////////////////////////////////////////////

namespace fs {
namespace detail {

inline void
path_helper::part(const std::string & s, size_type pos, path_part & dest)
{
    dest.pos = pos;
    dest.type = path_part_e::none;
    dest.raw_part.clear();
    dest.canon_part.clear();
    
    if (pos >= s.size()) {
        dest.pos = npos;
        return;
    }
    
    if (pos == 0)
        _first_part(s, dest);
    else
        _part(s, pos, dest);
    
    _process_part(s, dest);
}

inline path_part
path_helper::part(const std::string & s, size_type pos)
{
    path_part p;
    part(s, pos, p);
    return p;
}


inline path_part
path_helper::next(const std::string & s, const path_part & p)
{
    path_part dest{0, path_part_e::none, "", ""};
    size_type pos = p.pos + p.raw_part.size();
    part(s, pos, dest);
    return dest;
}
    
inline path_part
path_helper::prev(const std::string & s, const path_part & p)
{
    path_part dest{0, path_part_e::none, "", ""};
    size_type pos = index_of_prev(s, p.pos);
    part(s, pos, dest);
    return dest;
}

inline path_part
path_helper::last(const std::string & s)
{
    path_part dest{0, path_part_e::none, "", ""};
    size_type pos = index_of_last(s);
    part(s, pos, dest);
    return dest;
}

inline path_helper::size_type
path_helper::index_of_next(const std::string & s, size_type last_pos)
{
    if (last_pos >= s.size())
        return npos;
    
    auto p = part(s, last_pos);
    if (p.type == path_part_e::none)
        return npos;
    
    size_type pos = last_pos + p.raw_part.size();
    if (pos >= s.size())
        return npos;
    
    return pos;
}


inline path_helper::size_type
path_helper::index_of_prev(const std::string & s, size_type last_pos)
{
    if (last_pos == 0 || last_pos > s.size())
        return npos;
    
    auto iter = s.rbegin() + (s.size() - last_pos);
    bool in_delim = is_path_delim(*iter);
    
    size_type size = 0;
    while (iter < s.rend()) {
        if (in_delim != is_path_delim(*iter))
            break;
        ++size;
        ++iter;
    }
    
    size_type i = last_pos - size;
    if (i == 2 && is_path_delim(s[0]) && is_path_delim(s[1]))
        i = 0;
    
    return i;
}


inline path_helper::size_type
path_helper::index_of_last(const std::string & s)
{
    return index_of_prev(s, s.size());
}

inline bool
path_helper::is_last(const std::string & s, unsigned pos)
{
    auto p = part(s, pos);
    return (p.pos + p.raw_part.size() >= s.size());
}

inline bool
path_helper::is_last(const std::string & s, const path_part & p)
{
    return (p.pos + p.raw_part.size() >= s.size());
}

inline bool
path_helper::is_root_delim(const std::string & s, const path_part & p)
{
    if (! is_path_delim(p.raw_part))
        return false;
    
    if (p.pos == 0)
        return true;
    
    auto other = part(s, 0);
    return (other.pos + other.raw_part.size() == p.pos && 
            other.type == path_part_e::root_name);
}

inline bool
path_helper::is_trailing_delim(const std::string & s, const path_part & p)
{
    if (p.pos == 0)
        return false;
    
    if (p.pos + p.raw_part.size() < s.size())
        return false;
    
    return is_path_delim(p.raw_part);
}

inline bool
path_helper::set_delim_type(const std::string & s, path_part & p)
{
    if (is_root_delim(s, p)) {
        p.type = path_part_e::root_delim;
        p.canon_part = path_separator_str;
        return true;
    }
    else if (is_trailing_delim(s, p)) {
        p.type = path_part_e::trailing_delim;
        p.canon_part = ".";
        return true;
    }
    else if (is_path_delim(p.raw_part)) {
        p.type = path_part_e::delim;
        p.canon_part = path_separator_str;
        return true;
    }
    
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//                             private path_helper                                           
////////////////////////////////////////////////////////////////////////////////

inline void
path_helper::_first_part(const std::string & s, path_part & dest)
{
    bool in_delim;
    size_type pos = 0;
    
    if (is_path_root_name(s.substr(0, 3))) {
        dest.raw_part = s.substr(0, 3);
        dest.type = path_part_e::root_name;
        in_delim = false;
        pos = 3;
    }
    else if (s[0] == path_separator) {
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
        dest.canon_part = path_separator_str;
}

inline void
path_helper::_part(const std::string & s, size_type pos, path_part & dest)
{
    auto iter = s.begin() + pos;
    bool in_delim = (*iter == path_separator);
    
    while (iter < s.end()) {
        if (in_delim != is_path_delim(*iter))
            break;
        
        dest.raw_part += *iter;
        ++iter;
    }
}

inline void
path_helper::_process_part(const std::string & s, path_part & p)
{
    if (p.type != path_part_e::none)
        return;
    
    if (set_delim_type(s, p)) {
        //nothing
    }
    else if (p.raw_part == ".") {
        p.type = path_part_e::dot;
        p.canon_part = ".";
    }
    else if (p.raw_part == "..") {
        p.type = path_part_e::double_dot;
        p.canon_part = "..";
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
    return (ch == path_separator);
}

inline bool
is_path_delim(const std::string & s)
{
    if (s.empty())
        return false;
    
    for (auto & ch : s) {
        if (ch != path_separator)
            return false;
    }
    
    return true;
}

inline bool
is_path_name(const std::string & s)
{
    if (s.empty())
        return false;
    
    for (auto & ch : s) {
        if (ch == path_separator)
            return false;
    }
    
    if (s == "." || s == "..")
        return false;
    
    return true;
}

inline bool
is_path_root_name(const std::string & s)
{
    if (s.size() < 2)
        return false;
    
    if (s[0] != path_separator || s[1] != path_separator)
        return false;
    
    auto iter = s.begin() + 2;
    while (iter < s.end()) {
        if (*iter == path_separator)
            return false;
        
        ++iter;
    }
    
    return true;
}


} /* namespace detail */
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_PATH_HELPER_H */
