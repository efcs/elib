// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include <stdlib.h> /* for putenv */
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

// putenv takes a char* (not const char*) so suppress the warning
#if defined(__clang__) && ELIB_COMPILER_VERSION < 30500L
# pragma clang diagnostic ignored "-Wdeprecated-writable-strings"
# elif defined(__clang__)
# pragma clang diagnostic ignored "-Wwritable-strings"
# elif defined(__GNUC__)
# pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

namespace
{
    void clean_env()
    {
        ELIB_ASSERT_ALWAYS(::unsetenv("TMPDIR") == 0);
        ELIB_ASSERT_ALWAYS(::unsetenv("TMP") == 0);
        ELIB_ASSERT_ALWAYS(::unsetenv("TEMP") == 0);
        ELIB_ASSERT_ALWAYS(::unsetenv("TEMPDIR") == 0);
    }
}                                                           // namespace

TEST_SUITE(elib_filesystem_static_temp_directory_path_test_suite)

TEST_CASE(tmpdir_env_test)
{
    clean_env();
    ELIB_ASSERT_ALWAYS(::putenv("TMPDIR=/") == 0);
    ELIB_ASSERT_ALWAYS(::putenv("TMP=/DNE") == 0);
    ELIB_ASSERT_ALWAYS(::putenv("TEMP=/DNE") == 0);
    ELIB_ASSERT_ALWAYS(::putenv("TEMPDIR=/DNE") == 0);
    
    path const expect("/");
    
    // with error code
    {
        std::error_code ec;
        path const ret = temp_directory_path(ec);
        TEST_REQUIRE(not ec);
        TEST_CHECK(ret == expect);
    }
    // no error code
    {
        path ret;
        TEST_REQUIRE_NO_THROW(ret = temp_directory_path());
        TEST_CHECK(ret == expect);
    }
}

TEST_CASE(tmp_env_test)
{
    clean_env();
    ELIB_ASSERT_ALWAYS(::putenv("TMP=/") == 0);
    ELIB_ASSERT_ALWAYS(::putenv("TEMP=/DNE") == 0);
    ELIB_ASSERT_ALWAYS(::putenv("TEMPDIR=/DNE") == 0);
    path const expect("/");
    
    // with error code
    {
        std::error_code ec;
        path const ret = temp_directory_path(ec);
        TEST_REQUIRE(not ec);
        TEST_CHECK(ret == expect);
    }
    // no error code
    {
        path ret;
        TEST_REQUIRE_NO_THROW(ret = temp_directory_path());
        TEST_CHECK(ret == expect);
    }
}

TEST_CASE(temp_env_test)
{
    clean_env();
    ELIB_ASSERT_ALWAYS(::putenv("TEMP=/") == 0);
    ELIB_ASSERT_ALWAYS(::putenv("TEMPDIR=/DNE") == 0);
    path const expect("/");
    
    // with error code
    {
        std::error_code ec;
        path const ret = temp_directory_path(ec);
        TEST_REQUIRE(not ec);
        TEST_CHECK(ret == expect);
    }
    // no error code
    {
        path ret;
        TEST_REQUIRE_NO_THROW(ret = temp_directory_path());
        TEST_CHECK(ret == expect);
    }
}

TEST_CASE(tempdir_env_test)
{
    clean_env();
    ELIB_ASSERT_ALWAYS(::putenv("TEMPDIR=/") == 0);
    path const expect("/");
    
    // with error code
    {
        std::error_code ec;
        path const ret = temp_directory_path(ec);
        TEST_REQUIRE(not ec);
        TEST_CHECK(ret == expect);
    }
    // no error code
    {
        path ret;
        TEST_REQUIRE_NO_THROW(ret = temp_directory_path());
        TEST_CHECK(ret == expect);
    }
}

TEST_CASE(bad_env_test)
{
    clean_env();
    ELIB_ASSERT_ALWAYS(::putenv("TMPDIR=/DNE") == 0);
    ELIB_ASSERT_ALWAYS(::putenv("TMP=/") == 0);
    
    path const expect("");
    
    // with error code
    {
        std::error_code ec;
        path const ret = temp_directory_path(ec);
        TEST_REQUIRE(ec);
        TEST_CHECK(ret == expect);
    }
    // no error code
    {
        TEST_REQUIRE_THROW(filesystem_error,  temp_directory_path());
    }
}

TEST_CASE(no_env_set_test)
{
    clean_env();
    path const expect("/tmp");
    // with error code
    {
        std::error_code ec;
        path const ret = temp_directory_path(ec);
        TEST_REQUIRE(not ec);
        TEST_CHECK(ret == expect);
    }
    // no error code
    {
        path ret;
        TEST_REQUIRE_NO_THROW(ret = temp_directory_path());
        TEST_CHECK(ret == expect);
    }
}


TEST_SUITE_END()