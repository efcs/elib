#ifndef ELIB_OPTIONAL_HPP
#define ELIB_OPTIONAL_HPP

/**
 * Optional is implementation for proposal N793. 
 */
# include <elib/config.hpp>
# include <elib/aux.hpp>
# include <initializer_list>
# include <stdexcept>
# include <string>
# include <utility> /* for swap */

namespace elib 
{
////////////////////////////////////////////////////////////////////////////////
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class bad_optional_access 
      : public std::logic_error 
    {
    public:
        explicit bad_optional_access(std::string const & what_arg)
          : std::logic_error(what_arg)
        {}
        
        explicit bad_optional_access(const char *what_arg)
          : std::logic_error(what_arg)
        {}
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
    ////////////////////////////////////////////////////////////////////////////
    constexpr struct nullopt_t
    {
        struct init {};
        constexpr nullopt_t(init) {}
    } nullopt( nullopt_t::init{} );
    
    ////////////////////////////////////////////////////////////////////////////
    constexpr struct in_place_t 
    {
        struct init {};
        constexpr in_place_t(init) {}
    } in_place( in_place_t::init{} );
    
        
    namespace optional_detail
    {
        ////////////////////////////////////////////////////////////////////////
        constexpr struct dummy_ctor_arg_t 
        {
            struct init {};
            constexpr dummy_ctor_arg_t(init) {}
        } dummy_ctor_arg( dummy_ctor_arg_t::init{} );
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        union default_storage
        {
            unsigned char dummy;
            T value;
            
            constexpr default_storage(dummy_ctor_arg_t) noexcept
              : dummy(0)
            {}
            
            template <class ...Args>
            constexpr default_storage(Args &&... args)
              : value(elib::forward<Args>(args)...)
            {}
            
            ~default_storage() {}
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        union constexpr_storage
        {
            unsigned char dummy;
            T value;
            
            constexpr constexpr_storage(dummy_ctor_arg_t) noexcept
              : dummy(0)
            {}
            
            template <class ...Args>
            constexpr constexpr_storage(Args &&... args)
              : value(elib::forward<Args>(args)...)
            {}
            
            ~constexpr_storage() = default;
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        struct default_optional_base
        {
            bool init;
            default_storage<T> store;
            
            constexpr default_optional_base() noexcept
              : init(false), store(dummy_ctor_arg)
            {}
            
            constexpr default_optional_base(T const & v)
              : init(true), store(v)
            {}
            
            constexpr default_optional_base(T && v) 
              : init(true), store(elib::move(v))
            {}
            
            template <class ...Args>
            constexpr default_optional_base(in_place_t, Args &&... args)
              : init(true), store(elib::forward<Args>(args)...)
            {}
            
            template <class U, class ...Args>
            default_optional_base(in_place_t
              , std::initializer_list<U> il
              , Args &&... args
            )
              : init(true), store(il, elib::forward<Args>(args)...)
            {}
            
            ~default_optional_base()
            {
                if (init) store.value.T::~T();
            }
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        struct constexpr_optional_base
        {
            bool init;
            constexpr_storage<T> store;
            
            constexpr constexpr_optional_base() noexcept
              : init(false), store(dummy_ctor_arg)
            {}
            
            constexpr constexpr_optional_base(T const & v)
              : init(true), store(v)
            {}
            
            constexpr constexpr_optional_base(T && v) 
              : init(true), store(elib::move(v))
            {}
            
            template <class ...Args>
            constexpr constexpr_optional_base(in_place_t, Args &&... args)
              : init(true), store(elib::forward<Args>(args)...)
            {}
            
            template <class U, class ...Args>
            constexpr_optional_base(in_place_t
              , std::initializer_list<U> il
              , Args &&... args
            )
              : init(true), store(il, elib::forward<Args>(args)...)
            {}
            
            ~constexpr_optional_base() = default;
        };
        
        
        template <class T>
        using optional_base_t = 
          elib::if_t<
            aux::is_trivially_destructible<T>
          , constexpr_optional_base<T>
          , default_optional_base<T>
          >;
    }                                              // namespace optional_detail
    
    
    template <class T>
    class optional 
      : private optional_detail::optional_base_t<T>
    {
    private:
        static_assert(
            not aux::is_same<T, in_place_t>::value
          , "Cannot create elib::optional with type \"in_place_t\""
        );
        
        static_assert(
            not aux::is_same<T, nullopt_t>::value
          , "Cannot create elib::optional with type \"nullopt_t\""
        );
        
        using base_type = optional_detail::optional_base_t<T>;
        
        //
    public:
        //
        
        using value_type = T;
        
        ////////////////////////////////////////////////////////////////////////
        constexpr optional() noexcept
          : base_type()
        {}
        
        constexpr optional(nullopt_t) noexcept
          : base_type()
        {}
        
        optional(optional const & other)
          : base_type()
        {
            if (other) m_create(other.m_ref());
        }
        
        optional(optional && other)
          : base_type()
        {
            if (other) m_create(elib::move(other.m_ref()));
        }
        
        constexpr optional(T const & v)
          : base_type(v)
        {}
        
        constexpr optional(T && v)
          : base_type(static_cast<T &&>(v))
        {}
        
        template <class ...Args>
        constexpr explicit 
        optional(in_place_t, Args &&... args)
          : base_type(in_place, elib::forward<Args>(args)...)
        {}
        
        template <class U, class ...Args>
        constexpr explicit 
        optional(in_place_t, std::initializer_list<U> il, Args &&... args)
          : base_type(in_place, il, elib::forward<Args>(args)...)
        {}
        
        ////////////////////////////////////////////////////////////////////////
        ~optional() = default;
        
        ////////////////////////////////////////////////////////////////////////
        optional & operator=(nullopt_t) noexcept
        {
            m_destroy();
            return *this;
        }
        
        optional & operator=(optional const & other)
        {
            if (m_init() && not other.m_init()) {
                m_destroy();
            }
            else if (not m_init() && other.m_init()) {
                m_create(other.m_ref());
            }
            else if (m_init() && other.m_init()) {
                m_ref() = other.m_ref();
            }
            return *this;
        }
        
        optional & operator=(optional && other)
        {
            if (m_init() && not other.m_init()) {
                m_destroy();
            }
            else if (not m_init() && other.m_init()) {
                m_create(elib::move(*other));
            }
            else if (m_init() && other.m_init()) {
                m_ref() = elib::move(*other);
            }
            return *this;
        }
        
        template <
            class U
          , ELIB_ENABLE_IF(aux::is_same<aux::decay_t<U>, T>::value)
          >
        optional & operator=(U && v)
        {
            if (m_init()) {
                m_ref() = elib::forward<U>(v);
            } 
            else {
                m_create(elib::forward<U>(v));
            }
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class ...Args>
        void emplace(Args &&... args)
        {
            m_destroy();
            m_create(elib::forward<Args>(args)...);
        }
        
        template <class U, class ...Args>
        void emplace(std::initializer_list<U> il, Args &&... args)
        {
            m_destroy();
            m_create(il, elib::forward<Args>(args)...);
        }
        
        ////////////////////////////////////////////////////////////////////////
        void swap(optional & other)
            noexcept( aux::is_nothrow_move_constructible<T>::value
                   && aux::is_nothrow_swappable<T>::value
              )
        {
            if (m_init() && not other.m_init()) {
                other.m_create(elib::move(m_ref()));
                m_destroy();
            }
            else if (not m_init() && other.m_init()) {
                m_create(elib::move(*other));
                other.m_destroy();
            } 
            else if (m_init() && other.m_init()) {
                using std::swap;
                swap(m_ref(), other.m_ref());
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr T const* operator ->() const
        {
#       ifndef NDEBUG
            return m_init() ? m_ptr() : throw bad_optional_access("bad optional access");
#       else
            return m_ptr();
#       endif
        }
        
        T* operator ->()
        {
            ELIB_ASSERT(m_init());
            return m_ptr();
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr T const & operator *() const
        {
#       ifndef NDEBUG
            return *(m_init() ? m_ptr() : throw bad_optional_access("bad optional access"));
#       else
            return m_ref();
#       endif
        }
        
        T & operator *()
        {
            ELIB_ASSERT(m_init());
            return m_ref();
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr explicit operator bool() const noexcept
        {
            return m_init();
        }
        
        constexpr bool good() const noexcept
        {
            return m_init();
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr T const & value() const
        {
            return *(bool(*this) ? m_ptr() : throw bad_optional_access("bad optional access"));
        }
        
        T & value()
        {
            return *(bool(*this) ? m_ptr() : throw bad_optional_access("bad optional access"));
        }
        
        ////////////////////////////////////////////////////////////////////////
# if ! defined(ELIB_CONFIG_NO_REF_QUALIFIERS)
        template <
            class U
          , ELIB_ENABLE_IF(aux::is_convertible<U &&, T>::value)
          > 
        constexpr T value_or(U && v) const &
        {
            return bool(*this) ? **this : static_cast<T>(elib::forward<U>(v));
        }
        
        template <
            class U
          , ELIB_ENABLE_IF(aux::is_convertible<U &&, T>::value)
          > 
        T value_or(U && v) &&
        {
            return bool(*this) ? elib::move(**this) 
                               : static_cast<T>(elib::forward<U>(v));
        }
# else
        template <
            class U
          , ELIB_ENABLE_IF(aux::is_convertible<U &&, T>::value)
          > 
        constexpr T value_or(U && v) const
        {
            return bool(*this) ? **this : static_cast<T>(elib::forward<U>(v));
        }
# endif
       
       //
    private:
       //
       
        ////////////////////////////////////////////////////////////////////////
        template <class ...Args>
        void m_create(Args &&... args)
            noexcept(noexcept(T(elib::forward<Args>(args)...)))
        {
            ELIB_ASSERT( not m_init() );
            ::new ((void*)m_ptr()) T(elib::forward<Args>(args)...);
            base_type::init = true;
        }
        
        template <class U, class ...Args>
        void m_create(std::initializer_list<U> il, Args &&...args)
            noexcept(noexcept(T(il, elib::forward<Args>(args)...)))
        {
            ELIB_ASSERT( not m_init() );
            ::new ((void*)m_ptr()) T(il, elib::forward<Args>(args)...);
            base_type::init = true;
        }
        
        ////////////////////////////////////////////////////////////////////////
        void m_destroy() noexcept
        {
            if (m_init()) m_ptr()->T::~T();
            base_type::init = false;
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr bool m_init() const noexcept
        {
            return base_type::init;
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr value_type const* m_ptr() const noexcept
        {
            return elib::addressof(base_type::store.value);
        }
        
        value_type* m_ptr() noexcept
        {
            return elib::addressof(base_type::store.value);
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr value_type const & m_ref() const noexcept
        {
            return base_type::store.value;
        }
        
        value_type & m_ref() noexcept
        {
            return base_type::store.value;
        }
    };                                                      // class optional
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    class optional<T &>
    {
    private:
        static_assert(
            not aux::is_same<T, in_place_t>::value
          , "Cannot create elib::optional with type \"in_place_t\""
        );
        
        static_assert(
            not aux::is_same<T, nullopt_t>::value
          , "Cannot create elib::optional with type \"nullopt_t\""
        );
        
        //
    public:
        //
        
        using value_type = T &;
        
        constexpr optional() noexcept
          : m_data(nullptr)
        {}
        
        constexpr optional(nullopt_t) noexcept
          : m_data(nullptr)
        {}
        
        constexpr optional(T & v) noexcept
          : m_data(elib::addressof(v))
        {}
        
        optional(T &&) = delete;
        
        constexpr optional(optional const & other) noexcept
          : m_data(other.m_data)
        {}
        
        explicit constexpr optional(in_place_t, T & v) noexcept
          : m_data(elib::addressof(v))
        {}
        
        explicit optional(in_place_t, T &&)  = delete;
        
        ////////////////////////////////////////////////////////////////////////
        ~optional() = default;
        
        ////////////////////////////////////////////////////////////////////////
        optional & operator=(nullopt_t) noexcept
        {
            m_data = nullptr;
            return *this;
        }
        
        template <
            class U
          , ELIB_ENABLE_IF(aux::is_same<aux::decay_t<U>, optional<T &>>::value)
          >
        optional & operator=(U && u) noexcept
        {
            m_data = u.m_data;
            return *this;
        }
        
        template <
            class U
          , ELIB_ENABLE_IF(not aux::is_same<aux::decay_t<U>, optional<T &>>::value)
          >
        optional & operator=(U && u) noexcept = delete;
       
        void emplace(T & v) noexcept
        {
            m_data = elib::addressof(v);
        }
        
        void emplace(T &&) = delete;
        
        ////////////////////////////////////////////////////////////////////////
        void swap(optional & rhs) noexcept
        {
            // m_data is a pointer, so we just want std::swap. 
            std::swap(m_data, rhs.m_data);
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr T* operator->() const 
        {
#       ifndef NDEBUG
            return bool(m_data) ? m_data : throw bad_optional_access("bad optional access");
#       else
            return m_data;
#       endif
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr T & operator*() const
        {
#       ifndef NDEBUG
            return *(bool(m_data) ? m_data : throw bad_optional_access("bad optional access"));
#       else
            return *m_data;
#       endif
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr T & value() const 
        {
            return *(bool(m_data) ?  m_data : throw bad_optional_access("bad optional access"));
        }
        
        ////////////////////////////////////////////////////////////////////////
        explicit constexpr operator bool() const noexcept
        {
            return bool(m_data);
        }
        
        constexpr bool good() const noexcept
        {
            return bool(m_data);
        }
        
        //
    private:
       //
        
      T *m_data;  
    };

    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    class optional<T &&>
    {
        static_assert(
            aux::never<T>::value
          , "Rvalue references are not allowed in elib::optional"
        );
    };
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    constexpr bool operator==(optional<T> const & lhs, optional<T> const & rhs) 
    {
        return bool(lhs) != bool(rhs) 
               ? false
               : (!lhs ? true : (*lhs == *rhs));
    }
    
    template <class T>
    constexpr bool operator!=(optional<T> const & lhs, optional<T> const & rhs)
    {
        return !(lhs == rhs);
    }
    
    template <class T>
    constexpr bool operator<(optional<T> const & lhs, optional<T> const & rhs)
    {
        return !rhs ? false 
                    : (!lhs ? true : *lhs < *rhs);
    }

    template <class T>
    constexpr bool operator>(optional<T> const & lhs, optional<T> const & rhs)
    {
        return (rhs < lhs);
    }
    
    template <class T>
    constexpr bool operator<=(optional<T> const & lhs, optional<T> const & rhs)
    {
        return !(rhs < lhs);
    }
    
    template <class T>
    constexpr bool operator>=(optional<T> const & lhs, optional<T> const & rhs)
    {
        return !(lhs < rhs);
    }
        
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator==(optional<T> const & lhs, nullopt_t) noexcept
    {
        return !lhs;
    }
    
    template <class T> 
    constexpr bool operator==(nullopt_t, optional<T> const & rhs) noexcept
    {
        return !rhs;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator!=(optional<T> const & lhs, nullopt_t) noexcept
    {
        return bool(lhs);
    }
    
    template <class T> 
    constexpr bool operator!=(nullopt_t, optional<T> const & rhs) noexcept
    {
        return bool(rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator<(optional<T> const &, nullopt_t) noexcept
    {
        return false;
    }
    
    template <class T> 
    constexpr bool operator<(nullopt_t, optional<T> const & rhs) noexcept
    {
        return bool(rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator<=(optional<T> const & lhs, nullopt_t) noexcept
    {
        return !lhs;
    }
    
    template <class T> 
    constexpr bool operator<=(nullopt_t, optional<T> const &) noexcept
    {
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    constexpr bool operator>(optional<T> const & lhs, nullopt_t) noexcept
    {
        return bool(lhs);
    }
    
    template <class T> 
    constexpr bool operator>(nullopt_t, optional<T> const &) noexcept
    {
        return false;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    constexpr bool operator>=(optional<T> const &, nullopt_t) noexcept
    {
        return true;
    }
    
    template <class T> 
    constexpr bool operator>=(nullopt_t, optional<T> const & rhs) noexcept
    {
        return !rhs;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator==(optional<T> const & lhs, T const & rhs)
    {
        return bool(lhs) ? *lhs == rhs : false;
    }
    
    template <class T>
    constexpr bool operator==(T const & lhs, optional<T> const & rhs)
    {
        return bool(rhs) ? lhs == *rhs : false;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    constexpr bool operator!=(optional<T> const & lhs, T const & rhs)
    {
        return bool(lhs) ? *lhs != rhs : true;
    }
    
    template <class T> 
    constexpr bool operator!=(T const & lhs, optional<T> const & rhs)
    {
        return bool(rhs) ? lhs != *rhs : true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    constexpr bool operator<(optional<T> const & lhs, T const & rhs)
    {
        return bool(lhs) ? *lhs < rhs : true;
    }
    
    template <class T> 
    constexpr bool operator<(T const & lhs, optional<T> const & rhs)
    {
        return bool(rhs) ? lhs < *rhs : false;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator>(optional<T> const & lhs, T const & rhs)
    {
        return bool(lhs) ? rhs < *lhs : false;
    }
    
    template <class T> 
    constexpr bool operator>(T const & lhs, optional<T> const & rhs)
    {
        return bool(rhs) ? *rhs < lhs : true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator<=(optional<T> const & lhs, T const & rhs)
    {
        return !(lhs > rhs);
    }
    
    template <class T> 
    constexpr bool operator<=(T const & lhs, optional<T> const & rhs)
    {
        return !(lhs > rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator>=(optional<T> const & lhs, T const & rhs)
    {
        return !(lhs < rhs);
    }
    
    template <class T>
    constexpr bool operator>=(T const & lhs, optional<T> const & rhs)
    {
        return !(lhs < rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    void swap(optional<T> & lhs, optional<T> & rhs)
        noexcept(noexcept( lhs.swap(rhs) ))
    {
        lhs.swap(rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr optional<aux::decay_t<T>> make_optional(T && v)
    {
        return optional<aux::decay_t<T>>(elib::forward<T>(v));
    }
}                                                             // namespace elib
namespace std
{
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    struct hash< ::elib::optional<T>>
    {
        using result_type = typename hash<T>::result_type;
        using argument_type = ::elib::optional<T>;
        
        constexpr result_type operator()(::elib::optional<T> const & v) const
        {
            return bool(v) ? std::hash<T>{}(*v) : result_type{};
        }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    struct hash< ::elib::optional<T &>>
    {
        using result_type = typename std::hash<T>::result_type;
        using argument_type = ::elib::optional<T &>;
        
        constexpr result_type operator()(::elib::optional<T &> const & v) const
        {
            return bool(v) ? std::hash<T>{}(*v) : result_type{};
        }
    };
}
#endif /* ELIB_OPTIONAL_HPP */