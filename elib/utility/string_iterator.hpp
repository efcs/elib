#ifndef ELIB_STRING_ITERATOR_HPP
# define ELIB__STRING_ITERATOR_HPP

# include <elib/config.hpp>

# include <string>
# include <iterator>
# include <cstddef>


namespace elib 
{
  
  namespace detail
  {
    
    
    template <typename T>
    struct string_iterator_traits;
    
    
    template <>
    struct string_iterator_traits<std::string>
    {
      typedef std::string string_type;
      typedef char value_type;
    };                                         // struct string_iterator_traits
    
    
    template <>
    struct string_iterator_traits<const std::string>
    {
      typedef const std::string string_type;
      typedef const char value_type;
    };                                         // struct string_iterator_traits
    
    
  }                                                         // namespace detail
  
  
  template <class StringT>
  class basic_string_iterator
  {
  public:
    
    typedef typename detail::string_iterator_traits<StringT>::string_type
                                                              string_type;
                                                              
    typedef typename detail::string_iterator_traits<StringT>::value_type
                                                              value_type;
  
    typedef value_type& reference;
    typedef value_type* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    basic_string_iterator() noexcept
      : m_str_ptr{nullptr}, m_pos{static_cast<std::size_t>(-1)}
    { }

    explicit basic_string_iterator(string_type& s) noexcept
      : m_str_ptr{&s}, m_pos{0}
    { }
    
    basic_string_iterator(string_type& s, std::size_t pos) noexcept
      : m_str_ptr{&s}, m_pos{pos}
    { }

    basic_string_iterator(const basic_string_iterator& other) noexcept = default;
    basic_string_iterator(basic_string_iterator&& other) noexcept = default;
    basic_string_iterator& operator=(const basic_string_iterator& other) noexcept = default;
    basic_string_iterator& operator=(basic_string_iterator&& other) noexcept = default;
    
    ~basic_string_iterator() noexcept = default;


    const std::string& str() const noexcept
    {
      return *m_str_ptr;
    }
    
    std::size_t pos() const noexcept
    {
      return m_pos;
    }

    bool good() const noexcept
    {
      return (m_str_ptr != nullptr);
    }

    bool is_end() const noexcept
    {
      return (!good() || m_pos == str().size());
    }


    reference operator*() noexcept
    {
      return (*m_str_ptr)[m_pos];
    }

    basic_string_iterator& increment()
    {
      return m_advance(1);
    }

    basic_string_iterator& operator++()
    {
      return increment();
    }

    basic_string_iterator operator++(int)
    {
      auto tmp = *this;
      increment();
      return tmp;
    }

    basic_string_iterator& decrement()
    {
      return m_advance(-1);
    }

    basic_string_iterator& operator--()
    {
      return decrement();
    }

    basic_string_iterator operator--(int)
    {
      auto tmp = *this;
      decrement();
      return tmp;
    }

    bool operator==(const basic_string_iterator& other) const noexcept
    {
      return (m_str_ptr == other.m_str_ptr && m_pos == other.m_pos);
    }

    bool operator!=(const basic_string_iterator& other) const noexcept
    {
      return !(*this == other);
    }


    bool operator <(const basic_string_iterator& other) const noexcept
    {
      return m_pos < other.m_pos;
    }

    bool operator <=(const basic_string_iterator& other) const noexcept
    {
      return (m_pos <= other.m_pos);
    }

    bool operator >(const basic_string_iterator& other) const noexcept
    {
      return (m_pos > other.m_pos);
    }

    bool operator >=(const basic_string_iterator& other) const noexcept
    {
      return (m_pos >= other.m_pos);
    }

    basic_string_iterator& operator+=(difference_type n) noexcept
    {
      return m_advance(n);
    }

    basic_string_iterator operator+(difference_type n) const noexcept
    {
      auto tmp = *this;
      tmp += n;
      return tmp;
    }

    basic_string_iterator& operator-=(difference_type n) noexcept
    {
      return (*this += -n);
    }

    basic_string_iterator operator-(difference_type n) const noexcept
    {
      auto tmp = *this;
      tmp -= n;
      return tmp;
    }

    basic_string_iterator operator[](difference_type n) const noexcept
    {
      auto tmp = *this;
      tmp += n;
      return tmp;
    }
    
    template <class T>
    friend basic_string_iterator<T> begin(basic_string_iterator<T> it);
    
    template <class T>
    friend basic_string_iterator<T> end(basic_string_iterator<T> it);

  private:

    basic_string_iterator& m_advance(difference_type diff) noexcept
    {
      if (diff >= 0)
      {
        m_pos += diff;
        m_check_end();
      }
      else                                              // diff < 0; decrement by -n
      {
        // diff is now positive
        diff = -diff;
        // prevent 0 wrap-around
        if (diff > m_pos)
        diff = m_pos;
        m_pos -= diff;
      }
      
      return *this;
    }

    bool m_past_end() const noexcept
    {
      return (m_pos >= m_str_ptr->size());
    }

    void m_make_end() noexcept
    {
      m_pos = m_str_ptr->size();
    }

    void m_check_end() noexcept
    {
      if (m_past_end())
      m_make_end();
    }

    string_type *m_str_ptr{nullptr};
    std::size_t m_pos{static_cast<std::size_t>(-1)};
    
  };                                             // class basic_string_iterator
  
  typedef basic_string_iterator<std::string> string_iterator;
  typedef basic_string_iterator<const std::string> const_string_iterator;
  
  template <class T>
  basic_string_iterator<T> begin(basic_string_iterator<T> it)
  {
    it.m_pos = 0;
    return it;
  }
  
  template <class T>
  basic_string_iterator<T> end(basic_string_iterator<T> it)
  {
    if (it.good())
      it.m_pos = it.str().size();
    else
      it.m_pos = 0;
    return it;
  }
  
  
}                                                           // namespace elib
#endif /* ELIB__STRING_ITERATOR_HPP */