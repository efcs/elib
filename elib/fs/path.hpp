#ifndef ELIB_FS_PATH_HPP
#define ELIB_FS_PATH_HPP

#include <elib/fs/detail/path_converter.hpp>

#include <string>
#include <iterator>
#include <locale>
#include <cstddef>
#include <iostream>
#include <utility>

namespace elib {
namespace fs {
    
class path {
public:
    typedef char value_type;
    typedef std::basic_string<value_type> string_type;
    
    static constexpr value_type preferred_separator = '/';
    
// ctor & dtor
    // can't be default for some reason
    path() : m_pathname{}
    { }
    
    path(const path& p)
    { m_pathname = p.m_pathname; }
    
    path(path&& p) noexcept
    { m_pathname = std::move(p.m_pathname); }
    
    template <typename Source>
    path(const Source& src)
    {
        m_pathname = detail::dispatch<string_type>(src);
    }
    
    template <typename InputIter>
    path(InputIter begin, InputIter end)
    {
        typedef typename std::iterator_traits<InputIter>::value_type vtype;
        
        if (begin != end) {
            std::basic_string<vtype> s{begin, end};
            m_pathname = detail::convert<string_type>(s);
        }
    }
    
    //TODO
    template <typename Source>
    path(const Source& src, const std::locale& loc);
    
    //TODO
    template <typename InputIter>
    path(InputIter begin, InputIter end, const std::locale& loc);

    
//assignments
    path&
    operator=(const path& p)
    { 
        if (this == &p)
            return *this;
        m_pathname = p.m_pathname;
        return *this;
    }
    
    path&
    operator=(path&& p) noexcept
    {
        if (this == &p)
            return *this;
        m_pathname = std::move(p.m_pathname);
        return *this;
    }
    
    template <typename Source>
    detail::enable_if_convertible_t<Source, path>&
    operator=(const Source& src)
    { return assign(src); }
    
    template <typename Source>
    detail::enable_if_convertible_t<Source, path>&
    assign(const Source& src)
    {
        m_pathname = detail::dispatch<string_type>(src);
        return *this;
    }
    
    template <typename InputIter>
    path& 
    assign(InputIter begin, InputIter end)
    {
        typedef typename std::iterator_traits<InputIter>::value_type vtype;
        
        if (begin != end) {
            std::basic_string<vtype> s{begin, end};
            m_pathname = detail::convert<string_type>(s);
        }
        
        return *this;
    }
    
//appends
    path& 
    operator/=(const path& p)
    {
        bool append_sep = !( empty() ||
                             p.empty() ||
                             *p.native().cbegin() == preferred_separator ||
                             native().back() == preferred_separator);
        if (append_sep) 
            m_pathname += preferred_separator;
        
        m_pathname += p.native();
        return *this;
    }
    
    template <typename Source>
    detail::enable_if_convertible_t<Source, path>&
    operator/=(const Source& src)
    {
        path p{detail::dispatch<string_type>(src)};
        return this->operator/=(p);
    }
    
    template <typename Source>
    detail::enable_if_convertible_t<Source, path>&
    append(const Source& src)
    {
        path p{detail::dispatch<string_type>(src)};
        return this->operator/=(p);
    }
    
    template <typename InputIter>
    path&
    append(InputIter begin, InputIter end)
    {
        typedef typename std::iterator_traits<InputIter>::value_type vtype;
        if (begin != end) {
            std::basic_string<vtype> str{begin, end};
            
            path p{detail::convert<string_type>(str)};
            this->operator/=(p);
        }
        
        return *this;
    }
    
//concatenation
    path&
    operator+=(const path& p)
    {
        m_pathname += p.native();
        return *this;
    }
    
    path&
    operator+=(const string_type& str)
    {
        m_pathname += str;
        return *this;
    }
    
    path&
    operator+=(const value_type* str)
    { 
        m_pathname += str;
        return *this;
    }
    
    path&
    operator+=(value_type ch)
    {
        m_pathname += ch;
        return *this;
    }
    
    template <typename Source>
    detail::enable_if_convertible_t<Source, path>&
    operator+=(const Source& src)
    {
        return this->operator+=(detail::dispatch<string_type>(src));
    }
    
    template <typename CharT>
    detail::enable_if_convertible_t<std::basic_string<CharT>, path>&
    operator+=(CharT ch)
    {
        std::basic_string<CharT> tmp{};
        tmp += ch;
        return this->operator+=(detail::convert<string_type>(tmp));
    }
    
    template <typename Source>
    detail::enable_if_convertible_t<Source, path>&
    concat(const Source& src)
    {
        return this->operator+=(detail::dispatch<string_type>(src));
    }
    
    template <typename InputIter>
    path&
    concat(InputIter begin, InputIter end)
    {
        typedef typename std::iterator_traits<InputIter>::value_type vtype;
        
        if (begin != end) {
            std::basic_string<vtype> tmp{begin, end};
            this->operator+=(detail::convert<string_type>(tmp));
        }
        return *this;
    }
    
// modifiers
    void
    clear() noexcept
    { m_pathname.clear(); }
    
    path&
    make_preferred()
    {
        value_type other_sep;
        if (preferred_separator == '/')
            other_sep = '\\';
        else
            other_sep = '/';
        
        for (auto& ch : m_pathname) {
            if (ch == other_sep)
                ch = preferred_separator;
        }
        
        return *this;
    }
    
    path&
    remove_filename()
    {
        path p = filename();
        if (p.empty())
            return *this;
        
        m_pathname.erase(m_pathname.size() - p.native().size());
        return *this;
    }
    
    path&
    replace_filename(const path& replacement)
    {
        remove_filename();
        *this /= replacement;
        return *this;
    }
    
    path&
    replace_extension(const path& replacement = path())
    {
        path p = extension();
        if (!p.empty())
            m_pathname.erase(m_pathname.size() - p.native().size());
        
        return (*this += replacement);
    }
    
    void
    swap(path& rhs) noexcept
    {
        m_pathname.swap(rhs.m_pathname);
    }

//native format observers
    const string_type&
    native() const noexcept
    { return m_pathname; }
    
    //EXTENSION
    const string_type&
    str() const noexcept
    { return m_pathname; }
    
    const value_type*
    c_str() const noexcept
    { return m_pathname.c_str(); }
    
    operator string_type() const
    { return m_pathname; }
    
    template <class CharT, class Traits = std::char_traits<CharT>,
              class Allocator = std::allocator<CharT>>
    std::basic_string<CharT, Traits, Allocator>
    string(const Allocator& a = Allocator()) const;
    
    std::string
    string() const
    { return m_pathname; }
    
    std::wstring
    wstring() const;
    
    std::string
    u8string() const;
    
    std::u16string
    u16string() const;
    
    std::u32string 
    u32string() const;
    
//generic format observers
    template <class CharT, class Traits = std::char_traits<CharT>,
              class Allocator = std::allocator<CharT>>
    std::basic_string<CharT, Traits, Allocator>
    generic_string(const Allocator& a = Allocator()) const;
    
    std::string
    generic_string() const;
    
    std::wstring
    generic_wstring() const;
    
    std::string
    generic_u8string() const;
    
    std::u16string
    generic_u16string() const;
    
    std::u32string 
    generic_u32string() const;
    
// comparision
    int 
    compare(const path& p) const noexcept;
    
    int 
    compare(const string_type& str) const
    { return compare(path(str)); }
    
    int 
    compare(const value_type* str) const
    { return compare(path(str)); }
    
//decompasition
    path 
    root_name() const;
    
    path
    root_directory() const;
    
    path
    root_path() const;
    
    path
    relative_path() const;
    
    path
    parent_path() const;
    
    path
    filename() const;
    
    path
    stem() const;
    
    path
    extension() const;
    
// query
    bool
    empty() const noexcept
    { return m_pathname.empty(); }
    
    bool
    has_root_name() const
    { return !root_name().empty(); }
    
    bool
    has_root_directory() const
    { return !root_directory().empty(); }
    
    bool
    has_root_path() const
    { return !root_path().empty(); }
    
    bool
    has_relative_path() const
    { return !relative_path().empty(); }
    
    bool
    has_parent_path() const
    { return !parent_path().empty(); }
    
    bool
    has_filename() const
    { return !filename().empty(); }
    
    bool
    has_stem() const
    { return !stem().empty(); }
    
    bool
    has_extension() const
    { return !extension().empty(); }
    
    bool
    is_absolute() const
    { return !root_directory().empty(); }
    
    bool
    is_relative() const
    { return !is_absolute(); }
    
// iterators
    class iterator;
    typedef iterator const_iterator;
    
    iterator
    begin() const;
    
    iterator
    end() const;
    
private:
    string_type m_pathname{};
};

////////////////////////////////////////////////////////////////////////////////
//                        path functions                                                  
////////////////////////////////////////////////////////////////////////////////

inline void
swap(path& lhs, path& rhs) noexcept
{
    lhs.swap(rhs);
}

inline bool
operator<(const path& lhs, const path& rhs) noexcept
{ return (lhs.compare(rhs) < 0); }

inline bool
operator<=(const path& lhs, const path& rhs) noexcept
{ return (lhs.compare(rhs) <= 0); }

inline bool
operator>(const path& lhs, const path& rhs) noexcept
{ return (lhs.compare(rhs) > 0); }

inline bool
operator>=(const path& lhs, const path& rhs) noexcept
{ return (lhs.compare(rhs) >= 0); }

inline bool
operator==(const path& lhs, const path& rhs) noexcept
{ return (lhs.compare(rhs) == 0); }

inline bool
operator!=(const path& lhs, const path& rhs) noexcept
{ return (lhs.compare(rhs) == 0); }

inline path
operator/(const path& lhs, const path& rhs)
{
    path tmp{lhs};
    return tmp /= rhs;
}

template <class CharT, class Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const path& p)
{
    os << p.native();
    return os;
}

template <class CharT, class Traits>
inline std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, path& p)
{
    path::string_type tmp;
    is >> tmp;
    p = tmp;
    return is;
}

template <class Source>
path
u8path(const Source& src);

template <class InputIter>
path
u8path(InputIter begin, InputIter end);

   

////////////////////////////////////////////////////////////////////////////////
//                       path_parser's needed types                                                 
////////////////////////////////////////////////////////////////////////////////
namespace path_parser {
    
    
struct path_pos {
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);
    
    std::size_t begin{npos};
    std::size_t end{npos};
    
    path_pos() = default;
    
    path_pos(std::size_t p1, std::size_t p2)
        : begin{p1}, end{p2}
    { }
    
    std::size_t
    size() const
    { 
        if ((bool)*this)
            return (end - begin + 1);
        else
            return 0;
    }
    
    constexpr
    operator bool() const
    { return (begin != npos && end != npos && begin <= end); }
    
    constexpr bool
    operator==(const path_pos& rhs) const
    { return (begin == rhs.begin && end == rhs.end); }
    
    constexpr bool
    operator!=(const path_pos& rhs) const
    { return !(this->operator==(rhs)); }
    
    /* since operator bool() will allow this struct to be passed
     * to any function that expects an integral, we overload and throw */
    operator char() const
    { throw; }
};

    
} /* namespace path_parser */


////////////////////////////////////////////////////////////////////////////////
//                        path::iterator                                                 
////////////////////////////////////////////////////////////////////////////////


class path::iterator 
    : public std::iterator<std::bidirectional_iterator_tag, path> {
public:
    friend class path;
    
// ctor & dtor
    iterator() = default;
    iterator(const iterator&) = default;
    iterator(iterator&&) noexcept = default;
    ~iterator() = default;
     
//assignments
    iterator&
    operator=(const iterator&) = default;
     
    iterator&
    operator=(iterator&&) noexcept = default;
     
// iterator functionality
    const path&
    operator*() const
    { return m_curr_path; }
     
    const path*
    operator->() const
    { return &m_curr_path; }
     
    iterator&
    operator++()
    { return next(); }
     
    iterator
    operator++(int)
    {
        iterator it{*this};
        next();
        return it;
    }
     
    iterator&
    operator--()
    { return prev(); }
     
    iterator
    operator--(int)
    {
        iterator it{*this};
        prev();
        return it;
    }
     
    iterator&
    next();
     
    iterator&
    prev();
     
// equality comparable     
    bool
    operator==(const iterator& other) const
    { return (m_path == other.m_path && m_pos == other.m_pos); }
    
    bool
    operator!=(const iterator& other) const
    { return !(this->operator==(other)); }
     
private:
    path m_path{};
    path m_curr_path{};
    path_parser::path_pos m_pos{};
};
   

////////////////////////////////////////////////////////////////////////////////
//                           path::hash                                               
////////////////////////////////////////////////////////////////////////////////

inline std::size_t
hash_value(const path& p) noexcept
{
    path::string_type str{};
    for (auto& part : p)
        str += part.native();
    
    std::hash<path::string_type> hash_fn;
    return hash_fn(str);
}
    
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_PATH_HPP */