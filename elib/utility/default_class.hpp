#ifndef ELIB_UTILITY_DEFAULT_CLASS_HPP
#define ELIB_UTILITY_DEFAULT_CLASS_HPP
#
#  /* default constructor macro */
# define ELIB_DEFAULT_CLASS(Class)          \
  Class() = default;                        \
                                            \
  Class(const Class&) = default;            \
  Class(Class&&) = default;                 \
                                            \
  Class& operator=(const Class&) = default; \
  Class& operator=(Class&&) = default
# 
# 
#endif /* ELIB_UTILITY_DEFAULT_CLASS_HPP */