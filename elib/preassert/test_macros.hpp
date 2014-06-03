#ifndef ELIB_PREASSERT_TEST_MACROS_HPP
#define ELIB_PREASSERT_TEST_MACROS_HPP
# 
# include <elib/preassert/core.hpp>
#
#endif /* ELIB_PREASSERT_TEST_MACROS_HPP */
#
#
#if defined(ELIB_PRE_ASSERT_PASS)
# undef ELIB_TEST_PRE_ASSERT_PASS
# undef ELIB_TEST_PRE_ASSERT_FAIL
# undef ELIB_TEST_PRE_ASSERT_SAFE_PASS
# undef ELIB_TEST_PRE_ASSERT_SAFE_FAIL
# undef ELIB_TEST_PRE_ASSERT_OPT_PASS
# undef ELIB_TEST_PRE_ASSERT_OPT_FAIL
#endif
#
#
#if defined(ELIB_PRE_ASSERT_IS_ACTIVE)
# // TODO
# define ELIB_TEST_PRE_ASSERT_PASS(...) (true)
# define ELIB_TEST_PRE_ASSERT_FAIL(...) (true)
#else
# define ELIB_TEST_PRE_ASSERT_PASS(...) (true)
# define ELIB_TEST_PRE_ASSERT_FAIL(...) (true)
#endif /* ELIB_PRE_ASSERT_IS_ACTIVE */
#
#
#if defined(ELIB_PRE_ASSERT_SAFE_IS_ACTIVE)
# // TODO
# define ELIB_TEST_PRE_ASSERT_SAFE_PASS(...) (true)
# define ELIB_TEST_PRE_ASSERT_SAFE_FAIL(...) (true)
#else
# define ELIB_TEST_PRE_ASSERT_SAFE_PASS(...) (true)
# define ELIB_TEST_PRE_ASSERT_SAFE_FAIL(...) (true)
#endif /* ELIB_PRE_ASSERT_SAFE_IS_ACTIVE */
#
#
#if defined(ELIB_PRE_ASSERT_OPT_IS_ACTIVE)
# // TODO
# define ELIB_TEST_PRE_ASSERT_OPT_PASS(...) (true)
# define ELIB_TEST_PRE_ASSERT_OPT_FAIL(...) (true)
#else
# define ELIB_TEST_PRE_ASSERT_OPT_PASS(...) (true)
# define ELIB_TEST_PRE_ASSERT_OPT_FAIL(...) (true)
#endif /* ELIB_PRE_ASSERT_OPT_IS_ACTIVE */
#
