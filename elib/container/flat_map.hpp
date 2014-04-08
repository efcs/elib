#ifndef ELIB_CONTAINER_FLAT_MAP_HPP
#define ELIB_CONTAINER_FLAT_MAP_HPP

# include <elib/container/detail/flat_map_base.hpp>
# include <elib/aux.hpp>
# include <functional> /* std::less */
# include <initializer_list>
# include <utility> /* std::pair */

namespace elib { namespace container
{
    template <
        class Key, class T
      , class Compare = std::less<Key>
      >
    class flat_map
      : public flat_map_base<Key, T, Compare>
    {
    private:
        using base_type = flat_map_base<Key, T, Compare>;
        
    public:
        using key_type = typename base_type::key_type;
        using mapped_type = typename base_type::mapped_type;
        using value_type = typename base_type::value_type;
        
        using size_type = typename base_type::size_type;
        using difference_type = typename base_type::difference_type;
        using key_compare = typename base_type::key_compare;
        
        using reference = typename base_type::reference;
        using const_reference = typename base_type::const_reference;
        using pointer = typename base_type::pointer;
        using const_pointer = typename base_type::const_pointer;
        
        using iterator = typename base_type::iterator;
        using const_iterator = typename base_type::const_iterator;
        using reverse_iterator = typename base_type::reverse_iterator;
        using const_reverse_iterator = typename base_type::const_reverse_iterator;
    
    public:
        flat_map() = default;
        flat_map(flat_map const &) = default;
        flat_map(flat_map &&) = default;
        
        using base_type::base_type;
        
        ~flat_map() = default;
        
    public:
        flat_map & operator=(flat_map const &) = default;
        flat_map & operator=(flat_map &&) = default;
        
        flat_map & operator=(std::initializer_list<value_type> il)
        {
            base_type::operator=(il);
            return *this;
        }
        
    public:
        ////////////////////////////////////////////////////////////////////////
        T & at(Key const & k)
        { return base_type::log_at(k); }
        
        T const & at(Key const & k) const
        { return base_type::log_at(k); }
        
        ////////////////////////////////////////////////////////////////////////
        T & operator[](Key const & k)
        { return base_type::log_get(k); }
        
        T & operator[](Key && k)
        { return base_type::log_get(elib::move(k)); }
        
    public:
        ////////////////////////////////////////////////////////////////////////
        std::pair<iterator, bool>
        insert(value_type const & v)
        { return base_type::log_insert(v); }
        
        template <
            class P
          , ELIB_ENABLE_IF(aux::is_constructible<value_type, P &&>::value)
          >
        std::pair<iterator, bool>
        insert(P && p)
        { return base_type::log_insert(elib::forward<P>(p)); }
        
        iterator insert(const_iterator pos, value_type const & v)
        { return base_type::log_insert(pos, v); }
        
         template <
            class P
          , ELIB_ENABLE_IF(aux::is_constructible<value_type, P &&>::value)
          >
        iterator insert(const_iterator pos, P && p)
        { return base_type::log_insert(pos, elib::forward<P>(p)); }
        
        template <class InputIt>
        void insert(InputIt first, InputIt last)
        { base_type::log_insert(first, last); }
        
        void insert(std::initializer_list<value_type> il)
        { base_type::log_insert(il); }
        
        ////////////////////////////////////////////////////////////////////////
        template <class ...Args>
        std::pair<iterator, bool> 
        emplace(Args &&... args)
        { return base_type::log_emplace(elib::forward<Args>(args)...); }
        
        template <class ...Args>
        iterator emplace_hint(const_iterator pos, Args &&... args)
        { 
            return base_type::log_emplace_hint(
                pos, elib::forward<Args>(args)...
              ); 
        }
        
        ////////////////////////////////////////////////////////////////////////
        size_type erase(Key const & k)
        { return base_type::log_erase(k); }
        
        using base_type::erase;
        
        ////////////////////////////////////////////////////////////////////////
        void swap(flat_map & other)
        { base_type::swap(other); }
    public:
        ////////////////////////////////////////////////////////////////////////
        size_type count(Key const & k) const
        { return base_type::log_count(k); }
        
        ////////////////////////////////////////////////////////////////////////
        std::pair<iterator, iterator>
        equal_range(Key const & k)
        { return base_type::log_equal_range(k); }
        
        std::pair<const_iterator, const_iterator>
        equal_range(Key const & k) const
        { return base_type::log_equal_range(k); }
        
        ////////////////////////////////////////////////////////////////////////
        iterator find(Key const & k)
        { return base_type::log_find(k); }
        
        const_iterator find(Key const & k) const
        { return base_type::log_find(k); }
        
        ////////////////////////////////////////////////////////////////////////
        iterator lower_bound(Key const & k)
        { return base_type::log_lower_bound(k); }
        
        const_iterator lower_bound(Key const & k) const
        { return base_type::log_lower_bound(k); }
        
        ////////////////////////////////////////////////////////////////////////
        iterator upper_bound(Key const & k)
        { return base_type::log_upper_bound(k); }
        
        const_iterator upper_bound(Key const & k) const
        { return base_type::log_upper_bound(k); }
        
    public:
        using base_type::key_comp;
        using base_type::value_comp;
    };
    
}}                                                          // namespace elib
namespace elib
{
    using container::flat_map;
}                                                           // namespace elib
#endif /* ELIB_CONTAINER_FLAT_MAP_HPP */