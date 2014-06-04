#ifndef ELIB_CONTRACT_ASSERT_ASSERT_MACROS_HPP
#define ELIB_CONTRACT_ASSERT_ASSERT_MACROS_HPP
# 
# include <elib/experimental/contract_assert/core.hpp>
# 
#endif /* ELIB_CONTRACT_ASSERT_ASSERT_MACROS_HPP */
#
#
#if defined(ELIB_CONTRACT_ASSERT)
# undef ELIB_CONTRACT_ASSERT
# undef ELIB_CONTRACT_ASSERT_SAFE
# undef ELIB_CONTRACT_ASSERT_OPT
#endif
#
#
#if defined(ELIB_CONTRACT_ASSERT_IS_ACTIVE)
# 
# define ELIB_CONTRACT_ASSERT(...)                       \
    ( (__VA_ARGS__)                                      \
      ? ((void)0)                                        \
      : ::elib::preassert::assert_failed(                \
            ::elib::preassert::mode::dbg                 \
            , #__VA_ARGS__, __FILE__, __func__, __LINE__ \
        )                                                \
    )
# 
#else
# 
# define ELIB_CONTRACT_ASSERT(...) ((void)0)
# 
#endif /* ELIB_CONTRACT_ASSERT_IS_ACTIVE */
#
#
#if defined(ELIB_CONTRACT_ASSERT_SAFE_IS_ACTIVE)
# 
# define ELIB_CONTRACT_ASSERT_SAFE(...)                       \
    ( (__VA_ARGS__)                                      \
      ? ((void)0)                                        \
      : ::elib::preassert::assert_failed(                \
            ::elib::preassert::mode::safe                \
            , #__VA_ARGS__, __FILE__, __func__, __LINE__ \
        )                                                \
    )
# 
#else
# 
# define ELIB_CONTRACT_ASSERT_SAFE(...) ((void)0)
# 
#endif /* ELIB_CONTRACT_ASSERT_SAFE_IS_ACTIVE */
#
#
#if defined(ELIB_CONTRACT_ASSERT_OPT_IS_ACTIVE)
# 
# define ELIB_CONTRACT_ASSERT_OPT(...)                        \
    ( (__VA_ARGS__)                                      \
      ? ((void)0)                                        \
      : ::elib::preassert::assert_failed(                \
            ::elib::preassert::mode::opt                 \
            , #__VA_ARGS__, __FILE__, __func__, __LINE__ \
        )                                                \
    )
# 
#else
# 
# define ELIB_CONTRACT_ASSERT_OPT(...) ((void)0)
# 
#endif /* ELIB_CONTRACT_ASSERT_OPT_IS_ACTIVE */
#
