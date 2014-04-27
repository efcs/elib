#ifndef ELIB_CONTAINER_DETAIL_FLAT_MAP_BASE_HPP
#define ELIB_CONTAINER_DETAIL_FLAT_MAP_BASE_HPP

# include <elib/aux.hpp>
# include <algorithm>
# include <initializer_list>
# include <stdexcept>
# include <utility>
# include <vector>

namespace elib { namespace container 
{
    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <
            class Key, class T
          , class Compare
          >
        class flat_map_compare
        {
        public:
            using key_type = Key;
            using mapped_type = T;
            using value_type = std::pair<Key, T>;
            using key_compare = Compare;
            
        public:
            flat_map_compare()
              : m_cmp()
            {}
            
            flat_map_compare(Compare c)
              : m_cmp(c)
            {}
            
            flat_map_compare(flat_map_compare const &) = default;
            flat_map_compare(flat_map_compare &&) = default;
            flat_map_compare & operator=(flat_map_compare const &) = default;
            flat_map_compare & operator=(flat_map_compare &&) = default;
            
        public:
            key_compare key_comp() const
            {
                return m_cmp;
            }
            
        public:
            bool operator()(value_type const & lhs, value_type const & rhs) const
            {
                return m_cmp(lhs.first, rhs.first);
            }
            
            bool operator()(value_type const & lhs, Key const & rhs) const
            {
                return m_cmp(lhs.first, rhs);
            }
            
            bool operator()(Key const & lhs, Key const & rhs) const
            {
                return m_cmp(lhs, rhs);
            }
    
            bool operator()(Key const & lhs, value_type const & rhs) const
            {
                return m_cmp(lhs, rhs.first);
            }
            
        private:
            Compare m_cmp;
        };
    
    }                                                       // namespace detail
    
    template <
        class Key, class T
      , class Compare
      >
    class flat_map_base
    {
    private:
        using compare_type = detail::flat_map_compare<Key, T, Compare>;
    public:
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<Key, T>;
        
        // the underlying container used
        using storage_type = std::vector<value_type>;
        
        using size_type = typename storage_type::size_type;
        using difference_type = typename storage_type::difference_type;
        using key_compare = Compare;
        
        using reference = value_type &;
        using const_reference = value_type const &;
        using pointer = value_type *;
        using const_pointer = value_type const *;
        
        using iterator = typename storage_type::iterator;
        using const_iterator = typename storage_type::const_iterator;
        using reverse_iterator = typename storage_type::reverse_iterator;
        using const_reverse_iterator = typename storage_type::const_reverse_iterator;
    
    public:
        class value_compare
        {
        protected:
            friend class flat_map_base;
            Compare comp;
            
            value_compare(Compare c)
              : comp(elib::move(c))
            {}
            
        public:
            value_compare(value_compare const &) = default;
            value_compare(value_compare &&) = default;
            value_compare & operator=(value_compare const &) = default;
            value_compare & operator=(value_compare &&) = default;
            
            using result_type = bool;
            using first_argument_type = value_type;
            using second_argument_type = value_type;
            
            bool operator()(value_type const & lhs, value_type const & rhs) const
            { return comp(lhs.first, rhs.first); }
        };
        
    public:
        ////////////////////////////////////////////////////////////////////////
        flat_map_base()
            noexcept( elib::and_<
                aux::is_nothrow_default_constructible<Compare>
              , aux::is_nothrow_copy_constructible<Compare>
              >::value
            )
          : flat_map_base( Compare() )
        {}
        
        ////////////////////////////////////////////////////////////////////////
        explicit flat_map_base(Compare const & cmp)
            noexcept(aux::is_nothrow_copy_constructible<Compare>::value)
          : m_cmp(cmp), m_store()
        {}
        
        ////////////////////////////////////////////////////////////////////////
        template <class InputIt>
        flat_map_base(InputIt first, InputIt last)
          : m_cmp(), m_store(first, last)
        {
            std::stable_sort(begin(), end(), m_cmp);
            auto end_pos = std::unique(
                begin(), end()
              , [](value_type const & lhs, value_type const & rhs)
                { return lhs.first == rhs.first; }
              );
            m_store.erase(end_pos, end());
        }
        
        ////////////////////////////////////////////////////////////////////////
        flat_map_base(std::initializer_list<value_type> il)
          : flat_map_base(il.begin(), il.end())
        {}

        ////////////////////////////////////////////////////////////////////////
        flat_map_base(flat_map_base const &) = default;
        
        ////////////////////////////////////////////////////////////////////////
        flat_map_base(flat_map_base && other)
            noexcept(elib::and_<
                aux::is_nothrow_move_constructible<compare_type>
              , aux::is_nothrow_move_constructible<storage_type>
              >::value
            )
            : m_cmp(elib::move(other.m_cmp))
            , m_store(elib::move(other.m_store)) 
        {}
        
        ////////////////////////////////////////////////////////////////////////
        ~flat_map_base() = default;
        
    protected:
        flat_map_base & operator=(flat_map_base const &) = default;
        flat_map_base & operator=(flat_map_base &&) = default;
        
        flat_map_base & operator=(std::initializer_list<value_type> il)
        {
            std::vector<value_type>(il.begin(), il.end()).swap(m_store);
            return *this;
        }
        
    public:
        ////////////////////////////////////////////////////////////////////////
        T & linear_at(Key const & k)
        {
            auto pos = linear_find(k);
            if (pos == end()) {
                throw std::out_of_range("Key is not in the flat_map_base");
            }
            return pos->second;
        }
        
        T const & linear_at(Key const & k) const
        {
            return const_cast<flat_map_base &>(*this).linear_at(k);
        }
        
        T & log_at(Key const & k)
        {
            auto pos = log_find(k);
            if (pos == end()) {
                throw std::out_of_range("Key is not in the flat_map_base");
            }
            return pos->second;
        }
        
        T const & log_at(Key const & k) const
        {
            return const_cast<flat_map_base &>(*this).log_at(k);
        }
        
        ////////////////////////////////////////////////////////////////////////
        T & linear_get(Key const & k)
        {
            auto pos = linear_lower_bound(k);
            if (pos != end() && pos->first == k) {
                return pos->second;
            }
            return m_store.insert(pos, value_type(k, T()))->second;
        }
        
        T & linear_get(Key && k)
        {
            auto pos = linear_lower_bound(k);
            if (pos != end() && pos->first == k) {
                return pos->second;
            }
            return m_store.insert(pos, value_type(elib::move(k), T()))->second;
        }
        
        T & log_get(Key const & k)
        {
            auto pos = log_lower_bound(k);
            if (pos != end() && pos->first == k) {
                return pos->second;
            }
            return m_store.insert(pos, value_type(k, T()))->second;
        }
        
        T & log_get(Key && k)
        {
            auto pos = log_lower_bound(k);
            if (pos != end() && pos->first == k) {
                return pos->second;
            }
            return m_store.insert(pos, value_type(elib::move(k), T()))->second;
        }
        
    public:
        ////////////////////////////////////////////////////////////////////////
        iterator begin()
        {
            return m_store.begin();
        }
        
        const_iterator begin() const
        {
            return m_store.begin();
        }
        
        const_iterator cbegin() const
        {
            return m_store.begin();
        }
        
        ////////////////////////////////////////////////////////////////////////
        iterator end()
        {
            return m_store.end();
        }
        
        const_iterator end() const
        {
            return m_store.end();
        }
        
        const_iterator cend() const
        {
            return m_store.end();
        }
        
        ////////////////////////////////////////////////////////////////////////
        reverse_iterator rbegin()
        {
            return m_store.rbegin();
        }
        
        const_reverse_iterator rbegin() const
        {
            return m_store.rbegin();
        }
        
        const_reverse_iterator crbegin() const
        {
            return m_store.rbegin();
        }
        
        ////////////////////////////////////////////////////////////////////////
        reverse_iterator rend()
        {
            return m_store.rend();
        }
        
        const_reverse_iterator rend() const
        {
            return m_store.rend();
        }
        
        const_reverse_iterator crend() const
        {
            return m_store.rend();
        }

    public:
        bool empty() const
        {
            return m_store.empty();
        }
        
        size_type size() const
        {
            return m_store.size();
        }
        
        size_type max_size() const
        {
            return m_store.max_size();
        }
        
        void reserve(size_type n)
        {
            m_store.reserve(n);
        }
        
        size_type capacity() const
        {
            return m_store.capacity();
        }
        
        void shrink_to_fit()
        {
            m_store.shrink_to_fit();
        }
        
    public:
        ////////////////////////////////////////////////////////////////////////
        void clear()
        {
            m_store.clear();
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::pair<iterator, bool> 
        linear_insert(value_type const & v)
        {
            auto pos = linear_lower_bound(v.first);
            if (pos != end() && pos->first == v.first) {
                return std::make_pair(pos, false);
            }
            return std::make_pair(m_store.insert(pos, v), true);
        }
        
        std::pair<iterator, bool> 
        log_insert(value_type const & v)
        {
            auto pos = log_lower_bound(v.first);
            if (pos != end() && pos->first == v.first) {
                return std::make_pair(pos, false);
            }
            return std::make_pair(m_store.insert(pos, v), true);
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class P
          , ELIB_ENABLE_IF(aux::is_constructible<value_type, P &&>::value)
          >
        std::pair<iterator, bool> 
        linear_insert(P && p)
        { return linear_emplace(elib::forward<P>(p)); }
        
        template <
            class P
          , ELIB_ENABLE_IF(aux::is_constructible<value_type, P &&>::value)
          >
        std::pair<iterator, bool> 
        log_insert(P && p)
        { return log_emplace(elib::forward<P>(p)); }
        
        ////////////////////////////////////////////////////////////////////////
        iterator linear_insert(const_iterator, value_type const & v)
        { return linear_insert(v).first; }
        
        iterator log_insert(const_iterator, value_type const & v)
        { return log_insert(v).first; }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class P
          , ELIB_ENABLE_IF(aux::is_constructible<value_type, P &&>::value)
          >
        iterator linear_insert(const_iterator, P && p)
        { return linear_emplace(elib::forward<P>(p)).first; }
        
        template <
            class P
          , ELIB_ENABLE_IF(aux::is_constructible<value_type, P &&>::value)
          >
        iterator log_insert(const_iterator, P && p)
        { return log_emplace(elib::forward<P>(p)).first; }
        
        ////////////////////////////////////////////////////////////////////////
        template <class InputIt>
        void linear_insert(InputIt first, InputIt last)
        {
            for (; first != last; ++first) {
                linear_insert(*first);
            }
        }
        
        template <class InputIt>
        void log_insert(InputIt first, InputIt last)
        {
            for (; first != last; ++first) {
                log_insert(*first);
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        void linear_insert(std::initializer_list<value_type> il)
        { linear_insert(il.begin(), il.end()); }
        
        void log_insert(std::initializer_list<value_type> il)
        { log_insert(il.begin(), il.end()); }
        
        ////////////////////////////////////////////////////////////////////////
        template <class ...Args>
        std::pair<iterator, bool> 
        linear_emplace(Args &&... args)
        {
            value_type tmp(elib::forward<Args>(args)...);
            auto pos = linear_lower_bound(tmp.first);
            if (pos != end() && pos->first == tmp.first) {
                return std::make_pair(pos, false);
            }
            return std::make_pair(m_store.emplace(pos, elib::move(tmp)), true);
        }
        
        template <class ...Args>
        std::pair<iterator, bool> 
        log_emplace(Args &&... args)
        {
            value_type tmp(elib::forward<Args>(args)...);
            auto pos = log_lower_bound(tmp.first);
            if (pos != end() && pos->first == tmp.first) {
                return std::make_pair(pos, false);
            }
            return std::make_pair(m_store.emplace(pos, elib::move(tmp)), true);
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class ...Args>
        iterator linear_emplace_hint(const_iterator, Args &&... args)
        { return linear_emplace(elib::forward<Args>(args)...).first; }
        
        template <class ...Args>
        iterator log_emplace_hint(const_iterator, Args &&... args)
        { return log_emplace(elib::forward<Args>(args)...).first; }
        
        ////////////////////////////////////////////////////////////////////////
        iterator erase(const_iterator pos)
        {
#   if defined(ELIB_CONFIG_LIBSTDCXX) && ELIB_LIBRARY_VERSION < 20140108L
            auto non_const_pos = begin() + (pos - cbegin());
            return m_store.erase(non_const_pos);
#   else
            return m_store.erase(pos);
#   endif
        }
        
        iterator erase(const_iterator first, const_iterator last)
        {
#   if defined(ELIB_CONFIG_LIBSTDCXX) && ELIB_LIBRARY_VERSION < 20140108L
            auto non_const_first = begin() + (first - cbegin());
            auto non_const_last = begin() + (last - cbegin());
            return m_store.erase(non_const_first, non_const_last);
#    else
            return m_store.erase(first, last);
#    endif
        }
        
        
        size_type linear_erase(Key const & k)
        {
            auto pos = linear_find(k);
            if (pos == end()) return 0;
            m_store.erase(pos);
            return 1;
        }
        
        size_type log_erase(Key const & k)
        {
            auto pos = log_find(k);
            if (pos == end()) return 0;
            m_store.erase(pos);
            return 1;
        }
        
        ////////////////////////////////////////////////////////////////////////
        void swap(flat_map_base & other)
        {
            using std::swap;
            swap(m_cmp, other.m_cmp);
            swap(m_store, other.m_store);
        }

    public:
        
        size_type linear_count(Key const & k) const
        { return linear_find(k) != end(); }
        
        size_type log_count(Key const & k) const
        { return log_find(k) != end(); }
        
        ////////////////////////////////////////////////////////////////////////
        iterator linear_find(Key const & k)
        {
            auto pos = linear_lower_bound(k);
            if (pos == end() || pos->first == k) return pos;
            return end();
        }
        
        const_iterator linear_find(Key const & k) const
        {
            auto pos = linear_lower_bound(k);
            if (pos == end() || pos->first == k) return pos;
            return end();
        }
        
        ////////////////////////////////////////////////////////////////////////
        iterator log_find(Key const & k)
        {
            auto pos = log_lower_bound(k);
            if (pos == end() || pos->first == k) return pos;
            return end();
        }
        
        const_iterator log_find(Key const & k) const
        {
            auto pos = log_lower_bound(k);
            if (pos == end() || pos->first == k) return pos;
            return end();
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::pair<iterator, iterator>
        linear_equal_range(Key const & k)
        {
            return std::make_pair(linear_lower_bound(k), linear_upper_bound(k));
        }
        
        std::pair<const_iterator, const_iterator>
        linear_equal_range(Key const & k) const
        {
            return std::make_pair(linear_lower_bound(k), linear_upper_bound(k));
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::pair<iterator, iterator>
        log_equal_range(Key const & k)
        {
            return std::equal_range(begin(), end(), k, m_cmp);
        }
        
        std::pair<const_iterator, const_iterator> 
        log_equal_range(Key const & k) const
        {
            return std::equal_range(begin(), end(), k, m_cmp);
        }
        
        ////////////////////////////////////////////////////////////////////////
        iterator linear_lower_bound(Key const & k)
        {
            auto pos = begin();
            auto const xend = end();
            while (pos != xend && m_cmp(*pos, k)) {
                ++pos;
            }
            return pos;
        }
        
        const_iterator linear_lower_bound(Key const & k) const
        {
            auto pos = begin();
            auto const xend = end();
            while (pos != xend && m_cmp(*pos, k)) {
                ++pos;
            }
            return pos;
        }
        
        ////////////////////////////////////////////////////////////////////////
        iterator log_lower_bound(Key const & k)
        { return std::lower_bound(begin(), end(), k, m_cmp); }
        
        const_iterator log_lower_bound(Key const & k) const
        { return std::lower_bound(begin(), end(), k, m_cmp); }
        
        
        ////////////////////////////////////////////////////////////////////////
        iterator linear_upper_bound(Key const & k)
        {
            auto pos = begin();
            auto const xend = end();
            while (pos != xend && not m_cmp(k, *pos)) {
                ++pos;
            }
            return pos;
        }
        
        const_iterator linear_upper_bound(Key const & k) const
        {
            auto pos = begin();
            auto const xend = end();
            while (pos != xend && not m_cmp(k, *pos)) {
                ++pos;
            }
            return pos;
        }
        
        ////////////////////////////////////////////////////////////////////////
        iterator log_upper_bound(Key const & k)
        {
            return std::upper_bound(begin(), end(), k, m_cmp);
        }
        
        const_iterator log_upper_bound(Key const & k) const
        {
            return std::upper_bound(begin(), end(), k, m_cmp);
        }
        
    public:
        key_compare key_comp() const
        {
            return m_cmp.key_comp();
        }
        
        value_compare value_comp() const
        {
            return value_compare(m_cmp.key_comp());
        }
        
    private:
        compare_type m_cmp;
        std::vector<value_type> m_store;
    };
    
    template <class Key, class T, class Compare>
    void swap(
        flat_map_base<Key, T, Compare> & lhs
      , flat_map_base<Key, T, Compare> & rhs
      )
    {
        lhs.swap(rhs);
    }
    
    template <class Key, class T, class Compare>
    bool operator==(
        flat_map_base<Key, T, Compare> const & lhs
      , flat_map_base<Key, T, Compare> const & rhs
      )
    {
        if (lhs.size() != rhs.size()) return false;
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    
    template <class Key, class T, class Compare>
    bool operator !=(
        flat_map_base<Key, T, Compare> const & lhs
      , flat_map_base<Key, T, Compare> const & rhs
      )
    {
        return !(lhs == rhs);
    }
    
    template <class Key, class T, class Compare>
    bool operator<(
        flat_map_base<Key, T, Compare> const & lhs
      , flat_map_base<Key, T, Compare> const & rhs
      )
    {
        return std::lexicographical_compare(
            lhs.begin(), lhs.end()
          , rhs.begin(), rhs.end()
          , lhs.value_comp()
          );
    }
    
    template <class Key, class T, class Compare>
    bool operator>(
        flat_map_base<Key, T, Compare> const & lhs
      , flat_map_base<Key, T, Compare> const & rhs
      )
    {
        return (rhs < lhs);
    }
    
    template <class Key, class T, class Compare>
    bool operator<=(
        flat_map_base<Key, T, Compare> const & lhs
      , flat_map_base<Key, T, Compare> const & rhs
      )
    {
        return !(lhs > rhs);
    }
    
    template <class Key, class T, class Compare>
    bool operator>=(
        flat_map_base<Key, T, Compare> const & lhs
      , flat_map_base<Key, T, Compare> const & rhs
      )
    {
        return !(lhs < rhs);
    }
    
}}                                                          // namespace elib
#endif /* ELIB_CONTAINER_DETAIL_FLAT_MAP_BASE_HPP */