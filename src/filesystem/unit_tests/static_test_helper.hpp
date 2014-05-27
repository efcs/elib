#ifndef STATIC_TEST_HELPER_HPP
#define STATIC_TEST_HELPER_HPP

# include "test_helper.hpp"

const elib::fs::path static_test_env_path = test_root / elib::fs::path("static_test_env");

inline elib::fs::path make_static_env_path(elib::fs::path const & p)
{
    return static_test_env_path / p;
}

#endif /* STATIC_TEST_HELPER_HPP */