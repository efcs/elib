#ifndef STATIC_TEST_HELPER_HPP
#define STATIC_TEST_HELPER_HPP

# include "test_helper.hpp"

const elib::fs::path static_test_env_path = ELIB_FILESYSTEM_UNIT_TEST_PATH / elib::fs::path("static_test_env");

inline elib::fs::path make_static_env_path(elib::fs::path const & p)
{
    static const elib::fs::path root_p = ELIB_FILESYSTEM_UNIT_TEST_PATH / elib::fs::path("static_test_env");
    return root_p / p;
}

#endif /* STATIC_TEST_HELPER_HPP */