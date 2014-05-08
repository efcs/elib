#ifndef ELIB_ENUMERATION_ITERATOR_HPP
#define ELIB_ENUMERATION_ITERATOR_HPP

# include <elib/enumeration/basic_traits.hpp>
# include <elib/enumeration/cast.hpp>
# include <elib/enumeration/traits.hpp>
# include <elib/aux/traits/underlying_type.hpp>
# include <iterator>

namespace elib { namespace enumeration
{
    
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        template <
            class T
          , bool HasConstexprRange = has_constexpr_range<T>::value
          , bool HasNameMap = has_name_map<T>::value
          >
        class iter_impl;
        
        ////////////////////////////////////////////////////////////////////////
        template <class T, bool HasNameMap>
        class iter_impl<T, true, HasNameMap>
            : public std::iterator<std::bidirectional_iterator_tag, T const>
        {
        private:
            using underlying_type = aux::underlying_type_t<T>;
            
            static constexpr T m_end_value = 
            static_cast<T>(
                underlying_cast(enum_traits<T>::last_value) + 1
            );
            
        public:
            
            constexpr iter_impl()
              : m_val(m_end_value)
            {}
            
            constexpr explicit iter_impl(T val)
              : m_val(val)
            {}
            
        protected:
            
            const T & dereference() const noexcept
            { 
                return m_val; 
            }
            
            bool equals(const iter_impl& other) const
            {
                return (m_val == other.m_val);
            }
            
            void increment()
            {
                m_val = (m_val != m_end_value) 
                    ? static_cast<T>(underlying_cast(m_val) + 1)
                    : m_val;
            }
            
            void decrement()
            {
                m_val = static_cast<T>(
                    enumeration::underlying_cast(m_val) - 1
                  );
            }

        private:
            T m_val;
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        class iter_impl<T, false, true>
            : public std::iterator<std::bidirectional_iterator_tag, T const>
        {
        private:
            static_assert(has_name_map<T>::value, "must have name map");
            using btraits = basic_enum_traits<T>;
            using map_iterator = typename decltype(btraits::name_map)::const_iterator;    
            
        public:
            iter_impl()
            : m_iter{btraits::name_map.end()}
            {}
            
            explicit iter_impl(T pos)
            : m_iter{btraits::name_map.find(pos)}
            {}
            
        protected:
            constexpr const T& dereference() const
            { return m_iter->first; }
            
            constexpr bool equals(const iter_impl& other) const
            { return m_iter == other.m_iter; }
            
            void increment()
            { ++m_iter; }
            
            void decrement()
            { --m_iter; }
            
        private:
            map_iterator m_iter {};
        };
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <typename T>
    class enum_iterator 
      : public detail::iter_impl<T>
    {
        static_assert(has_range<T>::value, "T must satisfy has_range<T>");
        using base_type = detail::iter_impl<T>;
    public:
        
        constexpr enum_iterator()
          : base_type()
        {}
        
        constexpr explicit enum_iterator(T v)
          : base_type(v)
        {}
        
        const T& operator*() const
        {
            return this->dereference();
        }
        
        bool operator==(const enum_iterator& other) const
        { return this->equals(other); }
        
        bool operator!=(const enum_iterator& other) const
        { return not this->equals(other); }
        
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
    };                                                   // class enum_iterator
    
}}                                                          // namespace elib
#endif /* ELIB_ENUMERATION_ITERATOR_HPP */