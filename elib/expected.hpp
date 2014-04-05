#ifndef ELIB_EXPECTED_HPP
# define ELIB_EXPECTED_HPP

# include <elib/aux.hpp>
# include <exception>
# include <initializer_list>
# include <stdexcept>
# include <utility> /* for std::swap */

namespace elib
{

class bad_expected_access;

    // ??, expected for object types
template <class T, class E = std::exception_ptr>
class expected;
template <class E>
class expected<void, E>;
// ??, unexpected object type
template <class E>
struct unexpected{};

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
