// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;


/// NOTE: queries for files that can be done staticly are in the static tests
TEST_SUITE(elib_filesystem_dynamic_status_test_suite)

TEST_CASE(symlink_to_filetest)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("file1");
    env.create_file(real_file);
    
    path const file = env.make_env_path("sym1");
    env.create_symlink(real_file, file);
    
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
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(not is_socket(st));
        TEST_REQUIRE(is_symlink(st));
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
        TEST_REQUIRE(ret);
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
        TEST_REQUIRE(ret);
    }
}

TEST_CASE(hardlink_to_filetest)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("file1");
    env.create_file(real_file);
    
    path const file = env.make_env_path("link1");
    env.create_hardlink(real_file, file);
    
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

TEST_CASE(fifo_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_fifo(file);
    
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
        TEST_REQUIRE(is_fifo(st));
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
        TEST_REQUIRE(not is_character_file(st));
        TEST_REQUIRE(not is_directory(st));
        TEST_REQUIRE(is_fifo(st));
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
        TEST_REQUIRE(not ret);
        
        ret = is_directory(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_fifo(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret);
        
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
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_directory(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_fifo(file));
        TEST_REQUIRE(ret);
        
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

TEST_CASE(socket_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("socket1");
    env.create_socket(file);
    
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
        TEST_REQUIRE(is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(is_socket(st));
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
        TEST_REQUIRE(is_other(st));
        TEST_REQUIRE(not is_regular_file(st));
        TEST_REQUIRE(is_socket(st));
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
        TEST_REQUIRE(ret);
        
        ret = is_regular_file(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
        
        ret = is_socket(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret);
        
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
        TEST_REQUIRE(ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        TEST_REQUIRE(not ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_socket(file));
        TEST_REQUIRE(ret);
        
        TEST_REQUIRE_NO_THROW(ret = is_symlink(file));
        TEST_REQUIRE(not ret);
    }
}



TEST_SUITE_END()