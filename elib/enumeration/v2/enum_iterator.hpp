#ifndef ELIB_ENUMERATION_ENUM_ITERATOR_HPP
# define ELIB_ENUMERATION_ENUM_ITERATOR_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v2/enum_traits.hpp>
# include <elib/enumeration/v2/enum_fields.hpp>

# include <elib/CXX14/type_traits.hpp>

# include <iterator>


namespace elib 
{
  namespace enumeration
  {
    
    template <typename T>
    struct is_enumerable : public has_range<T>
    { };
    
    
    
    namespace detail
    {
      
      
      template <typename T, typename=void>
      class iter_impl;
      
      template <typename T>
      class iter_impl<T, std::enable_if_t<has_constexpr_range<T>::value>>
      {
      public:
        iter_impl() noexcept
          : m_end{true}
        { };

        iter_impl(T e) noexcept
          : m_end{false}, m_val{e}
        { };
        
        iter_impl(const iter_impl&) = default;
        iter_impl& operator=(const iter_impl&) = default;

        iter_impl(iter_impl&&) noexcept = default;
        iter_impl& operator=(iter_impl&&) noexcept = default;

        ~iter_impl() noexcept = default;
        
        const T& operator*() const
        { return m_val; }
        
        
        void increment()
        {
          if (m_end) return;
          if (m_val == last_value)
            make_end();
          else
            m_val = static_cast<T>(static_cast<underlying_type>(m_val) + 1);
        }
        
        void decrement()
        {
          if (m_end || m_val == first_value)
            return;
          
          m_val = static_cast<T>(static_cast<underlying_type>(m_val) - 1);
        }
        
        void make_end()
        {
          m_end = true;
          m_val = static_cast<T>(-1);
        }
        
        bool operator==(const iter_impl& rhs) const noexcept
        {
          if (m_end && rhs.m_end) return true;
          if (m_end != rhs.m_end) return false;
          return m_val == rhs.m_val;
        }

        //
      private:
        //
        
        typedef typename std::underlying_type<T>::type underlying_type;
        static constexpr T first_value = first_field_value<T>::value;
        static constexpr T last_value = last_field_value<T>::value;
        
        
        bool m_end;
        T m_val{};

      };                                                          // class iter_impl
      
      template <typename T>
      class iter_impl<T, std::enable_if_t<has_range<T>::value && 
                              !has_constexpr_range<T>::value>>
      {
      public:
        iter_impl() noexcept = default;
        
        iter_impl(T e)
          : m_it{basic_enum_traits<T>::name_map.begin()}
        { 
          auto end_it = basic_enum_traits<T>::name_map.end();
          while (m_it != end_it && m_it->first != e)
            m_it++;
        }

        iter_impl(const iter_impl&) = default;
        iter_impl& operator=(const iter_impl&) = default;

        iter_impl(iter_impl&&) noexcept = default;
        iter_impl& operator=(iter_impl&&) noexcept = default;

        ~iter_impl() noexcept = default;
        
        const T& operator*() const
        { return m_it->first; }
        
        void increment()
        {
          if (*this == iter_impl{}) return;
          ++m_it;
        }
        
        void decrement()
        {
          if (*this == iter_impl{}) return;
          --m_it;
        }
        
        void make_end()
        {
          m_it = iter_type{};
        }
        
        bool operator==(const iter_impl& rhs) const noexcept
        { return m_it == rhs.m_it; }

      //
      private:
      //
      
        typedef typename basic_enum_traits<T>::name_map::iterator iter_type;
        iter_type m_it{};
        
      };                                                     // class iter_impl
    
      
    }                                                       // namespace detail
    
    
    template <typename EnumT>
    class enum_iterator 
      : public std::iterator<std::bidirectional_iterator_tag, const EnumT>
    {
    public:
      enum_iterator() noexcept = default;
      
      enum_iterator(EnumT e)
        : m_impl{e}
      { };

      enum_iterator(const enum_iterator&) = default;
      enum_iterator& operator=(const enum_iterator&) = default;

      enum_iterator(enum_iterator&&) noexcept = default;
      enum_iterator& operator=(enum_iterator&&) noexcept = default;

      ~enum_iterator() noexcept = default;
      
      const EnumT& operator*() const
      { return *m_impl; }
      
      enum_iterator& operator++()
      { return increment(); }
      
      enum_iterator operator++(int)
      { 
        auto cp = *this;
        increment();
        return cp;
      }
      
      enum_iterator& increment()
      {
        m_impl.increment();
        return *this;
      }
      
      enum_iterator& operator--()
      { return decrement(); }
      
      enum_iterator operator--(int)
      { 
        auto cp = *this;
        decrement();
        return cp;
      }
      
      enum_iterator& decrement()
      {
        m_impl.decrement();
        return *this;
      }
      
      bool operator==(const enum_iterator& rhs) const noexcept
      { return m_impl == rhs.m_impl; }
      
      bool operator!=(const enum_iterator& rhs) const noexcept
      { return !(*this == rhs); }
      
    //
    private:
    //
      
      detail::iter_impl<EnumT> m_impl{};
    
    };                                                   // class enum_iterator
    
    
    template <typename T>
    std::enable_if_t<is_enumerable<T>::value, enum_iterator<T>>
    begin();

    template <typename T>
    std::enable_if_t<is_enumerable<T>::value, enum_iterator<T>>
    end();
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_ITERATOR_HPP */