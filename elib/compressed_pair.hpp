#ifndef ELIB_COMPRESSED_PAIR_HPP
#define ELIB_COMPRESSED_PAIR_HPP

# include <elib/aux.hpp>

namespace elib 
{
    namespace compressed_pair_detail
    {
        enum class compress
        {
            none, first, second, both
        };
        
        template <bool IsSame, bool FirstEmpty, bool SecondEmpty>
        struct choose_compress_impl;
        
        template <bool IsSame>
        struct choose_compress_impl<IsSame, false, false>
          : elib::integral_constant<compress, compress::none>
        {};
        
        template <bool IsSame>
        struct choose_compress_impl<IsSame, true, false>
          : elib::integral_constant<compress, compress::first>
        {};
        
        template <bool IsSame>
        struct choose_compress_impl<IsSame, false, true>
          : elib::integral_constant<compress, compress::second>
        {};
        
        template <>
        struct choose_compress_impl<false, true, true>
          : elib::integral_constant<compress, compress::both>
        {};
        
        template <>
        struct choose_compress_impl<true, true, true>
          : elib::integral_constant<compress, compress::first>
        {};
        
        template <class First, class Second>
        using choose_compress = choose_compress_impl<
            aux::is_same<aux::remove_cv_t<First>, aux::remove_cv_t<Second>>::value
          , aux::is_empty<First>::value
          , aux::is_empty<Second>::value
          >;
        
        template <
            class First, class Second
          , compress = choose_compress<First, Second>::value
          >
        class compressed_pair_impl;
        
        
        template <class First, class Second>
        class compressed_pair_impl<First, Second, compress::none>
        {
        public:
            using first_type = First;
            using second_type = Second;
            
            using first_reference = aux::remove_reference_t<First> &;
            using second_reference = aux::remove_reference_t<Second> &;
            
            using first_const_reference = aux::remove_reference_t<First> const &;
            using second_const_reference = aux::remove_reference_t<Second> const &;
            
            compressed_pair_impl() {}
            
            explicit compressed_pair_impl(First f)
              : m_first(elib::forward<First>(f))
            {}
            
            explicit compressed_pair_impl(Second s)
              : m_second(elib::forward<Second>(s))
            {}
            
            compressed_pair_impl(First f, Second s)
              : m_first(elib::forward<First>(f))
              , m_second(elib::forward<Second>(s))
            {}
            
            first_reference first() noexcept { return m_first; }
            first_const_reference first() const noexcept { return m_first; }
            
            second_reference second() noexcept { return m_second; }
            second_const_reference second() const noexcept { return m_second; }
            
            void swap(compressed_pair_impl & other)
                noexcept(aux::is_nothrow_swappable<First>::value 
                        && aux::is_nothrow_swappable<Second>::value)
            {
                using std::swap;
                swap(m_first, other.m_first);
                swap(m_second, other.m_second);
            }
            
            
        private:
            First m_first;
            Second m_second;
        };
        
        
        template <class First, class Second>
        class compressed_pair_impl<First, Second, compress::first>
          : private First
        {
        public:
            using first_type = First;
            using second_type = Second;
            
            using first_reference = First &;
            using second_reference = aux::remove_reference_t<Second> &;
            
            using first_const_reference = First const &;
            using second_const_reference = aux::remove_reference_t<Second> const &;
            
            compressed_pair_impl() {}
            
            explicit compressed_pair_impl(First f)
              : First(elib::forward<First>(f))
            {}
            
            explicit compressed_pair_impl(Second s)
              : m_second(elib::forward<Second>(s))
            {}
            
            compressed_pair_impl(First f, Second s)
              : First(elib::forward<First>(f))
              , m_second(elib::forward<Second>(s))
            {}
            
            first_reference first() noexcept { return *this; }
            first_const_reference first() const noexcept { return *this; }
            
            second_reference second() noexcept { return m_second; }
            second_const_reference second() const noexcept { return m_second; }
            
            void swap(compressed_pair_impl & other)
                noexcept(aux::is_nothrow_swappable<First>::value 
                        && aux::is_nothrow_swappable<Second>::value)
            {
                using std::swap;
                swap(m_second, other.m_second);
            }
            
        private:
            Second m_second;
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class First, class Second>
        class compressed_pair_impl<First, Second, compress::second>
          : private Second
        {
        public:
            using first_type = First;
            using second_type = Second;
            
            using first_reference = aux::remove_reference_t<First> &;
            using second_reference = Second &;
            
            using first_const_reference = aux::remove_reference_t<First> const &;
            using second_const_reference = Second const &;
            
            compressed_pair_impl() {}
            
            explicit compressed_pair_impl(First f)
              : m_first(elib::forward<First>(f))
            {}
            
            explicit compressed_pair_impl(Second s)
              : Second(elib::forward<Second>(s))
            {}
            
            compressed_pair_impl(First f, Second s)
              : m_first(elib::forward<First>(f))
              , Second(elib::forward<Second>(s))
            {}
            
            first_reference first() noexcept { return m_first; }
            first_const_reference first() const noexcept { return m_first; }
            
            second_reference second() noexcept { return *this; }
            second_const_reference second() const noexcept { return *this; }
            
            void swap(compressed_pair_impl & other)
                noexcept(aux::is_nothrow_swappable<First>::value 
                        && aux::is_nothrow_swappable<Second>::value)
            {
                using std::swap;
                swap(m_first, other.m_first);
            }
            
            
        private:
            First m_first;
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class First, class Second>
        class compressed_pair_impl<First, Second, compress::both>
          : private First, Second
        {
        public:
            using first_type = First;
            using second_type = Second;
            
            using first_reference = First &;
            using second_reference = Second &;
            
            using first_const_reference = First const &;
            using second_const_reference = Second const &;
            
            compressed_pair_impl() {}
            
            explicit compressed_pair_impl(First f)
              : First(elib::forward<First>(f))
            {}
            
            explicit compressed_pair_impl(Second s)
              : Second(elib::forward<Second>(s))
            {}
            
            compressed_pair_impl(First f, Second s)
              : First(elib::forward<First>(f))
              , Second(elib::forward<Second>(s))
            {}
            
            first_reference first() noexcept { return *this; }
            first_const_reference first() const noexcept { return *this; }
            
            second_reference second() noexcept { return *this; }
            second_const_reference second() const noexcept { return *this; }
            
            void swap(compressed_pair_impl &)
                noexcept(aux::is_nothrow_swappable<First>::value 
                        && aux::is_nothrow_swappable<Second>::value)
            {
            }
            
        };
    }                                       // namespace compressed_pair_detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class Second>
    class compressed_pair
      : private compressed_pair_detail::compressed_pair_impl<First, Second>
    {
        using base = compressed_pair_detail::compressed_pair_impl<First, Second>;

    public:
        using first_type = typename base::first_type;
        using second_type = typename base::second_type;
        using first_reference = typename base::first_reference;
        using second_reference = typename base::second_reference;
        using first_const_reference = typename base::first_const_reference;
        using second_const_reference = typename base::second_const_reference;
        
        compressed_pair() {}
        explicit compressed_pair(first_type f)
          : base(elib::forward<first_type>(f))
        {}
        
        explicit compressed_pair(second_type f)
          : base(elib::forward<second_type>(f))
        {}
        
        compressed_pair(first_type f, second_type s)
          : base(elib::forward<first_type>(f), elib::forward<second_type>(s))
        {}
        
        first_reference first() noexcept { return base::first(); }
        
        constexpr first_const_reference 
        first() const noexcept { return base::first(); }
        
        second_reference second() noexcept { return base::second(); }
        
        constexpr second_const_reference 
        second() const noexcept { return base::second(); }
        
        void swap(compressed_pair & other)
            noexcept( aux::is_nothrow_swappable<First>::value
                     && aux::is_nothrow_swappable<Second>::value)
        {
            base::swap(other);
        }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class Second>
    inline void swap(
        compressed_pair<First, Second> & lhs
      , compressed_pair<First, Second> & rhs 
      ) noexcept( aux::is_nothrow_swappable<First>::value 
                && aux::is_nothrow_swappable<Second>::value)
    {
        lhs.swap(rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class Second>
    constexpr bool operator==(
        compressed_pair<First, Second> const & lhs
      , compressed_pair<First, Second> const & rhs
      )
    {
        return (lhs.first() == rhs.first() && lhs.second() == rhs.second());
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class Second>
    constexpr bool operator!=(
        compressed_pair<First, Second> const & lhs
      , compressed_pair<First, Second> const & rhs
      )
    {
        return (lhs.first() != rhs.first() || lhs.second() != rhs.second());
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class Second>
    constexpr bool operator<(
        compressed_pair<First, Second> const & lhs
      , compressed_pair<First, Second> const & rhs
      )
    {
        return lhs.first() < rhs.first() ? true :
            (rhs.first() < lhs.first() ? false : lhs.second() < rhs.second());
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class Second>
    constexpr bool operator<=(
        compressed_pair<First, Second> const & lhs
      , compressed_pair<First, Second> const & rhs
      )
    {
        return !(rhs < lhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class Second>
    constexpr bool operator>(
        compressed_pair<First, Second> const & lhs
      , compressed_pair<First, Second> const & rhs
      )
    {
        return rhs < lhs;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class Second>
    constexpr bool operator>=(
        compressed_pair<First, Second> const & lhs
      , compressed_pair<First, Second> const & rhs
      )
    {
        return !(lhs < rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class First, class Second>
    inline compressed_pair<aux::decay_t<First>, aux::decay_t<Second>>
    make_compressed_pair(First && first, Second && second)
    {
        return compressed_pair<aux::decay_t<First>, aux::decay_t<Second>>(
            elib::forward<First>(first), elib::forward<Second>(second)
          );
    }
    
}                                                           // namespace elib
#endif /* ELIB_COMPRESSED_PAIR_HPP */