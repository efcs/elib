#ifndef ELIB_ENUMERATION_ENUM_ITERATOR_HPP
# define ELIB_ENUMERATION_ENUM_ITERATOR_HPP

# include <elib/config.hpp>
# include <elib/enumeration/enum_helper.hpp>
# include <elib/enumeration/basic_enum_traits.hpp>
# include <elib/enumeration/enum_traits.hpp>

# include <elib/CXX14/type_traits.hpp>

# include <iterator>

namespace elib 
{
  namespace enumeration
  {
    
    namespace detail
    {
      
      template <class T>
      struct is_iterable : has_range<T>
      {};
      
      template <class T, bool=std::is_enum<T>::value>
      struct is_constexpr_range_iterable : std::false_type
      {};
      
      template <class T>
      struct is_constexpr_range_iterable<T, true>
        : std::integral_constant<bool, enum_traits<T>::has_constexpr_range>
      {};
      
      template <class T>
      struct is_name_map_iterable : has_name_map<T>
      {};
      
      template <class T>
      using enable_if_constexpr_iterable_t =
        std::enable_if_t<is_constexpr_range_iterable<T>::value>;
        
      template <class T>
      using enable_if_name_map_iterable_t =
        std::enable_if_t<
          is_name_map_iterable<T>::value
            && !is_constexpr_range_iterable<T>::value
        >;
        
      template <class T>
      using enable_if_iterable_t =
        std::enable_if_t<is_iterable<T>::value>;
      
      
      template <class T, class=void>
      class iter_impl;
      
      
      template <class T>
      class iter_impl<T, enable_if_constexpr_iterable_t<T>>
        : public std::iterator<std::bidirectional_iterator_tag, T>
      {
      private:
        static constexpr T m_end_value = 
          static_cast<T>(
            underlying_cast(enum_traits<T>::last_value) + 1
          );
        
      public:
        
        iter_impl()
          : m_val{m_end_value}
        {}
        
        explicit iter_impl(T val)
          : m_val{val}
        {}
        
        virtual ~iter_impl() = default;
        
      protected:
        
        const T& dereference() const
        { return m_val; }
        
        bool equals(const iter_impl& other) const
        {
          return (m_val == other.m_val);
        }
        
        void increment()
        {
          if (m_val != m_end_value)
            m_val = static_cast<T>(underlying_cast(m_val) + 1);
        }
        
        void decrement()
        {
          if (m_val != first_value<T>())
            m_val = static_cast<T>(underlying_cast(m_val) - 1);
        }

      private:
        
        T m_val {};
        
      };
      
      
      template <class T>
      class iter_impl<T, enable_if_name_map_iterable_t<T>>
        : public std::iterator<std::bidirectional_iterator_tag, T>
      {
      private:
        
        static_assert(has_name_map<T>::value, "must have name map");
        
        using btraits = basic_enum_traits<T>;
        
        using map_iterator = 
          typename decltype(btraits::name_map)::const_iterator;
          
      
      public:
        
        iter_impl()
          : m_iter{btraits::name_map.end()}
        {}
        
        explicit iter_impl(T pos)
          : m_iter{btraits::name_map.find(pos)}
        {}
        
        virtual ~iter_impl() = default;
        
      protected:
        
        const T& dereference() const
        { return m_iter->first; }
        
        bool equals(const iter_impl& other) const
        { return m_iter == other.m_iter; }
        
        void increment()
        { ++m_iter; }
        
        void decrement()
        { --m_iter; }
        
      private:
        
        map_iterator m_iter {};
        
      };                                           // class iter_impl(name_map)
      
      
    }                                                       // namespace detail
    
    
    template <typename T, class=detail::enable_if_iterable_t<T>>
    class enum_iterator 
      : public detail::iter_impl<T>
    {
    public:
      
      using detail::iter_impl<T>::iter_impl;
      
      virtual ~enum_iterator() = default;
      
      const T& operator*() const
      {
        return this->dereference();
      }
      
      bool operator==(const enum_iterator& other) const
      { return this->equals(other); }
      
      bool operator!=(const enum_iterator& other) const
      { return ! this->equals(other); }
      
      enum_iterator& operator++()
      {
        this->increment();
        return *this;
      }
      
      enum_iterator operator++(int)
      {
        auto cp = *this;
        this->increment();
        return cp;
      }
      
      enum_iterator& operator--()
      {
        this->decrement();
        return *this;
      }
      
      enum_iterator operator--(int)
      {
        auto cp = *this;
        this->decrement();
        return cp;
      }
      
      friend enum_iterator begin(const enum_iterator&)
      {
        return enum_iterator{first_value<T>()};
      }
      
      friend enum_iterator end(const enum_iterator&)
      {
        return enum_iterator{};
      }
      
    };                                                   // class enum_iterator
    
    
    
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_ITERATOR_HPP */