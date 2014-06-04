/*! \file optional.hpp
 * 
 * A type-erased container. It implements the std::any proposal.
 */
namespace elib 
{

    /// The exception thrown by \ref optional for invalid access.
    class bad_optional_access 
      : public std::logic_error 
    {
    public:
        explicit bad_optional_access(std::string const & what_arg);
        
        explicit bad_optional_access(const char *what_arg);
    };
    
    
    /// nullopt tag used by \ref optional.
    struct nullopt_t
    {
    private:
        nullopt_t();
    };
    
    /// Instance of \ref nullopt_t.
    constexpr nullopt_t nullopt;
    
    /// in_place construction tag used by \ref optional.
    struct in_place_t 
    {
    private:
        in_place_t();
    };
    
    /// Instance of \ref in_place_t.
    constexpr in_place_t in_place;
    
    /// An optional object.
    template <class T>
    class optional
    {
    public:
        
        using value_type = T;
        
        constexpr optional() noexcept;
        
        constexpr optional(nullopt_t) noexcept;
        optional(optional const & other);
        optional(optional && other);
        
        constexpr optional(T const & v);
        
        constexpr optional(T && v);
        
        template <class ...Args>
        constexpr explicit 
        optional(in_place_t, Args &&... args);
        
        template <class U, class ...Args>
        constexpr explicit 
        optional(in_place_t, std::initializer_list<U> il, Args &&... args);
        
        ~optional() = default;
        
        optional & operator=(nullopt_t) noexcept;
        
        optional & operator=(optional const & other);
        
        optional & operator=(optional && other);
        
        /// \remark If this is empty. T is constructed from v. Otherwise v is
        /// assigned to this.
        ///
        ///
        /// \remark Only participates in overload resolution if
        /// aux::is_same<aux::decay_t<U>, T>::value.
        template <class U>
        optional & operator=(U && v);
        
        template <class ...Args>
        void emplace(Args &&... args);
        
        template <class U, class ...Args>
        void emplace(std::initializer_list<U> il, Args &&... args);

        void swap(optional & other);
        
        constexpr T const* operator->() const;
        
        ELIB_CXX1Y_CONSTEXPR T* operator->();

        constexpr T const & operator*() const &;
        
        ELIB_CXX1Y_CONSTEXPR T & operator*() &;
        
        ELIB_CXX1Y_CONSTEXPR T && operator*() &&;
    
 
        constexpr explicit operator bool() const noexcept;
        
        constexpr bool good() const noexcept;

        constexpr T const & value() const &;
        
        T & value() &;
        
        T && value() &&;

        template <
            class U
          , ELIB_ENABLE_IF(aux::is_convertible<U &&, T>::value)
          > 
        constexpr T value_or(U && v) const &;
        
        template <
            class U
          , ELIB_ENABLE_IF(aux::is_convertible<U &&, T>::value)
          > 
        T value_or(U && v) &&;

       

    };                                                      // class optional
    

    template <class T>
    class optional<T &>
    {
    public:
        
        using value_type = T &;
        
        constexpr optional() noexcept;
        
        constexpr optional(nullopt_t) noexcept;
        
        constexpr optional(T & v) noexcept;
        
        optional(T &&) = delete;
        
        constexpr optional(optional const & other) noexcept;
        
        explicit constexpr optional(in_place_t, T & v) noexcept;
        
        explicit optional(in_place_t, T &&)  = delete;
        
        
        ~optional() = default;
        
        ////////////////////////////////////////////////////////////////////////
        optional & operator=(nullopt_t) noexcept;
        
        template <
            class U
          , ELIB_ENABLE_IF(aux::is_same<aux::decay_t<U>, optional<T &>>::value)
          >
        optional & operator=(U && u) noexcept;
        
        template <class U>
        optional & operator=(U && u) noexcept = delete;
       
        void emplace(T & v) noexcept;
        
        void emplace(T &&) = delete;
        
        ////////////////////////////////////////////////////////////////////////
        void swap(optional & rhs) noexcept;
        
        ////////////////////////////////////////////////////////////////////////
        constexpr T* operator->() const ;
        
        ////////////////////////////////////////////////////////////////////////
        constexpr T & operator*() const;
        
        ////////////////////////////////////////////////////////////////////////
        constexpr T & value() const;
        
        ////////////////////////////////////////////////////////////////////////
        explicit constexpr operator bool() const noexcept;
        
        constexpr bool good() const noexcept;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    constexpr bool operator==(optional<T> const & lhs, optional<T> const & rhs);
    
    template <class T>
    constexpr bool operator!=(optional<T> const & lhs, optional<T> const & rhs);
    
    template <class T>
    constexpr bool operator<(optional<T> const & lhs, optional<T> const & rhs);

    template <class T>
    constexpr bool operator>(optional<T> const & lhs, optional<T> const & rhs);
    
    template <class T>
    constexpr bool operator<=(optional<T> const & lhs, optional<T> const & rhs);
    
    template <class T>
    constexpr bool operator>=(optional<T> const & lhs, optional<T> const & rhs);
        
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator==(optional<T> const & lhs, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator==(nullopt_t, optional<T> const & rhs) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator!=(optional<T> const & lhs, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator!=(nullopt_t, optional<T> const & rhs) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator<(optional<T> const &, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator<(nullopt_t, optional<T> const & rhs) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T> 
    constexpr bool operator<=(optional<T> const & lhs, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator<=(nullopt_t, optional<T> const &) noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    constexpr bool operator>(optional<T> const & lhs, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator>(nullopt_t, optional<T> const &) noexcept;
    
    template <class T>
    constexpr bool operator>=(optional<T> const &, nullopt_t) noexcept;
    
    template <class T> 
    constexpr bool operator>=(nullopt_t, optional<T> const & rhs) noexcept;
    
    template <class T> 
    constexpr bool operator==(optional<T> const & lhs, T const & rhs);
    
    template <class T>
    constexpr bool operator==(T const & lhs, optional<T> const & rhs);

    template <class T>
    constexpr bool operator!=(optional<T> const & lhs, T const & rhs);
    
    template <class T> 
    constexpr bool operator!=(T const & lhs, optional<T> const & rhs);
   
    template <class T>
    constexpr bool operator<(optional<T> const & lhs, T const & rhs);
    
    template <class T> 
    constexpr bool operator<(T const & lhs, optional<T> const & rhs);
    
    template <class T> 
    constexpr bool operator>(optional<T> const & lhs, T const & rhs);
    
    template <class T> 
    constexpr bool operator>(T const & lhs, optional<T> const & rhs);
    
    template <class T> 
    constexpr bool operator<=(optional<T> const & lhs, T const & rhs);
    
    template <class T> 
    constexpr bool operator<=(T const & lhs, optional<T> const & rhs);
    
    template <class T> 
    constexpr bool operator>=(optional<T> const & lhs, T const & rhs);
    
    template <class T>
    constexpr bool operator>=(T const & lhs, optional<T> const & rhs);
    
    template <class T> 
    void swap(optional<T> & lhs, optional<T> & rhs);
    
    template <class T> 
    constexpr optional<aux::decay_t<T>> make_optional(T && v);
}                                                             // namespace elib
namespace std
{
    template <class T>
    struct hash< ::elib::optional<T>>;
    
    template <class T>
    struct hash< ::elib::optional<T &>>;
}
#endif /* ELIB_OPTIONAL_HPP */