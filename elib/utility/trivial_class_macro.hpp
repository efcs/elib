#ifndef ELIB_UTILITY_TRIVIAL_CLASS_MACRO_HPP
#define ELIB_UTILITY_TRIVIAL_CLASS_MACRO_HPP
# 
# define ELIB_TRIVIAL_CLASS(Name)           \
  Class() = default;                        \
                                            \
  Class(const Class&) = default;            \
  Class(Class&&) = default;                 \
                                            \
  Class& operator=(const Class&) = default; \
  Class& operator(Class&&) = default
# 
# 
#endif /* ELIB_UTILITY_TRIVIAL_CLASS_MACRO_HPP */