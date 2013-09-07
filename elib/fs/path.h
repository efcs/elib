#ifndef ELIB_FS_PATH_H
#define ELIB_FS_PATH_H


#include <elib/fs/detail/path_helper.h>

#include <string>
#include <iterator>


namespace elib {
namespace fs {
    
    
class path {
public:
    typedef typename std::string::size_type size_type;
    static constexpr size_type npos = std::string::npos;
    
    path();
    path(const std::string & str);
    
    path(const path&) = default;
    
    path &
    operator=(const path&) = default;
    
    path &
    operator=(const std::string & s);
    
    path(path&&) = default;
    
    path &
    operator=(path&&) = default;
    
    ~path() = default;
    
//
// to string
//
    
    const std::string &
    str() const;
    
    const char*
    c_str() const;
    
//
// modifiers
//
    void 
    clear();
    
    path &
    remove_filename();
    
    path &
    replace_extension(const path & new_ext = path());
    
    void
    swap(path & other);
    
//
// cmp 
//
    
    int 
    compare(const path & other) const;
    
    int 
    compare(const std::string & other) const;
    
//
// iterator
//
    class iterator;
    typedef iterator const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef reverse_iterator const_reverse_iterator;
    
    iterator
    begin() const;
    
    iterator
    end() const;
    
    reverse_iterator
    rbegin() const;
    
    reverse_iterator
    rend() const;
    
//
// append
//
    path &
    operator/=(const path & p);
    
    path &
    operator/=(const std::string & s);
    
    path &
    append(const path & p);
    
    path &
    append(const std::string & s);
    
    template <typename InputIter>
    path &
    append(InputIter begin, InputIter end);

//
// concat
//
    path &
    operator+=(const path & p);
    
    path &
    operator+=(const std::string & s);
    
    path &
    operator+=(char ch);
    
    path & 
    concat(const path & p);
    
    path &
    concat(const std::string & s);
    
    path &
    concat(char ch);
    
    template <typename InputIter>
    path &
    concat(InputIter begin, InputIter end);
    
//
// check parts
//
    bool
    empty() const;
    
    bool
    has_root_name() const;
    
    bool
    has_root_directory() const;
    
    bool
    has_root_path() const;
    
    bool
    has_parent_path() const;
    
    bool
    has_filename() const;
    
    bool
    has_stem() const;
    
    bool
    has_extension() const;
    
    bool
    is_absolute() const;
    
    bool
    is_relative() const;
    
//
// decompose
//
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
    stem() const;
    
    path
    filename() const;
    
    path
    extension() const;

private:
    using pp_helper = detail::path_helper;
    using path_part = detail::path_part;
    using pp_e = detail::path_part_e;
    std::string m_pathname;
};



class path::iterator {
public:
    typedef path value_type;
    typedef path& reference;
    typedef path* pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    
    iterator() = default;
    
    iterator(const iterator &) = default;
    
    iterator &
    operator=(const iterator &) = default; 
    
    ~iterator() = default;
    
    reference
    operator*();

    iterator &
    operator++();
    
    iterator
    operator++(int);
    
    iterator &
    operator--();
    
    iterator
    operator--(int);

    bool
    operator==(const iterator & other) const;
    
    bool
    operator!=(const iterator & other) const;
    
private:
    bool
    is_end() const;
    
    void
    next();
    
    void
    prev();
    
    void
    set_part(const path_part & p);
    
private:
    friend class path;
    path m_curr;
    size_type m_pos;
    const path* m_path{nullptr};
};


} /* namespace fs */
} /* namespace elib */


#include <elib/fs/detail/path_inline.h>
#include <elib/fs/detail/path_iterator_inline.h>


#endif /* ELIB_FS_PATH_H */