#ifndef ELIB_FS_PATH_PARSER_HPP
#define ELIB_FS_PATH_PARSER_HPP

#include <elib/fs/path.hpp>
#include <elib/debug/assert.hpp>

#include <string>
#include <cstddef>

namespace elib {
namespace fs {
namespace path_parser {
    
typedef typename path::value_type value_type;
typedef typename path::string_type string_type;
    
constexpr value_type preferred_separator = '/';
constexpr const value_type* preferred_separators = "/";
    
inline bool
contains_pos(const path& p, const path_pos& pos)
{
    return (pos && pos.end < p.native().size());
}

inline string_type
substr(const path& p, const path_pos& pos)
{
    if (! contains_pos(p, pos))
        return string_type{};
    
    return string_type{p.native().substr(pos.begin, pos.size())};
}   

inline path
subpath(const path& p, const path_pos& pos)
{
    return path{substr(p, pos)};
}

// parsing functions
path_pos
parse_separator(const path& p, std::size_t pos);
    
path_pos
parse_name(const path& p, std::size_t pos);

path_pos
parse_root_name(const path& p, std::size_t pos);
    
path_pos
parse_root_separator(const path& p, std::size_t pos);

std::size_t
index_of_next(const path& p, const path_pos& pos);

std::size_t
index_of_prev(const path& p, const path_pos& pos);

path_pos
parse(const path& p, std::size_t pos);

inline path_pos
next(const path& p, const path_pos& pos)
{
    return parse(p, index_of_next(p, pos));
}
    
inline path_pos
prev(const path& p, const path_pos& pos)
{
    return parse(p, index_of_prev(p, pos));
}

// move forward & back 
inline path_pos
front(const path& p)
{ 
    return parse(p, 0);
}
    
inline path_pos
back(const path& p)
{
    return parse(p, index_of_prev(p, path_pos{}));
}

    
// observers

bool
matches_name(const string_type& s);

inline bool
matches_name(const path& p)
{ return matches_name(p.native()); }

inline bool
matches_name(const path& p, const path_pos& pos)
{ return matches_name(substr(p, pos)); }

bool
matches_separator(const string_type& s);

inline bool
matches_separator(const path& p)
{ return matches_separator(p.native()); }

inline bool
matches_separator(const path& p, const path_pos& pos)
{ return matches_separator(substr(p, pos)); }

bool 
matches_root_name(const string_type& s);

inline bool
matches_root_name(const path& p)
{ return matches_root_name(p.native()); }

inline bool
matches_root_name(const path& p, const path_pos& pos)
{ return matches_root_name(substr(p, pos)); }

bool
is_root_name(const path& p, const path_pos& pos);
    
bool
is_root_separator(const path& p, const path_pos& pos);
    
inline bool
is_trailing_separator(const path& p, const path_pos& pos)
{
    return (pos && matches_separator(p, pos) && !is_root_separator(p, pos));
}
    
inline bool
is_front(const path& p, const path_pos& pos)
{
    return (contains_pos(p, pos) && pos.begin == 0);
}
    
inline bool
is_back(const path& p, const path_pos& pos)
{
    return (contains_pos(p, pos) && pos.end == p.native().size() - 1);
}


inline bool
is_iterator_member(const path& p, const path_pos& pos)
{    
    return (!p.empty() && 
            (!matches_separator(p, pos) || is_root_separator(p, pos) ||
             is_trailing_separator(p, pos)));
}
    
inline path
preferred_path_string(const path& p, const path_pos& pos)
{
    if (is_root_separator(p, pos))
        return path{preferred_separators};
    else if (is_trailing_separator(p, pos))
        return path{"."};
    else if (matches_separator(p, pos))
        return path{};
    else
        return subpath(p, pos);
}

    
} /* namespace path_parser  */   
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_PATH_PARSER_HPP */