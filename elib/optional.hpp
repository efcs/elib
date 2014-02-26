#ifndef ELIB_OPTIONAL_HPP
#define ELIB_OPTIONAL_HPP

# include <elib/aux.hpp>
# include <stdexcept>
# include <initializer_list>
# include <utility> /* for swap */

namespace elib 
{
    ////////////////////////////////////////////////////////////////////////////
    //
    constexpr class nullopt_t  {}  nullopt  {};
    constexpr class in_place_t {}  in_place {};
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    ////////////////////////////////////////////////////////////////////////////
    //
    class bad_optional_access : public std::logic_error
    {
    public:
        bad_optional_access() : std::logic_error("bad optional access") {}
        
        ELIB_DEFAULT_COPY_MOVE(bad_optional_access);
        
        virtual ~bad_optional_access() = default;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

    namespace optional_detail
    {
        constexpr struct dummy_ctor_arg_t
        {} dummy_ctor_arg {};
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        union storage
        {
            char dummy;
            T value;
            
            constexpr storage(dummy_ctor_arg_t) noexcept : dummy(0) {}
            
            template <class ...Args>
            constexpr storage(Args&&... args) : value(elib::forward<Args>(args)...) 
            {}
            
            //TODO: they don't do this in the draft
            ~storage() = default;
        };
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T>
        struct optional_impl
        {
            bool init;
            storage<T> store;
            
            constexpr optional_impl() noexcept
              : init(false), store(dummy_ctor_arg) 
            {}
        
            constexpr explicit optional_impl(T const & t)
              : init(true), store(t)
            {}
            
            constexpr explicit optional_impl(T && t)
              : init(true), store(elib::move(t))
            {}
            
            template <class ...Args>
            constexpr explicit optional_impl(in_place_t, Args &&... args)
              : init(true), store(elib::forward<Args>(args)...)
            {}
            
            template <class U, class ...Args>
            constexpr explicit 
            optional_impl(in_place_t, std::initializer_list<U> il, Args &&... args)
              : init(true), store(il, elib::forward<Args>(args)...)
            {}
            
            ~optional_impl()
            {
                if (init) store.value.T::~T();
            }
        };
    }                                              // namespace optional_detail
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T>
    class optional
    {
    public:
        using value_type = T;
        
        constexpr optional() noexcept : m_impl() {}
        constexpr optional(nullopt_t) noexcept : m_impl() {}
        
        optional(optional const & rhs) : m_impl() 
        {
            m_impl.init = rhs.is_init();
            if (is_init()) ::new (static_cast<void*>(raw_ptr())) T(*rhs);
        }
        
        optional(optional && rhs) noexcept 
          : m_impl()
        {
            m_impl.init = rhs.is_init();
            if (is_init()) ::new (static_cast<void*>(raw_ptr())) T(elib::move(*rhs));
        }
        
        constexpr optional(T const & t)
          : m_impl(t)
        {}
        
        constexpr optional(T && t)
          : m_impl(elib::move(t))
        {}
        
        template <class ...Args>
        constexpr explicit optional(in_place_t, Args &&... args)
          : m_impl(in_place, elib::forward<Args>(args)...)
        {}
        
        template <class U, class ...Args>
        constexpr explicit optional(
            in_place_t, std::initializer_list<U> il, Args &&... args
        ) : m_impl(in_place, il, elib::forward<Args>(args)...)
        {}
        
        ~optional() = default;
        
        optional & operator=(nullopt_t) noexcept
        {
            clear();
            return *this;
        }
        
        optional & operator=(optional const & rhs)
        {
            if (is_init() && rhs.is_init()) raw_val() = rhs.raw_val();
            else if (is_init()) clear();
            else if (rhs.is_init()) init(rhs.raw_val());
            return *this;
        }
        
        optional & operator=(optional && rhs) noexcept
        {
            if (is_init() && rhs.is_init()) raw_val() = elib::move(rhs).raw_val();
            else if (is_init()) clear();
            else if (rhs.is_init()) init(elib::move(rhs).raw_val());
            return *this;
        }
        
        // TODO this definition makes no sense
        //template <class U> 
        //optional & operator=(U &&);
        
        template <class ...Args>
        void emplace(Args &&... args)
        {
            clear();
            init(elib::forward<Args>(args)...);
        }
        
        template <class U, class ...Args>
        void emplace(std::initializer_list<U>, Args &&... args)
        {
            clear();
            init(elib::forward<Args>(args)...);
        }
        
        void swap(optional & rhs) noexcept
        {
            if (is_init() && rhs.is_init()) 
            {
                using std::swap;
                swap(raw_val(), rhs.raw_val());
            }
            else if (is_init()) rhs.init(elib::move(*this).raw_val());
            else if (rhs.is_init()) init(elib::move(rhs).raw_val());
            
        }
        
        constexpr explicit operator bool() const noexcept
        { 
            return is_init(); 
        }
        
        constexpr T const * operator->() const
        {
            return is_init() ? raw_ptr() : throw bad_optional_access();
        }
        
        T * operator->()
        {
            return is_init() ? raw_ptr() : throw bad_optional_access();
        }
        
        // TODO is this god-awful workaround even close to correct? 
        constexpr T const & operator*() const
        {
            return static_cast<T const &>(
                *(is_init() ? raw_ptr() : throw bad_optional_access())
            );
        }
        
        T & operator*()
        {
            return static_cast<T &>(
                *(is_init() ? raw_ptr() : throw bad_optional_access())
            );
        }
        
        constexpr T const & value() const &
        {
            return static_cast<T const &>(
                *(is_init() ? raw_ptr() : throw bad_optional_access())
            );
        }
        
        T & value() &
        {
            return static_cast<T &>(
                *(is_init() ? raw_ptr() : throw bad_optional_access())
            );
        }
        
        T && value() &&
        {
            return static_cast<T &&>(
                *(is_init() ? raw_ptr() : throw bad_optional_access())
            );
        }
        
        template <class U> 
        constexpr T value_or(U && u) const &
        {
            return *this ?  **this : static_cast<T>(elib::forward<U>(u));
        }
        
        template <class U>
        T value_or(U && u) &&
        {
            return *this ? elib::move(*this).raw_val() 
                         : static_cast<T>(elib::forward<U>(u));
        }

    private:
        
        constexpr bool is_init() const noexcept 
        { 
            return m_impl.init; 
        }
        
        constexpr T const * raw_ptr() const
        {
            return elib::addressof(m_impl.store.value);
        }
        
        T * raw_ptr() 
        {
            return elib::addressof(m_impl.store.value);
        }
        
        constexpr T const & raw_val() const &
        {
            return m_impl.store.value;
        }
        
        T & raw_val() &
        {
            return m_impl.store.value;
        }
        
        T && raw_val() &&
        {
            return static_cast<T &&>(m_impl.store.value);
        }
        
        template <class ...Args>
        void init(Args &&... args) noexcept(noexcept(T(elib::forward<Args>(args)...)))
        {
            ELIB_ASSERT(!is_init());
            ::new (static_cast<void*>(raw_ptr())) T(elib::forward<Args>(args)...);
            m_impl.init = true;
        }
        
        template <class U, class ...Args>
        void init(std::initializer_list<U> il, Args &&... args)
            noexcept(noexcept(T(il, elib::forward<Args>(args)...)))
        {
            ELIB_ASSERT(!is_init());
            ::new (static_cast<void*>(raw_ptr())) T(il, elib::forward<Args>(args)...);
            m_impl.init = true;
        }
        
        void clear() noexcept
        {
            if (is_init()) m_impl.store.value.T::~T();
            m_impl.init = false;
        }
        
    private:
        optional_detail::optional_impl<T> m_impl;
    };                                                      // class optional
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T>
    class optional<T &>
    {
    public:
        
        constexpr optional() noexcept : m_ref(nullptr) {}
        constexpr optional(nullopt_t) noexcept : m_ref(nullptr) {}
        
        constexpr optional(T & v) noexcept : m_ref(elib::addressof(v)) {}
        optional(T &&) = delete;
        
        optional(optional const & rhs) noexcept : m_ref(rhs.m_ref) {}
        
        constexpr explicit optional(in_place_t, T & v) noexcept 
          : m_ref(elib::addressof(v))
        {}
        
        explicit optional(in_place_t, T &&) = delete;
        
        ~optional() = default;
        
        optional & operator=(nullopt_t) noexcept
        {
            m_ref = nullptr;
            return *this;
        }
        
        // TODO fix for decay
        optional & operator=(optional const & rhs) noexcept
        {
            m_ref = rhs.m_ref;
            return *this;
        }
        
        void emplace(T & v) noexcept
        {
            m_ref = elib::addressof(v);
        }
        
        void emplace(T &&) = delete;
        
        void swap(optional & rhs) noexcept
        {
            std::swap(m_ref, rhs.m_ref);
        }
        
        constexpr T* operator->() const 
        {
            return m_ref ? m_ref : throw bad_optional_access();
        }
        
        constexpr T & operator*() const
        {
            return m_ref ? *m_ref : throw bad_optional_access();
        }
        
        constexpr T & value() const
        {
            return **this;
        }
        
        constexpr explicit operator bool() const noexcept
        {
            return m_ref;
        }
        
        template <class U>
        constexpr aux::decay_t<T> value_or(U && u) const
        {
            return *this ? **this : static_cast<aux::decay_t<T>>(elib::forward<U>(u));
        }
        
    private:
        T * m_ref;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T>
    class optional<T &&>
    {
        static_assert(
            aux::never<T>::value
          , "Cannot create an instance of optional<T> with [T = T&&]"
        );
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T> 
    constexpr bool operator==(optional<T> const & lhs, nullopt_t) noexcept
    {
        return (!lhs);
    }
    
    template <class T> 
    constexpr bool operator==(nullopt_t, optional<T> const & rhs) noexcept
    {
        return (!rhs);
    }
    
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
    
    template <class T> 
    constexpr bool operator<=(optional<T> const & lhs, nullopt_t) noexcept
    {
        return (!lhs);
    }
    
    template <class T> 
    constexpr bool operator<=(nullopt_t, optional<T> const &) noexcept
    {
        return true;
    }
    
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
    
    template <class T>
    constexpr bool operator>=(optional<T> const &, nullopt_t) noexcept
    {
        return true;
    }
    
    template <class T>
    constexpr bool operator>=(nullopt_t, optional<T> const & rhs) noexcept
    {
        return (!rhs);
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T> 
    constexpr bool operator==(optional<T> const & lhs, T const & rhs)
    {
        return lhs ? *lhs == rhs : false;
    }
    
    template <class T> 
    constexpr bool operator==(T const & lhs, optional<T> const & rhs)
    {
        return rhs ?  lhs == *rhs : false;
    }
    
    template <class T> 
    constexpr bool operator!=(optional<T> const & lhs, T const & rhs)
    {
        return lhs ? *lhs != rhs : true;
    }
    
    template <class T> 
    constexpr bool operator!=(T const & lhs, optional<T> const & rhs)
    {
        return rhs ? lhs != rhs : true;
    }
    
    template <class T> 
    constexpr bool operator<(optional<T> const & lhs, T const & rhs)
    {
        return lhs ? *lhs < rhs : true;
    }
    
    template <class T>
    constexpr bool operator<(T const & lhs, optional<T> const & rhs)
    {
        return rhs ? lhs < *rhs : false;
    }
    
    template <class T>
    constexpr bool operator<=(optional<T> const & lhs, T const & rhs)
    {
        return lhs ? *lhs <= rhs : true;
    }
    
    template <class T> 
    constexpr bool operator<=(T const & lhs, optional<T> const & rhs)
    {
        return rhs ? lhs <= *rhs : false;
    }
    
    template <class T>
    constexpr bool operator>(optional<T> const & lhs, T const & rhs)
    {
        return lhs ? *lhs > rhs : false;
    }
    
    template <class T>
    constexpr bool operator>(T const & lhs, optional<T> const & rhs)
    {
        return rhs ?  lhs > *rhs : true;
    }
    
    template <class T>
    constexpr bool operator>=(optional<T> const & lhs, T const & rhs)
    {
        return lhs ? *lhs >= rhs : false;
    }
    
    template <class T> 
    constexpr bool operator>=(T const & lhs, optional<T> const & rhs)
    {
        return rhs ? lhs >= *rhs : true;
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T> 
    void swap(optional<T> & lhs, optional<T> & rhs)
    {
        lhs.swap(rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T> 
    constexpr optional<aux::decay_t<T>> 
    make_optional(T && t)
    {
        return optional<aux::decay_t<T>>(elib::forward<T>(t));
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T> struct hash;
    template <class T> struct hash<optional<T>>;
    
}                                                             // namespace elib
#endif /* ELIB_OPTIONAL_HPP */