#ifndef TEST_HELPER_HPP
#define TEST_HELPER_HPP

# include <elib/filesystem/config.hpp>
# include <elib/filesystem/path.hpp>

#ifndef ELIB_FILESYSTEM_UNIT_TEST_PATH
# error ELIB_FILESYSTEM_UNIT_TEST_PATH must be set to the directory of this file
# endif

const elib::fs::path test_root = ELIB_FILESYSTEM_UNIT_TEST_PATH;

#endif /* TEST_HELPER_HPP */