// REQUIRES: ELIB_FILESYSTEM
#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_static_status_test_suite)

TEST_CASE(dne_file_test)
{
    path const file = make_static_env_path("dne");
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(status(file));
        
        TEST_REQUIRE(not exists(st));
        TEST_REQUIRE(not is_block_file(st));
        TEST_REQUIRE(not is_character_file(st));
        TEST_REQUIRE(not is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(not is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(symlink_status(file));
        
        TEST_REQUIRE(not exists(st));
        TEST_REQUIRE(not is_block_file(st));
        TEST_REQUIRE(not is_character_file(st));
        TEST_REQUIRE(not is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(not is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = exists(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not ret);
        
        ret = is_block_file(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not ret);
        
        ret = is_character_file(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not ret);
        
        ret = is_directory(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not ret);
        
        ret = is_fifo(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not ret);
        
        ret = is_regular_file(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not ret);
        
        ret = is_socket(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        TEST_REQUIRE_NO_THROW(ret = exists(file));
        TEST_REQUIRE(ret == false);
        
        TEST_REQUIRE_NO_THROW(ret = is_block_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_character_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_directory(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_fifo(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_other(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_socket(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_symlink(file));
        TEST_REQUIRE(not ret);
    }
}

TEST_CASE(regular_file_test)
{
    path const file = make_static_env_path("empty_file");
    
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(status(file));
        
        TEST_REQUIRE(exists(st));
        TEST_REQUIRE(not is_block_file(st));
        TEST_REQUIRE(not is_character_file(st));
        TEST_REQUIRE(not is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(not is_other(st));
        TEST_REQUIRE(is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(symlink_status(file));
        
        TEST_REQUIRE(exists(st));
        TEST_REQUIRE(not is_block_file(st));
        TEST_REQUIRE(not is_character_file(st));
        TEST_REQUIRE(not is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(not is_other(st));
        TEST_REQUIRE(is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = is_block_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_character_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_directory(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_fifo(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_regular_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret);
        
        ret = is_socket(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        
        TEST_REQUIRE_NO_THROW(ret = is_block_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_character_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_directory(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_fifo(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_other(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        TEST_REQUIRE(ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_socket(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_symlink(file));
        TEST_REQUIRE(not ret);
    }
}

TEST_CASE(directory_test)
{
    path const file = make_static_env_path("dir1");
    
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(status(file));
        
        TEST_REQUIRE(exists(st));
        TEST_REQUIRE(not is_block_file(st));
        TEST_REQUIRE(not is_character_file(st));
        TEST_REQUIRE(is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(not is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(symlink_status(file));
        
        TEST_REQUIRE(exists(st));
        TEST_REQUIRE(not is_block_file(st));
        TEST_REQUIRE(not is_character_file(st));
        TEST_REQUIRE(is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(not is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = is_block_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_character_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_directory(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret);
        
        ret = is_fifo(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_regular_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_socket(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        
        TEST_REQUIRE_NO_THROW(ret = is_block_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_character_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_directory(file));
        TEST_REQUIRE(ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_fifo(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_other(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_socket(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_symlink(file));
        TEST_REQUIRE(not ret);
    }
}


TEST_CASE(block_file_test)
{

#if defined(ELIB_CONFIG_LINUX) || defined(ELIB_CONFIG_CYGWIN)
    path const file("/dev/sda");
#elif defined(ELIB_CONFIG_APPLE)
    path const file("/dev/disk0");
#else
# error Platform not supported
#endif
    
    if (!exists(file)) {
        TEST_CHECK(true);
        return;
    }
    
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(status(file));
        
        TEST_REQUIRE(exists(st));
        TEST_REQUIRE(is_block_file(st));
        TEST_REQUIRE(not is_character_file(st));
        TEST_REQUIRE(not is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(symlink_status(file));
        
        TEST_REQUIRE(exists(st));
        TEST_REQUIRE(is_block_file(st));
        TEST_REQUIRE(not is_character_file(st));
        TEST_REQUIRE(not is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = is_block_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret);
        
        ret = is_character_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_directory(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_fifo(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret);
        
        ret = is_regular_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_socket(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        
        TEST_REQUIRE_NO_THROW(ret = is_block_file(file));
        TEST_REQUIRE(ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_character_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_directory(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_fifo(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_other(file));
        TEST_REQUIRE(ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_socket(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_symlink(file));
        TEST_REQUIRE(not ret);
    }
}


TEST_CASE(character_file_test)
{
    path const file("/dev/null");
    
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(status(file));
        
        TEST_REQUIRE(exists(st));
        TEST_REQUIRE(not is_block_file(st));
        TEST_REQUIRE(is_character_file(st));
        TEST_REQUIRE(not is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(status_known(st));
        
        TEST_REQUIRE_NO_THROW(symlink_status(file));
        
        TEST_REQUIRE(exists(st));
        TEST_REQUIRE(not is_block_file(st));
        TEST_REQUIRE(is_character_file(st));
        TEST_REQUIRE(not is_directory(st));
        TEST_REQUIRE(not is_fifo(st));
        TEST_REQUIRE(is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = is_block_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_character_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret);
        
        ret = is_directory(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_fifo(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret);
        
        ret = is_regular_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_socket(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        
        TEST_REQUIRE_NO_THROW(ret = is_block_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_character_file(file));
        TEST_REQUIRE(ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_directory(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_fifo(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_other(file));
        TEST_REQUIRE(ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_socket(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_symlink(file));
        TEST_REQUIRE(not ret);
    }
}

TEST_SUITE_END()