#ifndef ELIB_EXPECTED_HPP
#define ELIB_EXPECTED_HPP

# include <elib/aux.hpp>
# include <elib/optional.hpp> /* for in_place_t */

# include <exception>
# include <initializer_list>
# include <stdexcept>
# include <utility> /* for std::swap */

namespace elib
{
    
    template <>
    
    namespace expected_detail
    {
        constexpr struct dummy_ctor_arg_t
        {
            struct init {};
            constexpr dummy_ctor_arg_t(init) {}
        } dummy_ctor_arg( dummy_ctor_arg_t::init{} );
        
        template <class T, class E>
        union default_storage
        {
            using value_type = T;
            using error_type = E;
            
            T value;
            E error;
            
            constexpr default_storage()
                noexcept(aux::has_nothrow_default_constructor<E>::value)
              : error()
            {}
            
            
            
            ~default_storage() {}
        };
    }                                             // namespace expected_detail

# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class bad_expected_access
      : std::logic_error
    {
    public:
        bad_expected_access(std::string const & what_arg)
          : std::logic_error(what_arg)
        {}
        
        explicit bad_expected_access(const char *what_arg)
          : std::logic_error(what_arg)
        {}
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

template <class E>
struct unexpected {};


template <class T, class E = std::exception_ptr>
class expected
{
public:
    using value_type = T;
    using error_type = E;
    
    constexpr expected() noexcept(false);
    constexpr expected(expected const &);
    expected(expected &&) noexcept(false);
    constexpr expected(T const &);
    constexpr expected(T &&);
    
    template <class ...Args>
    constexpr explicit expected(in_place_t, Args &&... args);
    
    template <class U, class ...Args>
    constexpr explicit expected(in_place_t, std::initializer_list<U>, Args &&...args);
    
    constexpr expected(unexpected<E> const &);
    
    template <class Err>
    constexpr expected(unexpected<Err> const &);
    
    ~expected() = default;
  
    expected & operator=(expected const &);
    expected & operator=(expected &&) noexcept(false);
    
    template <class U>
    expected & operator=(U &&);
    
    template <class ...Args>
    void emplace(Args &&... args);
    
    template <class U, class ...Args>
    void emplace(std::initializer_list<U>, Args &&...);
    
    void swap(expected &) noexcept(false);
    
    constexpr T const* operator->() const;
    
    T* operator->();
    
    constexpr T const & operator*() const ;
    T & operator*();
    
    constexpr explicit operator bool() const noexcept;
    constexpr bool has_value() const noexcept;
    constexpr bool has_error() const noexcept;
    
    constexpr T const & value() const;
    T & value();
    
    constexpr E const & error() const;
    E & error();
    
    template <class U>
    constexpr T value_or(U &&) const &;
    
    template <class U>
    T value_or(U &&) &&;
    
    template <class G>
    constexpr T value_or_throw() const &;
    
    template <class G>
    T value_or_throw() const &;
    
  
};


template <class E>
class expected<void, E>;

// ??, Relational operators
template <class T, class E>
constexpr bool operator==(const expected<T, E>&, const expected<T, E>&);
template <class T, class E>
constexpr bool operator!=(const expected<T, E>&, const expected<T, E>&);
template <class T, class E>
constexpr bool operator<(const expected<T, E>&, const expected<T, E>&);
template <class T, class E>
constexpr bool operator>(const expected<T, E>&, const expected<T, E>&);
template <class T, class E>
constexpr bool operator<=(const expected<T, E>&, const expected<T, E>&);
template <class T, class E>
constexpr bool operator>=(const expected<T, E>&, const expected<T, E>&);

// ??, Comparison with T
template <class T, class E>
constexpr bool operator==(expected<T, E> const & lhs, T const & rhs);
template <class T, class E>
constexpr bool operator==(T const & lhs, expected<T, E> const & rhs);

template <class T, class E>
constexpr bool operator!=(expected<T, E> const & lhs, T const & rhs);
template <class T, class E>
constexpr bool operator!=(T const & lhs, expected<T, E> const & rhs);

template <class T, class E>
constexpr bool operator<(expected<T, E> const & lhs, T const & rhs);
template <class T, class E>
constexpr bool operator<(T const & lhs, expected<T, E> const & rhs);

template <class T, class E>
constexpr bool operator>(expected<T, E> const & lhs, T const & rhs);
template <class T, class E>
constexpr bool operator>(T const & lhs, expected<T, E> const & rhs);

template <class T, class E>
constexpr bool operator<=(expected<T, E> const & lhs, T const & rhs);
template <class T, class E>
constexpr bool operator<=(T const & lhs, expected<T, E> const & rhs);

template <class T, class E>
constexpr bool operator>=(expected<T, E> const & lhs, T const & rhs);
template <class T, class E>
constexpr bool operator>=(T const & lhs, expected<T, E> const & rhs);

template <class T, class E>
void swap(expected<T, E> & lhs, expected<T, E> & rhs);

template <class T> constexpr expected<see below> make_expected(T&& v);
template <> constexpr expected<void> make_expected();
template <class T>
constexpr expected<T> make_expected_from_error(std::exception_ptr v);
template <class T, class E>
constexpr expected<T> make_expected_from_error(E&& v);
template <class T>
constexpr expected<T> make_expected_from_error();
template <class F>
constexpr typename expected<typename result_type<F>::type
make_expected_from_call(F f);

template <class T> struct hash;
template <class T> struct hash<expected<T, E>>;

}
#endif /* ELIB_EXPECTED_HPP */
