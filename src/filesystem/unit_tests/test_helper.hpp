#ifndef FILESYSTEM_UNIT_TEST_TEST_HELPER_HPP
#define FILESYSTEM_UNIT_TEST_TEST_HELPER_HPP

# include <elib/filesystem/config.hpp>
# include <elib/filesystem/path.hpp>

# ifndef ELIB_FILESYSTEM_UNIT_TEST_PATH
#   error ELIB_FILESYSTEM_UNIT_TEST_PATH must be set to the directory of this file
# endif

# ifndef ELIB_ROOT_PATH
#   error ELIB_ROOT_PATH must point to the top level of elib
# endif

const elib::fs::path elib_root = ELIB_ROOT_PATH;
const elib::fs::path test_root = ELIB_FILESYSTEM_UNIT_TEST_PATH;

#endif /* FILESYSTEM_UNIT_TEST_TEST_HELPER_HPP */