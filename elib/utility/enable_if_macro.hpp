#ifndef ELIB_UTILITY_ENABLE_IF_MACRO_HPP
#define ELIB_UTILITY_ENABLE_IF_MACRO_HPP

# include <type_traits>
# include <elib/utility/static_const.hpp>

/* implementation from eric_niebler in proto-0x
 * via Matt Calabrese */
# define ELIB_ENABLE_IF(...)                                               \
  typename std::enable_if<static_cast<bool>(__VA_ARGS__)>::type* const & = \
    ::elib::static_const<void*>::value
# 
# 
# define ELIB_ENABLE_IF_VALID_EXPR(...)               \
  decltype(static_cast<void>(__VA_ARGS__))* const & = \
    ::elib::static_const<void*>::value

#endif /* ELIB_UTILITY_ENABLE_IF_MACRO_HPP */