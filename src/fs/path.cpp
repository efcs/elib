#include "elib/fs/path.hpp"
#include "elib/assert.hpp"

#include <utility> // for pair 


namespace elib { namespace fs 
{
    ////////////////////////////////////////////////////////////////////////////
    constexpr path::value_type path::preferred_separator;
    constexpr path::value_type path::other_separator;
    
    ////////////////////////////////////////////////////////////////////////////
    namespace { namespace parser
    {
        using string_type = path::string_type;
        using value_type = path::value_type;
        using string_pair = std::pair<string_type, string_type>;
        
        // status reporting
        constexpr std::size_t npos = static_cast<std::size_t>(-1);
        
        inline bool good(std::size_t pos)
        { return pos != npos; }
        
        // lexical elements
        constexpr value_type preferred_separator = path::preferred_separator;
        constexpr value_type const * dot = ".";
        constexpr value_type const* double_dot = "..";
        
        // suppress unused warning for double_dot
        static constexpr struct ignore_double_dot_unused 
        { 
            explicit constexpr ignore_double_dot_unused(const char*) {}
        } ignore_double_dot_unused_obj { double_dot };
        
        
        // forward //
        bool is_separator(string_type const &, std::size_t);
        bool is_root_name(const string_type&, std::size_t);
        bool is_root_directory(string_type const &, std::size_t);
        bool is_trailing_separator(string_type const &, std::size_t);
        
        std::size_t start_of(string_type const &, std::size_t);
        std::size_t end_of(string_type const &, std::size_t);

        std::size_t root_name_start(const string_type& s);
        std::size_t root_name_end(const string_type&);
        
        std::size_t root_directory_start(string_type const &);
        std::size_t root_directory_end(string_type const &);
        
        string_pair separate_filename(string_type const &);
        string_type extract_raw(string_type const &, std::size_t);
        string_type extract_preferred(string_type const &, std::size_t);
        
        ////////////////////////////////////////////////////////////////////////
        std::size_t start_of(const string_type& s, std::size_t pos)
        {
            if (pos >= s.size()) return npos;
            bool in_sep = (s[pos] == preferred_separator);
            while (pos - 1 < s.size() && 
                (s[pos-1] == preferred_separator) == in_sep)
            { --pos; }
            if (pos == 2 && !in_sep && s[0] == preferred_separator &&
                s[1] == preferred_separator)
            { return 0; }
            return pos;
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::size_t end_of(const string_type& s, std::size_t pos)
        {
            if (pos >= s.size()) return npos;
            // special case for root name
            if (pos == 0 && is_root_name(s, pos)) return root_name_end(s);
            bool in_sep = (s[pos] == preferred_separator);
            while (pos + 1 < s.size() && (s[pos+1] == preferred_separator) == in_sep)
            { ++pos; }
            return pos;
        }
        
        ////////////////////////////////////////////////////////////////////////
        bool is_separator(const string_type& s, std::size_t pos)
        {
            return (pos < s.size() && s[pos] == preferred_separator);
        }
        
        ////////////////////////////////////////////////////////////////////////
        bool is_root_name(const string_type& s, std::size_t pos)
        {
            return good(pos) && pos == 0 ? root_name_start(s) == pos : false;
        }
        
        ////////////////////////////////////////////////////////////////////////
        bool is_root_directory(const string_type& s, std::size_t pos)
        {
            return good(pos) ? root_directory_start(s) == pos : false;
        }
        
        ////////////////////////////////////////////////////////////////////////
        bool is_trailing_separator(const string_type& s, std::size_t pos)
        {
            return (pos < s.size() && is_separator(s, pos) && 
                end_of(s, pos) == s.size()-1 &&
                !is_root_directory(s, pos) && !is_root_name(s, pos));
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::size_t root_name_start(const string_type& s)
        {
            return good(root_name_end(s)) ? 0 : npos;
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::size_t root_name_end(const std::string& s)
        {
            if (s.size() < 2 || s[0] != preferred_separator
                || s[1] != preferred_separator) { 
                return npos; 
            }
            if (s.size() == 2) {  
                return 1;
            }
            std::size_t index = 2; // current position
            if (s[index] == preferred_separator) {
                return npos;
            }
            while (index + 1 < s.size() && s[index+1] != preferred_separator) {
                ++index;
            }
            return index;
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::size_t root_directory_start(const string_type& s)
        {
            auto e = root_name_end(s);
            if (!good(e))
            return is_separator(s, 0) ? 0 : npos;
            return is_separator(s, e + 1) ? e + 1 : npos; 
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::size_t root_directory_end(const std::string& s)
        {
            auto st = root_directory_start(s);
            if (!good(st)) return npos;
            std::size_t index = st;
            while (index + 1 < s.size() && s[index + 1] == preferred_separator)
            ++index;
            return index;
        }
        
        ////////////////////////////////////////////////////////////////////////
        string_pair separate_filename(string_type const & s)
        {
            if (s == "." || s == ".." || s.empty()) return string_pair{s, ""};
            auto pos = s.find_last_of('.');
            if (pos == string_type::npos) return string_pair{s, string_type{}};
            return string_pair{s.substr(0, pos), s.substr(pos)};
        }
        
        
        ////////////////////////////////////////////////////////////////////////
        string_type extract_raw(const string_type& s, std::size_t pos)
        {
            std::size_t end_i = end_of(s, pos);
            if (!good(end_i)) return string_type{};
            return s.substr(pos, end_i - pos + 1);
        }
        
        ////////////////////////////////////////////////////////////////////////
        string_type extract_preferred(const string_type& s, std::size_t pos)
        {
            string_type raw = extract_raw(s, pos);
            if (raw.empty()) return raw;
            if (is_trailing_separator(s, pos)) return string_type{dot};
            if (is_separator(s, pos) && !is_root_name(s, pos))
            return string_type{} += preferred_separator;
            return raw;
        }
    }} // namespace parser
    
    
////////////////////////////////////////////////////////////////////////////////
//                            path definitions
////////////////////////////////////////////////////////////////////////////////
  
    path & path::replace_extension(path const & replacement)
    {
        path p = extension();
        if (not p.empty()) {
            m_pathname.erase(m_pathname.size() - p.native().size());
        }
        if (!replacement.empty()) {
            if (replacement.native()[0] != '.') {
                m_pathname += ".";
            }
            m_pathname.append(replacement.m_pathname);
        }
        return *this;
    }
  
    ////////////////////////////////////////////////////////////////////////////
    path path::root_name() const
    {
      return parser::is_root_name(m_pathname, 0) 
        ? path{parser::extract_preferred(m_pathname, 0)}
        : path{};
    }
    
    ////////////////////////////////////////////////////////////////////////////
    path path::root_directory() const
    {
      auto start_i = parser::root_directory_start(m_pathname);
      if(!parser::good(start_i)) return path{};
      return path{parser::extract_preferred(m_pathname, start_i)};
    }
    
    path path::root_path() const
    {
      return root_name() / root_directory();
    }
    
    path path::relative_path() const
    {
      if (empty()) return *this;
      auto end_i = parser::root_directory_end(m_pathname);
      if (!parser::good(end_i))
        end_i = parser::root_name_end(m_pathname);
      if (!parser::good(end_i)) return path{m_pathname};
      return path{m_pathname.substr(end_i+1)};
    }
    
    path path::parent_path() const
    {
      if (empty() || begin() == --end()) return path{};
      auto end_it = --(--end());
      auto end_i = parser::end_of(m_pathname, end_it.m_pos);
      return path{m_pathname.substr(0, end_i+1)};
    }
    
    path path::filename() const
    {
      return empty() ? path{} : *--end();
    }
    
    path path::stem() const
    {
      return path{parser::separate_filename(filename().native()).first};
    }
    
    path path::extension() const
    {
      return path{parser::separate_filename(filename().native()).second};
    }
    
    path::iterator path::begin() const
    {
      iterator it{};
      it.m_path_ptr = this;
      it.m_set_position(0);
      return it;
    }
    
    path::iterator path::end() const
    {
      iterator it{};
      it.m_path_ptr = this;
      it.m_set_position(parser::npos);
      return it;
    }
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            path::iterator                                                
  ////////////////////////////////////////////////////////////////////////////////
    
    typename path::iterator& path::iterator::increment()
    {
      if (m_pos == parser::npos) return *this;
      while (! m_set_position(parser::end_of(m_path_str(), m_pos)+1))
        ;
      return *this;
    }
    
    typename path::iterator& path::iterator::decrement()
    {
      if (m_pos == 0) 
        m_set_position(0);
      else if (m_pos == parser::npos)
        m_set_position(parser::start_of(m_path_str(), m_path_str().size()-1));
      else
      {
        while (!m_set_position(parser::start_of(m_path_str(), m_pos-1)))
          ;
      }
      ELIB_ASSERT(m_valid_iterator_position());
      return *this;
    }
    
    bool path::iterator::m_set_position(std::size_t pos)
    {
      // if past-end. set to end position
      if (pos >= m_path_str().size()) 
      {
        m_pos = parser::npos;
        m_element.clear();
      }
      else
      {
        m_pos = pos;
        m_element = path{parser::extract_preferred(m_path_str(), m_pos)};
      }
      return m_valid_iterator_position();
    }
    
    bool path::iterator::m_valid_iterator_position() const
    {
      if (m_pos == parser::npos) return true; // end position is valid
      ELIB_ASSERT(m_pos < m_path_str().size());
      return (!parser::is_separator(m_path_str(), m_pos) ||
          parser::is_root_directory(m_path_str(), m_pos) ||
          parser::is_trailing_separator(m_path_str(), m_pos) ||
          parser::is_root_name(m_path_str(), m_pos));
    }
    
    const path::string_type& path::iterator::m_path_str() const
    {
      return m_path_ptr->native();
    }

}}                                                          // namespace elib
