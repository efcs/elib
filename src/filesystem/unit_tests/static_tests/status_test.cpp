#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_static_status_test_suite)

BOOST_AUTO_TEST_CASE(dne_file_test)
{
    path const file = make_static_env_path("dne");
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(status(file));
        
        BOOST_REQUIRE(not exists(st));
        BOOST_REQUIRE(not is_block_file(st));
        BOOST_REQUIRE(not is_character_file(st));
        BOOST_REQUIRE(not is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(not is_other(st));
        BOOST_REQUIRE(not is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(symlink_status(file));
        
        BOOST_REQUIRE(not exists(st));
        BOOST_REQUIRE(not is_block_file(st));
        BOOST_REQUIRE(not is_character_file(st));
        BOOST_REQUIRE(not is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(not is_other(st));
        BOOST_REQUIRE(not is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = exists(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_block_file(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_character_file(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_directory(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_fifo(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_regular_file(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_socket(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        BOOST_REQUIRE_NO_THROW(ret = exists(file));
        BOOST_REQUIRE(ret == false);
        
        BOOST_REQUIRE_NO_THROW(ret = is_block_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_character_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_directory(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_fifo(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_other(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_socket(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_symlink(file));
        BOOST_REQUIRE(not ret);
    }
}

BOOST_AUTO_TEST_CASE(regular_file_test)
{
    path const file = make_static_env_path("empty_file");
    
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(status(file));
        
        BOOST_REQUIRE(exists(st));
        BOOST_REQUIRE(not is_block_file(st));
        BOOST_REQUIRE(not is_character_file(st));
        BOOST_REQUIRE(not is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(not is_other(st));
        BOOST_REQUIRE(is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(symlink_status(file));
        
        BOOST_REQUIRE(exists(st));
        BOOST_REQUIRE(not is_block_file(st));
        BOOST_REQUIRE(not is_character_file(st));
        BOOST_REQUIRE(not is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(not is_other(st));
        BOOST_REQUIRE(is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = is_block_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_character_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_directory(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_fifo(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_regular_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret);
        
        ret = is_socket(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        
        BOOST_REQUIRE_NO_THROW(ret = is_block_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_character_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_directory(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_fifo(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_other(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        BOOST_REQUIRE(ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_socket(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_symlink(file));
        BOOST_REQUIRE(not ret);
    }
}

BOOST_AUTO_TEST_CASE(directory_test)
{
    path const file = make_static_env_path("dir1");
    
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(status(file));
        
        BOOST_REQUIRE(exists(st));
        BOOST_REQUIRE(not is_block_file(st));
        BOOST_REQUIRE(not is_character_file(st));
        BOOST_REQUIRE(is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(not is_other(st));
        BOOST_REQUIRE(not is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(symlink_status(file));
        
        BOOST_REQUIRE(exists(st));
        BOOST_REQUIRE(not is_block_file(st));
        BOOST_REQUIRE(not is_character_file(st));
        BOOST_REQUIRE(is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(not is_other(st));
        BOOST_REQUIRE(not is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = is_block_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_character_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_directory(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret);
        
        ret = is_fifo(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_regular_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_socket(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        
        BOOST_REQUIRE_NO_THROW(ret = is_block_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_character_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_directory(file));
        BOOST_REQUIRE(ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_fifo(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_other(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_socket(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_symlink(file));
        BOOST_REQUIRE(not ret);
    }
}

BOOST_AUTO_TEST_CASE(block_file_test)
{

#if defined(ELIB_CONFIG_LINUX)
    path const file("/dev/sda");
#elif defined(ELIB_CONFIG_APPLE)
    path const file("/dev/disk0");
#else
# error Platform not supported
#endif
    
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(status(file));
        
        BOOST_REQUIRE(exists(st));
        BOOST_REQUIRE(is_block_file(st));
        BOOST_REQUIRE(not is_character_file(st));
        BOOST_REQUIRE(not is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(is_other(st));
        BOOST_REQUIRE(not is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(symlink_status(file));
        
        BOOST_REQUIRE(exists(st));
        BOOST_REQUIRE(is_block_file(st));
        BOOST_REQUIRE(not is_character_file(st));
        BOOST_REQUIRE(not is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(is_other(st));
        BOOST_REQUIRE(not is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = is_block_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret);
        
        ret = is_character_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_directory(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_fifo(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret);
        
        ret = is_regular_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_socket(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        
        BOOST_REQUIRE_NO_THROW(ret = is_block_file(file));
        BOOST_REQUIRE(ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_character_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_directory(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_fifo(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_other(file));
        BOOST_REQUIRE(ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_socket(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_symlink(file));
        BOOST_REQUIRE(not ret);
    }
}

BOOST_AUTO_TEST_CASE(character_file_test)
{
    path const file("/dev/null");
    
    // status test
    {
        std::error_code ec;
        file_status const st = status(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(status(file));
        
        BOOST_REQUIRE(exists(st));
        BOOST_REQUIRE(not is_block_file(st));
        BOOST_REQUIRE(is_character_file(st));
        BOOST_REQUIRE(not is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(is_other(st));
        BOOST_REQUIRE(not is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    {
        std::error_code ec;
        file_status const st = symlink_status(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(status_known(st));
        
        BOOST_REQUIRE_NO_THROW(symlink_status(file));
        
        BOOST_REQUIRE(exists(st));
        BOOST_REQUIRE(not is_block_file(st));
        BOOST_REQUIRE(is_character_file(st));
        BOOST_REQUIRE(not is_directory(st));
        BOOST_REQUIRE(not is_fifo(st));
        BOOST_REQUIRE(is_other(st));
        BOOST_REQUIRE(not is_regular_file(st));
        BOOST_REQUIRE(not is_socket(st));
        BOOST_REQUIRE(not is_symlink(st));
    }
    // query from path test with error code
    {
        std::error_code ec;
        bool ret;
        
        ret = is_block_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_character_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret);
        
        ret = is_directory(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_fifo(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_other(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret);
        
        ret = is_regular_file(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_socket(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
        
        ret = is_symlink(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
    }
    // query with throwing versions
    {
        bool ret = false;
        
        BOOST_REQUIRE_NO_THROW(ret = is_block_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_character_file(file));
        BOOST_REQUIRE(ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_directory(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_fifo(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_other(file));
        BOOST_REQUIRE(ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_regular_file(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_socket(file));
        BOOST_REQUIRE(not ret);
        
        BOOST_REQUIRE_NO_THROW(ret = is_symlink(file));
        BOOST_REQUIRE(not ret);
    }
}

BOOST_AUTO_TEST_SUITE_END()