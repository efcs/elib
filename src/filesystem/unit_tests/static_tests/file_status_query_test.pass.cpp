// REQUIRES: ELIB_FILESYSTEM_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem/file_status.hpp>
#include <elib/filesystem/filesystem_error.hpp>
#include <elib/filesystem/operations.hpp>
#include <elib/filesystem/path.hpp>

using namespace elib;
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(filesystem_file_status_query_test_suite)

BOOST_AUTO_TEST_CASE(file_type_none_test)
{
    const file_status st(file_type::none);
    BOOST_CHECK(not status_known(st));
    BOOST_CHECK(not exists(st));
    BOOST_CHECK(not is_block_file(st));
    BOOST_CHECK(not is_character_file(st));
    BOOST_CHECK(not is_directory(st));
    BOOST_CHECK(not is_fifo(st));
    BOOST_CHECK(not is_other(st));
    BOOST_CHECK(not is_regular_file(st));
    BOOST_CHECK(not is_socket(st));
    BOOST_CHECK(not is_symlink(st));
}

BOOST_AUTO_TEST_CASE(file_type_not_found_test)
{
    const file_status st(file_type::not_found);
    BOOST_CHECK(status_known(st));
    BOOST_CHECK(not exists(st));
    BOOST_CHECK(not is_block_file(st));
    BOOST_CHECK(not is_character_file(st));
    BOOST_CHECK(not is_directory(st));
    BOOST_CHECK(not is_fifo(st));
    BOOST_CHECK(not is_other(st));
    BOOST_CHECK(not is_regular_file(st));
    BOOST_CHECK(not is_socket(st));
    BOOST_CHECK(not is_symlink(st));
}

BOOST_AUTO_TEST_CASE(file_type_unknown_test)
{
    const file_status st(file_type::unknown);
    BOOST_CHECK(status_known(st));
    BOOST_CHECK(exists(st));
    BOOST_CHECK(not is_block_file(st));
    BOOST_CHECK(not is_character_file(st));
    BOOST_CHECK(not is_directory(st));
    BOOST_CHECK(not is_fifo(st));
    BOOST_CHECK(is_other(st));
    BOOST_CHECK(not is_regular_file(st));
    BOOST_CHECK(not is_socket(st));
    BOOST_CHECK(not is_symlink(st));
}

BOOST_AUTO_TEST_CASE(file_type_regular_test)
{
    const file_status st(file_type::regular);
    BOOST_CHECK(status_known(st));
    BOOST_CHECK(exists(st));
    BOOST_CHECK(not is_block_file(st));
    BOOST_CHECK(not is_character_file(st));
    BOOST_CHECK(not is_directory(st));
    BOOST_CHECK(not is_fifo(st));
    BOOST_CHECK(not is_other(st));
    BOOST_CHECK(is_regular_file(st));
    BOOST_CHECK(not is_socket(st));
    BOOST_CHECK(not is_symlink(st));
}

BOOST_AUTO_TEST_CASE(file_type_directory_test)
{
    const file_status st(file_type::directory);
    BOOST_CHECK(status_known(st));
    BOOST_CHECK(exists(st));
    BOOST_CHECK(not is_block_file(st));
    BOOST_CHECK(not is_character_file(st));
    BOOST_CHECK(is_directory(st));
    BOOST_CHECK(not is_fifo(st));
    BOOST_CHECK(not is_other(st));
    BOOST_CHECK(not is_regular_file(st));
    BOOST_CHECK(not is_socket(st));
    BOOST_CHECK(not is_symlink(st));
}

BOOST_AUTO_TEST_CASE(file_type_symlink_test)
{
    const file_status st(file_type::symlink);
    BOOST_CHECK(status_known(st));
    BOOST_CHECK(exists(st));
    BOOST_CHECK(not is_block_file(st));
    BOOST_CHECK(not is_character_file(st));
    BOOST_CHECK(not is_directory(st));
    BOOST_CHECK(not is_fifo(st));
    BOOST_CHECK(not is_other(st));
    BOOST_CHECK(not is_regular_file(st));
    BOOST_CHECK(not is_socket(st));
    BOOST_CHECK(is_symlink(st));
}

BOOST_AUTO_TEST_CASE(file_type_block_test)
{
    const file_status st(file_type::block);
    BOOST_CHECK(status_known(st));
    BOOST_CHECK(exists(st));
    BOOST_CHECK(is_block_file(st));
    BOOST_CHECK(not is_character_file(st));
    BOOST_CHECK(not is_directory(st));
    BOOST_CHECK(not is_fifo(st));
    BOOST_CHECK(is_other(st));
    BOOST_CHECK(not is_regular_file(st));
    BOOST_CHECK(not is_socket(st));
    BOOST_CHECK(not is_symlink(st));
}

BOOST_AUTO_TEST_CASE(file_type_character_test)
{
    const file_status st(file_type::character);
    BOOST_CHECK(status_known(st));
    BOOST_CHECK(exists(st));
    BOOST_CHECK(not is_block_file(st));
    BOOST_CHECK(is_character_file(st));
    BOOST_CHECK(not is_directory(st));
    BOOST_CHECK(not is_fifo(st));
    BOOST_CHECK(is_other(st));
    BOOST_CHECK(not is_regular_file(st));
    BOOST_CHECK(not is_socket(st));
    BOOST_CHECK(not is_symlink(st));
}

BOOST_AUTO_TEST_CASE(file_type_fifo_test)
{
    const file_status st(file_type::fifo);
    BOOST_CHECK(status_known(st));
    BOOST_CHECK(exists(st));
    BOOST_CHECK(not is_block_file(st));
    BOOST_CHECK(not is_character_file(st));
    BOOST_CHECK(not is_directory(st));
    BOOST_CHECK(is_fifo(st));
    BOOST_CHECK(is_other(st));
    BOOST_CHECK(not is_regular_file(st));
    BOOST_CHECK(not is_socket(st));
    BOOST_CHECK(not is_symlink(st));
}

BOOST_AUTO_TEST_CASE(file_type_socket_test)
{
    const file_status st(file_type::socket);
    BOOST_CHECK(status_known(st));
    BOOST_CHECK(exists(st));
    BOOST_CHECK(not is_block_file(st));
    BOOST_CHECK(not is_character_file(st));
    BOOST_CHECK(not is_directory(st));
    BOOST_CHECK(not is_fifo(st));
    BOOST_CHECK(is_other(st));
    BOOST_CHECK(not is_regular_file(st));
    BOOST_CHECK(is_socket(st));
    BOOST_CHECK(not is_symlink(st));
}

BOOST_AUTO_TEST_SUITE_END()