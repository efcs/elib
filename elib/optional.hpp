#ifndef ELIB_OPTIONAL_HPP
#define ELIB_OPTIONAL_HPP



/**
 * Optional is currently an almost exact copy of the reference implementation
 * for proposal N793. The repository can be found here.
 * https://github.com/akrzemi1/Optional/ 
 */
# include <elib/aux.hpp>
# include <initializer_list>
# include <stdexcept>
# include <utility> /* for swap */

namespace elib 
{
    ////////////////////////////////////////////////////////////////////////////
    constexpr class nullopt_t  {}  nullopt  {};
    constexpr class in_place_t {}  in_place {};
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    ////////////////////////////////////////////////////////////////////////////
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
        constexpr struct dummy_ctor_arg_t {} dummy_ctor_arg {};
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        union storage
        {
            unsigned char dummy;
            T value;
            
            constexpr storage(dummy_ctor_arg_t) noexcept
              : dummy(0)
            {}
            
            template <class ...Args>
            constexpr storage(Args &&... args)
              : value(elib::forward<Args>(args)...)
            {}
            
            ~storage() {}
        };
        
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        struct optional_base
        {
            bool init;
            storage<T> store;
            
            optional_base() noexcept
              : init(false), store(dummy_ctor_arg)
            {}
            
            optional_base(T const & v)
              : init(true), store(v)
            {}
            
            optional_base(T && v) 
              : init(true), store(elib::move(v))
            {}
            
            template <class ...Args>
            optional_base(in_place_t, Args &&... args)
              : init(true), store(elib::forward<Args>(args)...)
            {}
            
            template <class U, class ...Args>
            optional_base(in_place_t, std::initializer_list<U> il, Args &&... args)
              : init(true), store(il, elib::forward<Args>(args)...)
            {}
            
            ~optional_base()
            {
                if (init) store.value.T::~T();
            }
        };
        
    }                                              // namespace optional_detail
    
    
    template <class T>
    class optional 
      : private optional_detail::optional_base<T>
    {
    public:
        using value_type = T;
        
        constexpr optional() noexcept;
        
        constexpr optional(nullopt_t) noexcept;
        
        optional(optional const &);
        
        optional(optional &&);
        
        constexpr optional(T const &);
        
        constexpr optional(T &&);
        
        template <class ...Args>
        constexpr explicit 
        optional(in_place_t, Args &&... args);
        
        template <class U, class ...Args>
        constexpr explicit 
        optional(in_place_t, std::initializer_list<U>, Args &&... args);
        
        ~optional();
        
        optional & operator=(nullopt_t) noexcept;
        optional & operator=(optional const &);
        optional & operator=(optional &&);
        
        template <class U>
        optional & operator=(U &&);
        
        template <class ...Args>
        void emplace(Args &&... args);
        
        template <class U, class ...Args>
        void emplace(std::initializer_list<U>, Args &&... args);
        
        void swap(optional &);
        
        constexpr T const* operator ->() const;
        
        T* operator ->();
        
        constexpr T const& operator *() const;
        
        T& operator *();
        
        constexpr explicit operator bool() const noexcept;
        
        constexpr T const& value() const;
        
        T& value();
        
        template <class U> constexpr T value_or(U&&) const&;
        
        template <class U> T value_or(U&&) &&;
        
    private:
        

    };

    template <class T>
    constexpr bool operator==(const optional<T>&, const optional<T>&);
    template <class T>
    constexpr bool operator!=(const optional<T>&, const optional<T>&);
    template <class T>
    constexpr bool operator<(const optional<T>&, const optional<T>&);
    template <class T>
    constexpr bool operator>(const optional<T>&, const optional<T>&);
    template <class T>
    constexpr bool operator<=(const optional<T>&, const optional<T>&);
    template <class T>
    constexpr bool operator>=(const optional<T>&, const optional<T>&);
        
    template <class T> constexpr bool operator==(const optional<T>&, nullopt_t) noexcept;
    template <class T> constexpr bool operator==(nullopt_t, const optional<T>&) noexcept;
    template <class T> constexpr bool operator!=(const optional<T>&, nullopt_t) noexcept;
    template <class T> constexpr bool operator!=(nullopt_t, const optional<T>&) noexcept;
    template <class T> constexpr bool operator<(const optional<T>&, nullopt_t) noexcept;
    template <class T> constexpr bool operator<(nullopt_t, const optional<T>&) noexcept;
    template <class T> constexpr bool operator<=(const optional<T>&, nullopt_t) noexcept;
    template <class T> constexpr bool operator<=(nullopt_t, const optional<T>&) noexcept;
    template <class T> constexpr bool operator>(const optional<T>&, nullopt_t) noexcept;
    template <class T> constexpr bool operator>(nullopt_t, const optional<T>&) noexcept;
    template <class T> constexpr bool operator>=(const optional<T>&, nullopt_t) noexcept;
    template <class T> constexpr bool operator>=(nullopt_t, const optional<T>&) noexcept;
    
    template <class T> constexpr bool operator==(const optional<T>&, const T&);
    template <class T> constexpr bool operator==(const T&, const optional<T>&);
    template <class T> constexpr bool operator!=(const optional<T>&, const T&);
    template <class T> constexpr bool operator!=(const T&, const optional<T>&);
    template <class T> constexpr bool operator<(const optional<T>&, const T&);
    template <class T> constexpr bool operator<(const T&, const optional<T>&);
    template <class T> constexpr bool operator<=(const optional<T>&, const T&);
    template <class T> constexpr bool operator<=(const T&, const optional<T>&);
    template <class T> constexpr bool operator>(const optional<T>&, const T&);
    template <class T> constexpr bool operator>(const T&, const optional<T>&);
    template <class T> constexpr bool operator>=(const optional<T>&, const T&);
    template <class T> constexpr bool operator>=(const T&, const optional<T>&);
    
    template <class T> void swap(optional<T>&, optional<T>&);
    //template <class T> constexpr optional<see below> make_optional(T&&);

    
}                                                             // namespace elib
#endif /* ELIB_OPTIONAL_HPP */