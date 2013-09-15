#include <elib/fs/path.hpp>

#include <utility> // for pair 


namespace elib 
{
  namespace fs 
  {
    namespace parser
    {
      typedef typename path::string_type string_type;
      typedef typename path::value_type value_type;
      
      typedef std::pair<string_type, string_type> string_pair;
      
    // status reporting
      constexpr const std::size_t npos = static_cast<std::size_t>(-1);
      
      inline bool good(std::size_t pos)
        { return pos != npos; }
      
    // lexical elements
      constexpr const value_type preferred_separator = path::preferred_separator;
      constexpr const value_type* dot = ".";
      constexpr const value_type* double_dot = "..";
      
    // fwd
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
      
      // forward's for end_of
      bool is_root_name(const string_type&, std::size_t);
      std::size_t root_name_end(const string_type&);
      
      std::size_t end_of(const string_type& s, std::size_t pos)
      {
        if (pos >= s.size()) return npos;
        if (is_root_name(s, pos)) return root_name_end(s);
        bool in_sep = (s[pos] == preferred_separator);
        while (pos + 1 < s.size() && 
          (s[pos+1] == preferred_separator) == in_sep)
        { ++pos; }
        return pos;
      }
      
      // end == npos if size == 0
      std::size_t end(const string_type& s)
        { return s.size()-1; }
      
    // lexical observers
      inline bool is_separator(const string_type& s)
      {
        if (s.empty()) return false;
        for (auto& ch : s)
          { if (ch != preferred_separator) return false; }
        return true;
      }
      
      bool is_separator(const string_type& s, std::size_t pos)
      {
        return (pos < s.size() && s[pos] == preferred_separator);
      }
        
      
      bool is_name(const string_type& s)
      {
        if (s.empty()) return false;
        for (auto& ch : s)
        {
          if (ch == preferred_separator)
            return false;
        }
        return true;
      }
      
      bool is_name(const string_type& s, std::size_t pos)
      {
        return (pos < s.size() && s[pos] != preferred_separator);
      }
      
      bool is_root_name(const string_type& s)
      {
        if (s.size() < 2 || s[0] != preferred_separator ||
          s[1] == preferred_separator)
            { return false; }
        if (s.size() == 2) return true;
        return is_name(s.substr(3));
      }
      
      bool is_root_name(const string_type& s, std::size_t pos)
      {
        if (pos != 0 || pos >= s.size() || s.size() < 2 ||
          s[0] != preferred_separator || s[1] != preferred_separator)
            { return false;}
        if (s.size() == 2) return true;
        return is_name(s.substr(3));
      }
      
      // fwd for is_root_directory
      std::size_t root_directory_start(const string_type&);
      std::size_t root_directory_end(const string_type&);
      
      bool is_root_directory(const string_type& s, std::size_t pos)
      {
        auto spos = root_directory_start(s);
        if (!good(spos) || spos != pos) return false;
        auto epos = root_directory_end(s);
        return good(epos);
      }
      
      bool is_trailing_separator(const string_type& s, std::size_t pos)
      {
        return (good(pos) && is_separator(s, pos) &&
            end_of(s, pos) == s.size() - 1 && !is_root_directory(s, pos));
      }
      
      
    // index of observers
      
      std::size_t root_name_start(const string_type& s)
      {
        auto ret = root_name_end(s);
        if (!good(ret)) return npos;
        return 0;
      }
      
      
      std::size_t root_name_end(const std::string& s)
      {
        if (s.size() < 2 || s[0] != preferred_separator ||
          s[1] != preferred_separator)
            { return npos; }
        if (s.size() == 2) return 1; // off by one
        std::size_t index = 2; // current position
        if (s[index] == preferred_separator) return npos;
        while (index + 1 < s.size() && s[index + 1] != preferred_separator)
          ++index;
        return index;
      }
      
      
      std::size_t root_directory_start(const string_type& s)
      {
        auto e = root_name_end(s);
        if (!good(e))
          return is_separator(s, 0) ? 0 : npos;
        return is_separator(s, e + 1) ? e + 1 : npos; 
      }
      
      
      std::size_t root_directory_end(const std::string& s)
      {
        auto st = root_directory_start(s);
        if (!good(st)) return npos;
        std::size_t index = st;
        while (index + 1 < s.size() && s[index + 1] == preferred_separator)
          ++index;
        return index;
      }
      
      std::size_t filename_start(const string_type& s)
      {
        // start_of handles size == 0 case (npos is passed)
        return start_of(s, s.size()-1);
      }
      
      std::size_t filename_end(const std::string& s)
      {
        // filename_start will never succed on s.size() == 0
        // so s.size() - 1 never rolls over
        return good(filename_start(s)) ? s.size()-1 : npos;
      }
      
    // misc
      string_pair separate_filename(const std::string& s)
      {
        auto pos = s.find_last_of(preferred_separator);
        if (pos == string_type::npos) return string_pair{};
        return string_pair{s.substr(0, pos), s.substr(pos)};
      }
      
      
    // substring extraction
      string_type extract_raw(const string_type& s, std::size_t pos)
      {
        std::size_t end_i = end_of(s, pos);
        if (!good(end_i)) return string_type{};
        return s.substr(pos, end_i - pos + 1);
      }
      
      string_type extract_preferred(const string_type& s, std::size_t pos)
      {
        string_type raw = extract_raw(s, pos);
        if (raw.empty()) return raw;
        if (is_trailing_separator(s, pos)) return string_type{double_dot};
        if (is_separator(s, pos) && !is_root_name(s, pos))
          return string_type{} += preferred_separator;
        return s;
      }
      
      string_pair extract_pair(const string_type& s, std::size_t pos)
      {
        return string_pair{extract_raw(s, pos), extract_preferred(s, pos)};
      }
      
    } // namespace parser
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            path definitions                                                      
  ////////////////////////////////////////////////////////////////////////////////
    
    //decompasition
    path path::root_name() const
    {
      return parser::is_root_name(m_pathname, 0) 
        ? path{parser::extract_preferred(m_pathname, 0)}
        : path{};
    }
    
    path path::root_directory() const
    {
      auto start_i = parser::root_directory_start(m_pathname);
      if(!parser::good(start_i)) return path{};
      return path{parser::extract_raw(m_pathname, 0)};
    }
    
    path path::root_path() const
    {
      return root_name() / root_directory();
    }
    
    path path::relative_path() const
    {
      if (empty()) return path{};
      auto end_i = parser::root_directory_end(m_pathname);
      if (parser::good(end_i))
        return path{parser::extract_raw(m_pathname, end_i + 1)};
      else
        end_i = parser::root_name_end(m_pathname);
      if (!parser::good(end_i)) return path{};
      return path{parser::extract_raw(m_pathname, end_i+1)};
    }
    
    path path::parent_path() const
    {
      //TODO
      throw;
    }
    
    path path::filename() const
    {
      auto start_i = parser::filename_start(m_pathname);
      if(!parser::good(start_i)) return path{};
      return path{parser::extract_raw(m_pathname, start_i)};
    }
    
    path path::stem() const
    {
      return parser::separate_filename(filename()).first;
    }
    
    path path::extension() const
    {
      return parser::separate_filename(filename()).second;
    }
    
    typename path::iterator path::begin() const
    {
      iterator it{};
      it.m_path_ptr = this;
      set_iterator_pos(it, 0);
      return it;
    }
    
    typename path::iterator path::end() const
    {
      iterator it{};
      it.m_path_ptr = this;
      it.m_pos = parser::npos;
      it.m_element = path{};
      return it;
    }
    
    bool path::valid_iterator_position(iterator& it)
    {
      if (it.m_pos == parser::npos) return true;
      if (!parser::is_separator(it.m_path_ptr->native(), it.m_pos)) return true;
      return (parser::is_root_name(it.m_path_ptr->native(), it.m_pos) ||
          parser::is_root_directory(it.m_path_ptr->native(), it.m_pos) ||
          parser::is_trailing_separator(it.m_path_ptr->native(), it.m_pos));
    }
    
    typename path::iterator& path::increment_iterator(iterator& it)
    {
        if (!parser::good(it.m_pos))
          return it;
        set_iterator_pos(it, parser::end_of(it.m_path_ptr->native(), it.m_pos)+1);
        while (!valid_iterator_position(it))
          set_iterator_pos(it, parser::end_of(it.m_path_ptr->native(), it.m_pos)+1);
        return it;
    }
    
    typename path::iterator& path::decrement_iterator(iterator& it)
    {
      //TODO
      throw it;
    }
    
    typename path::iterator& 
      path::set_iterator_pos(iterator& it, std::size_t pos)
    {
      if (pos == parser::npos)
      {
        it.m_pos = parser::npos;
        it.m_element = path{};
      }
      else
      {
        it.m_element = path{parser::extract_raw(it.m_path_ptr->native(), pos)};
        it.m_pos = pos;
      }
      return it;
    }
    
    
    

  } // namespace fs
} // namespace elib
