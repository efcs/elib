#ifndef ELIB_ENABLE_IF_HPP
#define ELIB_ENABLE_IF_HPP

# include <type_traits>

/* thanks to Matt Calabrese for new style enable if 
* and eric neibler for macro impl
*/
# define ELIB_ENABLE_IF(...)                                              \
  typename std::enable_if<static_cast<bool>(__VA_ARGS__)>::type* const& = \
    ::elib::enable_if_detail::enabler
# 
# 
# define ELIB_ENABLE_IF_VALID_EXPR(...)              \
  decltype(static_cast<void>(__VA_ARGS__))* const& = \
    ::elib::enable_if_detail::enabler
# 
# 
namespace elib 
{
  namespace enable_if_detail
  {
    extern void* enabler;
  }
}                                                           // namespace elib
#endif /* ELIB_ENABLE_IF_HPP */