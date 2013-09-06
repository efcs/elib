#ifndef ELIB_PATH_H
#define ELIB_PATH_H

#include "detail/_path_helper.h"

#include <string>


namespace elib {
    
    
class path {
public:
    typedef typename std::string::size_type size_type;
    static constexpr size_type npos = std::string::npos;
    
    path();
    path(const std::string & str);
    
    path(const path&) = default;
    path(path&&) = default;
    
    ~path() = default;
    
    path &
    operator=(const path&) = default;
    
    path &
    operator=(path&&) = default;
    
    void 
    clear();
    
//
// iterator
//
    class iterator;
    typedef iterator const_iterator;
    
    iterator
    begin() const;
    
    iterator
    end() const;
    
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

//
// concat
//
    path &
    operator+=(const path & p);
    
    path &
    operator+=(const std::string & s);
    
    path &
    concat(const path & p);
    
    path &
    concat(const std::string & s);
    
    
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

//
// converting
//
    
    const std::string &
    str() const;
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
    path m_curr_path;
    unsigned m_pos{0};
    path* m_path{nullptr};
};

    
} /* namespace elib */


#include "detail/_path.h"


#endif /* ELIB_PATH_H */