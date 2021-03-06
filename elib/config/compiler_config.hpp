#ifndef ELIB_CONFIG_COMPILER_CONFIG_HPP
#define ELIB_CONFIG_COMPILER_CONFIG_HPP
# 
# if defined(__clang__)
#   include <elib/config/compiler/clang.ipp>
# elif defined(__GNUC__)
#   include <elib/config/compiler/gcc.ipp>
# elif defined(_MSC_VER)
#   include <elib/config/compiler/msvc.ipp>
# elif defined(ELIB_ASSERT_CONFIG)
#   error "Unknown compiler"
# endif
# 
#endif /* ELIB_CONFIG_COMPILER_CONFIG_HPP */