// REQUIRES: ELIB_FILESYSTEM
#include <elib/filesystem/file_status.hpp>
#include <elib/filesystem/filesystem_error.hpp>
#include <elib/filesystem/operations.hpp>
#include <elib/filesystem/path.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib;
using namespace elib::fs;

TEST_SUITE(filesystem_file_status_query_test_suite)

TEST_CASE(file_type_none_test)
{
    const file_status st(file_type::none);
    TEST_CHECK(not status_known(st));
    TEST_CHECK(not exists(st));
    TEST_CHECK(not is_block_file(st));
    TEST_CHECK(not is_character_file(st));
    TEST_CHECK(not is_directory(st));
    TEST_CHECK(not is_fifo(st));
    TEST_CHECK(not is_other(st));
    TEST_CHECK(not is_regular_file(st));
    TEST_CHECK(not is_socket(st));
    TEST_CHECK(not is_symlink(st));
}

TEST_CASE(file_type_not_found_test)
{
    const file_status st(file_type::not_found);
    TEST_CHECK(status_known(st));
    TEST_CHECK(not exists(st));
    TEST_CHECK(not is_block_file(st));
    TEST_CHECK(not is_character_file(st));
    TEST_CHECK(not is_directory(st));
    TEST_CHECK(not is_fifo(st));
    TEST_CHECK(not is_other(st));
    TEST_CHECK(not is_regular_file(st));
    TEST_CHECK(not is_socket(st));
    TEST_CHECK(not is_symlink(st));
}

TEST_CASE(file_type_unknown_test)
{
    const file_status st(file_type::unknown);
    TEST_CHECK(status_known(st));
    TEST_CHECK(exists(st));
    TEST_CHECK(not is_block_file(st));
    TEST_CHECK(not is_character_file(st));
    TEST_CHECK(not is_directory(st));
    TEST_CHECK(not is_fifo(st));
    TEST_CHECK(is_other(st));
    TEST_CHECK(not is_regular_file(st));
    TEST_CHECK(not is_socket(st));
    TEST_CHECK(not is_symlink(st));
}

TEST_CASE(file_type_regular_test)
{
    const file_status st(file_type::regular);
    TEST_CHECK(status_known(st));
    TEST_CHECK(exists(st));
    TEST_CHECK(not is_block_file(st));
    TEST_CHECK(not is_character_file(st));
    TEST_CHECK(not is_directory(st));
    TEST_CHECK(not is_fifo(st));
    TEST_CHECK(not is_other(st));
    TEST_CHECK(is_regular_file(st));
    TEST_CHECK(not is_socket(st));
    TEST_CHECK(not is_symlink(st));
}

TEST_CASE(file_type_directory_test)
{
    const file_status st(file_type::directory);
    TEST_CHECK(status_known(st));
    TEST_CHECK(exists(st));
    TEST_CHECK(not is_block_file(st));
    TEST_CHECK(not is_character_file(st));
    TEST_CHECK(is_directory(st));
    TEST_CHECK(not is_fifo(st));
    TEST_CHECK(not is_other(st));
    TEST_CHECK(not is_regular_file(st));
    TEST_CHECK(not is_socket(st));
    TEST_CHECK(not is_symlink(st));
}

TEST_CASE(file_type_symlink_test)
{
    const file_status st(file_type::symlink);
    TEST_CHECK(status_known(st));
    TEST_CHECK(exists(st));
    TEST_CHECK(not is_block_file(st));
    TEST_CHECK(not is_character_file(st));
    TEST_CHECK(not is_directory(st));
    TEST_CHECK(not is_fifo(st));
    TEST_CHECK(not is_other(st));
    TEST_CHECK(not is_regular_file(st));
    TEST_CHECK(not is_socket(st));
    TEST_CHECK(is_symlink(st));
}

TEST_CASE(file_type_block_test)
{
    const file_status st(file_type::block);
    TEST_CHECK(status_known(st));
    TEST_CHECK(exists(st));
    TEST_CHECK(is_block_file(st));
    TEST_CHECK(not is_character_file(st));
    TEST_CHECK(not is_directory(st));
    TEST_CHECK(not is_fifo(st));
    TEST_CHECK(is_other(st));
    TEST_CHECK(not is_regular_file(st));
    TEST_CHECK(not is_socket(st));
    TEST_CHECK(not is_symlink(st));
}

TEST_CASE(file_type_character_test)
{
    const file_status st(file_type::character);
    TEST_CHECK(status_known(st));
    TEST_CHECK(exists(st));
    TEST_CHECK(not is_block_file(st));
    TEST_CHECK(is_character_file(st));
    TEST_CHECK(not is_directory(st));
    TEST_CHECK(not is_fifo(st));
    TEST_CHECK(is_other(st));
    TEST_CHECK(not is_regular_file(st));
    TEST_CHECK(not is_socket(st));
    TEST_CHECK(not is_symlink(st));
}

TEST_CASE(file_type_fifo_test)
{
    const file_status st(file_type::fifo);
    TEST_CHECK(status_known(st));
    TEST_CHECK(exists(st));
    TEST_CHECK(not is_block_file(st));
    TEST_CHECK(not is_character_file(st));
    TEST_CHECK(not is_directory(st));
    TEST_CHECK(is_fifo(st));
    TEST_CHECK(is_other(st));
    TEST_CHECK(not is_regular_file(st));
    TEST_CHECK(not is_socket(st));
    TEST_CHECK(not is_symlink(st));
}

TEST_CASE(file_type_socket_test)
{
    const file_status st(file_type::socket);
    TEST_CHECK(status_known(st));
    TEST_CHECK(exists(st));
    TEST_CHECK(not is_block_file(st));
    TEST_CHECK(not is_character_file(st));
    TEST_CHECK(not is_directory(st));
    TEST_CHECK(not is_fifo(st));
    TEST_CHECK(is_other(st));
    TEST_CHECK(not is_regular_file(st));
    TEST_CHECK(is_socket(st));
    TEST_CHECK(not is_symlink(st));
}

TEST_SUITE_END()