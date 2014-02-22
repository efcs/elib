#ifndef ELIB_OPTIONAL_HPP
#define ELIB_OPTIONAL_HPP

# include <elib/aux.hpp>

# include <initalizer_list>

namespace elib 
{
    constexpr class nullopt_t {}  nullopt  {};
    constexpr class in_place_t {} in_place {};
    
    class bad_optional_access;
    
    namespace optional_detail
    {
        constexpr struct dummy_ctor_arg_t
        {} dummy_ctor_arg {};
        
        
        template <class T>
        union storage
        {
            char dummy;
            T value;
            
            constexpr storage(dummy_ctor_arg_t) noexcept : dummy(0) {}
            
            template <class ...Args>
            constexpr storage(Args&&... args) : m_value(elib::forward<Args>(args)...) 
            {}
            
            //TODO: they don't do this in the draft
            ~storage() = default;
        };
        
        template <class T>
        struct optional_impl
        {
            bool init;
            storage<T> storage;
            
            constexpr optional_impl() noexcept
              : init(false), storage(dummy_ctor_arg) 
            {}
        
            constexpr explicit optional_impl(T const & t)
              : init(true), storage(t)
            {}
            
            constexpr explicit optional_impl(T && t)
              : init(true), storage(elib::move(t))
            {}
            
            template <class ...Args>
            constexpr explicit optional_impl(in_place_t, Args &&... args)
              : init(true), storage(elib::forward<Args>(args))
            {}
            
            template <class U, class ...Args>
            constexpr explicit 
            optional_impl(in_place_t, std::initalizer_list<U> il, Args &&... args)
              : init(true), storage(il, elib::forward<Args>(args)...)
            {}
            
            ~optional_impl()
            {
                if (init) storage.value.T::~T();
            }
        };
        
    }                                              // namespace optional_detail
    
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
            if (is_init()) new (raw_ptr()) T(*rhs);
        }
        
        optional(optional && rhs) noexcept 
          : m_impl()
        {
            m_impl.init = rhs.is_init();
            if (is_init()) new (raw_ptr()) T(elib::move(*rhs));
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
            in_place_t, std::initalizer_list<U> il, Args &&... args
        ) : m_impl(in_place, il, elib::forward<Args>(args)...)
        {}
        
        ~optional() = default;
        
        optional & operator=(nullopt_t) noexcept
        {
            clear();
            return *this;
        }
        
        optional & operator=(optional const &);
        optional & operator=(optional &&) noexcept;
        template <class U> 
        optional & operator=(U &&);
        
        template <class ...Args>
        void emplace(Args &&...);
        
        template <class U, class ...Args>
        void emplace(std::initalizer_list<U>, Args &&...);
        
        void swap(optional &) noexcept;
        
        constexpr T const * operator->() const;
        T * operator->();
        
        constexpr T const & operator*() const;
        T & operator*();
        
        constexpr explicit operator bool() const noexcept;
        
        constexpr T const & value() const;
        T & value();
        
        template <class U> 
        constexpr T value_or(U &&) const &;
        
        template <class U>
        T value_or(U &&) &&;

    private:
        constexpr bool is_init() const noexcept { return m_impl.init; }
        
        constexpr void const * raw_ptr() const;
        void* raw_ptr();
        
        constexpr T const & raw_val() const;
        T & raw_val();
        
        template <class ...Args>
        void init(Args &&... args) noexcept(noexcept(T(elib::forward<Args>(args)...)));
        
        template <class U, class ...Args>
        void init(std:initalizer_list<U> il, Args &&... args)
            noexcept(noexcept(T(il, elib::forward<Args>(args)...)));
        
        void clear() noexcept;
        
    private:
        optional_detail::optional_impl<T> m_impl;
    };                                                      // class optional
    
    template <class T> 
    constexpr bool operator==(optional<T> const&, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator==(nullopt_t, optional<T> const &) noexcept;
    
    template <class T> 
    constexpr bool operator!=(optional<T> const &, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator!=(nullopt_t, optional<T> const &) noexcept;
    
    template <class T>
    constexpr bool operator<(optional<T> const &, nullopt_t) noexcept;
    
    template <class T>
    constexpr bool operator<(nullopt_t, optional<T> const &) noexcept;
    
    template <class T> 
    constexpr bool operator<=(optional<T> const &, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator<=(nullopt_t, optional<T> const &) noexcept;
    
    template <class T> 
    constexpr bool operator>(optional<T> const &, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator>(nullopt_t, optional<T> const &) noexcept;
    
    template <class T>
    constexpr bool operator>=(optional<T> const &, nullopt_t) noexcept;
    
    template <class T>
    constexpr bool operator>=(nullopt_t, optional<T> const &) noexcept;

    template <class T> 
    constexpr bool operator==(optional<T> const &, T const &);
    
    template <class T> 
    constexpr bool operator==(T const &, optional<T> const &);
    
    template <class T> 
    constexpr bool operator!=(optional<T> const &, T const &);
    
    template <class T> 
    constexpr bool operator!=(T const &, optional<T> const &);
    
    template <class T> 
    constexpr bool operator<(optional<T> const &, T const &);
    
    template <class T>
    constexpr bool operator<(T const &, optional<T> const &);
    
    template <class T>
    constexpr bool operator<=(optional<T> const &, T const &);
    
    template <class T> 
    constexpr bool operator<=(T const &, optional<T> const &);
    
    template <class T>
    constexpr bool operator>(optional<T> const &, T const &);
    
    template <class T>
    constexpr bool operator>(T const &, optional<T> const &);
    
    template <class T>
    constexpr bool operator>=(optional<T> const &, T const &);
    
    template <class T> 
    constexpr bool operator>=(T const &, optional<T> const &);

    //template <class T> 
    //void swap(optional<T>&, optional<T>&) noexcept(see below);
    
    //template <class T> constexpr 
    //optional<see below> make_optional(T&&);

    template <class T> struct hash;
    template <class T> struct hash<optional<T>>;
    
}                                                             // namespace elib
#endif /* ELIB_OPTIONAL_HPP */