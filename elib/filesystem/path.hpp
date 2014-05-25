#ifndef ELIB_FILESYSTEM_PATH_HPP
#define ELIB_FILESYSTEM_PATH_HPP

# include <elib/filesystem/config.hpp>
# include <elib/filesystem/detail/path_converter.hpp>
# include <elib/aux/enable_if.hpp>

# include <string>
# include <iterator>
# include <algorithm>
# include <locale>
# include <iostream>
# include <utility>
# include <cstddef>

namespace elib { namespace fs { inline namespace v1
{    
    ////////////////////////////////////////////////////////////////////////////
    class path 
    {
    public:
        using value_type = char;
        using string_type = std::basic_string<value_type>;
        
        static constexpr value_type preferred_separator = '/';
        static constexpr value_type other_separator = '\\';
       
        path() {}
        path(path const &) = default;
        path(path &&) = default;
        
        template <
            class Source
          , ELIB_ENABLE_IF(detail::is_pathable<Source>::value)
          >
        path(const Source& src)
        {
          m_pathname = detail::dispatch<string_type>(src);
        }
        
        template <typename InputIter>
        path(InputIter xbegin, InputIter xend)
        {
            using vtype = typename std::iterator_traits<InputIter>::value_type;
                
            if (xbegin != xend) 
            {
                std::basic_string<vtype> s{xbegin, xend};
                m_pathname = detail::convert<string_type>(s);
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        //TODO
        template <typename Source>
        path(const Source& src, const std::locale& loc);
        
        ////////////////////////////////////////////////////////////////////////
        //TODO
        template <typename InputIter>
        path(InputIter begin, InputIter end, const std::locale& loc);

        ////////////////////////////////////////////////////////////////////////
        ~path() =  default;
        
        ////////////////////////////////////////////////////////////////////////
        path & operator=(const path &) = default;
        
        ////////////////////////////////////////////////////////////////////////
        path & operator=(path&& p) noexcept
        {
          m_pathname.swap(p.m_pathname);
          return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class Source
          , ELIB_ENABLE_IF(detail::is_pathable<Source>::value)
          >
        path & operator=(Source const & src)
        { 
            return assign(src);
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class Source
          , ELIB_ENABLE_IF(detail::is_pathable<Source>::value)
          >
        path & assign(Source const & src)
        {
            m_pathname = detail::dispatch<string_type>(src);
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class InputIter>
        path & assign(InputIter xbegin, InputIter xend)
        {
            using vtype = typename std::iterator_traits<InputIter>::value_type;
            if (xbegin != xend) {
                std::basic_string<vtype> s{xbegin, xend};
                m_pathname = detail::convert<string_type>(s);
            }
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        path & operator/=(path const & p)
        {
            bool const append_sep = 
                not empty() && not p.empty() 
                  && p.m_pathname[0] != preferred_separator 
                  && p.m_pathname[0] != other_separator
                  && m_pathname.back() != preferred_separator
                  && m_pathname.back() != other_separator;
                
            if (append_sep)  m_pathname += preferred_separator;
            
            m_pathname += p.native();
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class Source
          , ELIB_ENABLE_IF(detail::is_pathable<Source>::value)
          >
        path & operator/=(Source const & src)
        {
            path p{detail::dispatch<string_type>(src)};
            return this->operator/=(p);
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class Source
          , ELIB_ENABLE_IF(detail::is_pathable<Source>::value)
          >
        path & append(Source const & src)
        {
            path p{detail::dispatch<string_type>(src)};
            return this->operator/=(p);
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class InputIter>
        path& append(InputIter xbegin, InputIter xend)
        {
            using vtype = typename std::iterator_traits<InputIter>::value_type;
            if (xbegin != xend)  {
                std::basic_string<vtype> xstr{xbegin, xend};
                path p{detail::convert<string_type>(xstr)};
                this->operator/=(p);
            }
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        path & operator+=(path const & p)
        {
            m_pathname += p.native();
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        path & operator+=(string_type const & xstr)
        {
            m_pathname += xstr;
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        path & operator+=(value_type const* xstr)
        { 
            m_pathname += xstr;
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        path & operator+=(value_type ch)
        {
            m_pathname += ch;
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class Source
          , ELIB_ENABLE_IF(detail::is_pathable<Source>::value)
          >
        path & operator+=(Source const & src)
        {
            return this->operator+=(detail::dispatch<string_type>(src));
        }
        
        static_assert(detail::is_pathable<std::basic_string<char>>::value, "shit");
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class CharT
          , ELIB_ENABLE_IF(detail::is_pathable<std::basic_string<CharT>>::value)
          >
        path & operator+=(CharT ch)
        {
          std::basic_string<CharT> tmp{};
          tmp += ch;
          return this->operator+=(detail::convert<string_type>(tmp));
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class Source
          , ELIB_ENABLE_IF(detail::is_pathable<Source>::value)
          >
        path & concat(Source const & src)
        {
            return this->operator+=(detail::dispatch<string_type>(src));
        }
    
        ////////////////////////////////////////////////////////////////////////
        template <class InputIter>
        path & concat(InputIter xbegin, InputIter xend)
        {
            using vtype = typename std::iterator_traits<InputIter>::value_type;
            if (xbegin != xend) {
                std::basic_string<vtype> tmp{xbegin, xend};
                this->operator+=(detail::convert<string_type>(tmp));
            }
            return *this;
        }
    
        ////////////////////////////////////////////////////////////////////////
        void clear() noexcept
        { 
            m_pathname.clear(); 
        }

        ////////////////////////////////////////////////////////////////////////
        path & make_preferred()
        {
          std::replace(
              std::begin(m_pathname), std::end(m_pathname)
            , other_separator, preferred_separator
            );
          return *this;
        } 
    
        ////////////////////////////////////////////////////////////////////////
        path & remove_filename()
        { 
            return *this = parent_path(); 
        }
        
        ////////////////////////////////////////////////////////////////////////
        path & replace_filename(path const & replacement)
        {
            remove_filename();
            return (*this /= replacement);
        }
        
        path & replace_extension(path const & replacement = path());
        
        ////////////////////////////////////////////////////////////////////////
        void swap(path& rhs) noexcept
        { 
            m_pathname.swap(rhs.m_pathname); 
        }

        ////////////////////////////////////////////////////////////////////////
        //native format observers
        string_type const & native() const noexcept
        { 
            return m_pathname; 
        }
  
        ////////////////////////////////////////////////////////////////////////
        value_type const* c_str() const noexcept
        { 
            return m_pathname.c_str(); 
        }
        
        ////////////////////////////////////////////////////////////////////////
        operator string_type() const
        { 
            return m_pathname; 
        }
        
        ////////////////////////////////////////////////////////////////////////
        // TODO
        template <
            class CharT
          , class Traits = std::char_traits<CharT>
          , class Allocator = std::allocator<CharT>
          > 
        std::basic_string<CharT, Traits, Allocator>
        string(Allocator const & a = Allocator()) const; //TODO
        
        ////////////////////////////////////////////////////////////////////////
        std::string string() const
        { 
            return m_pathname;
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::wstring wstring() const; //TODO
        std::string u8string() const; //TODO
        std::u16string u16string() const; //TODO
        std::u32string u32string() const; //TODO
        
        ////////////////////////////////////////////////////////////////////////
        // generic format observers TODO
        template <
            class CharT
          , class Traits = std::char_traits<CharT>
          , class Allocator = std::allocator<CharT>
          >
        std::basic_string<CharT, Traits, Allocator>
        generic_string(const Allocator& a = Allocator()) const;

        std::string generic_string() const; //TODO
        std::wstring generic_wstring() const; //TODO
        std::string generic_u8string() const; //TODO
        std::u16string generic_u16string() const; //TODO
        std::u32string generic_u32string() const; //TODO
        
        ////////////////////////////////////////////////////////////////////////
        // comparision
        int compare(path const & other) const noexcept
        {
            return m_pathname.compare(other.m_pathname);
        }
        
        int compare(const string_type& xstr) const
        { 
            return compare(path(xstr)); 
        }
        
        int compare(const value_type* xstr) const
        { 
            return compare(path(xstr)); 
        }
        
        ////////////////////////////////////////////////////////////////////////
        // decomp
        path root_name() const;
        path root_directory() const;
        path root_path() const;
        path relative_path() const;
        path parent_path() const;
        path filename() const;
        path stem() const;
        path extension() const;
        
        ////////////////////////////////////////////////////////////////////////
        // query
        bool empty() const noexcept
        { return m_pathname.empty(); }
        
        ////////////////////////////////////////////////////////////////////////
        bool has_root_name() const
        { return !root_name().empty(); }
        
        ////////////////////////////////////////////////////////////////////////
        bool has_root_directory() const
        { return !root_directory().empty(); }
        
        ////////////////////////////////////////////////////////////////////////
        bool has_root_path() const
        { return !root_path().empty(); }
        
        ////////////////////////////////////////////////////////////////////////
        bool has_relative_path() const
        { return !relative_path().empty(); }
        
        ////////////////////////////////////////////////////////////////////////
        bool has_parent_path() const
        { return !parent_path().empty();}
        
        ////////////////////////////////////////////////////////////////////////
        bool has_filename() const
        { return !filename().empty(); }
        
        ////////////////////////////////////////////////////////////////////////
        bool has_stem() const
        { return !stem().empty();}
        
        ////////////////////////////////////////////////////////////////////////
        bool has_extension() const
        { return !extension().empty(); }
        
        ////////////////////////////////////////////////////////////////////////
        bool is_absolute() const
        { return !root_directory().empty();}
        
        ////////////////////////////////////////////////////////////////////////
        bool is_relative() const
        { return !is_absolute(); }
        
        ////////////////////////////////////////////////////////////////////////
        // iterators
        class iterator;
        using const_iterator = iterator;
        
        iterator begin() const;
        iterator end() const;
        
    private:
        string_type m_pathname{};
    };                                                       // class path
    
    ////////////////////////////////////////////////////////////////////////////
    inline void swap(path & lhs, path & rhs) noexcept
    { lhs.swap(rhs); }
      
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator<(path const & lhs, path const & rhs) noexcept
    { return (lhs.compare(rhs) < 0); }

    inline bool operator<=(path const & lhs, path const & rhs) noexcept
    { return (lhs.compare(rhs) <= 0); }
      
    inline bool operator>(path const & lhs, path const & rhs) noexcept
    { return (lhs.compare(rhs) > 0); }
      
    inline bool operator>=(path const & lhs, path const & rhs) noexcept
    { return (lhs.compare(rhs) >= 0); }
      
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator==(path const & lhs, path const & rhs) noexcept
    { return (lhs.compare(rhs) == 0); }
      
    inline bool operator!=(path const & lhs, path const & rhs) noexcept
    { return (lhs.compare(rhs) != 0); }

    ////////////////////////////////////////////////////////////////////////////
    inline path operator/(path const & lhs, path const & rhs)
    { return path(lhs) /= rhs;}

    ////////////////////////////////////////////////////////////////////////////
    template <class CharT, class Traits>
    inline std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT, Traits> & os, path const & p)
    {
        os << p.native();
        return os;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class CharT, class Traits>
    inline std::basic_istream<CharT, Traits> &
    operator>>(std::basic_istream<CharT, Traits> & is, path & p)
    {
      path::string_type tmp;
      is >> tmp;
      p = tmp;
      return is;
    }

    ////////////////////////////////////////////////////////////////////////////
    template <class Source>
    path u8path(const Source& src);  //TODO

    template <class InputIter>
    path u8path(InputIter begin, InputIter end); //TODO

    ////////////////////////////////////////////////////////////////////////////
    inline std::size_t hash_value(const path& p) noexcept
    {
        std::hash<path::string_type> h;
        return h(p.native());
    }

    
////////////////////////////////////////////////////////////////////////////////
//                               PATH ITERATOR
////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////
    class path::iterator 
      : public std::iterator<std::bidirectional_iterator_tag, path> 
    {
    public:
        ////////////////////////////////////////////////////////////////////////
        // ctor & dtor
        iterator() = default;
        iterator(const iterator&) = default;
        iterator(iterator&&) noexcept = default;
        ~iterator() = default;
        
        ////////////////////////////////////////////////////////////////////////
        //assignments
        iterator& operator=(const iterator&) = default;
        iterator& operator=(iterator&&) = default;
        
        ////////////////////////////////////////////////////////////////////////
        // deref
        const path & operator*() const
        { return m_element; }
        
        const path* operator->() const
        { return &m_element; }
        
        ////////////////////////////////////////////////////////////////////////
        // forward iterator requirements
        iterator & operator++()
        { return increment(); }
        
        iterator operator++(int)
        {
          iterator it{*this};
          increment();
          return it;
        }
        
        ////////////////////////////////////////////////////////////////////////
        // bidirectional iterator requirements
        iterator & operator--()
        { return decrement(); }
        
        iterator operator--(int)
        {
          iterator it{*this};
          decrement();
          return it;
        }
        
        ////////////////////////////////////////////////////////////////////////
        // logic for traversal is here
        iterator & increment();
        iterator& decrement();
        
      private:
        
        // for begin() and end()
        friend class path;
        friend bool operator==(iterator const & lhs, iterator const & rhs);
        
        bool equal(iterator const & other) const
        {
            return (m_path_ptr == other.m_path_ptr && m_pos == other.m_pos);
        }
        
        // check if the element is a valid iterator element,
        // ie. check it is not a (non-trailing/root) separator
        bool m_valid_iterator_position() const;
        
        // parse the token at pos & set the iterator to said element
        // return the result of valid_iterator_position() after
        // setting the element
        bool m_set_position(std::size_t pos);
        
        // return the string for the assocated path
        // as if by path::native()
        const string_type&
        m_path_str() const;
      
        path m_element;
        const path *m_path_ptr{nullptr};
        std::size_t m_pos{};
    };
    
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator==(path::iterator const & lhs, path::iterator const & rhs)
    {
        return lhs.equal(rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator!=(path::iterator const & lhs, path::iterator const & rhs)
    {
        return !(lhs == rhs);
    }
    
}}}                                                       // namespace elib::fs
#endif /* ELIB_FILESYSTEM_PATH_HPP */