// REQUIRES: ELIB_WEB
#include <elib/experimental/web/socket.hpp>
#include <string>
#include <system_error>
#include <vector>

#include <iostream>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "rapid-cxx-test.hpp"


TEST_SUITE(elib_web_socket_test_suite)

using namespace elib::web;
using elib::web::socket;

TEST_CASE(socket_error_test)
{
    socket_error e1{"se1", std::error_code{0, std::system_category()}};
    TEST_CHECK(e1.what() == std::string{"se1"});
    TEST_CHECK((e1.error_code() == std::error_code{0, std::system_category()}));
    
    const std::error_code ec{EBADF, std::system_category()};
    const std::string s{"This is What!"};
    socket_error e2{s, ec};
    TEST_CHECK(e2.what() == s);
    TEST_CHECK(e2.error_code() == ec);
}

TEST_CASE(default_test)
{
    socket s;
    TEST_CHECK(s.raw_socket() == -1);
    TEST_CHECK(!s.is_open());
    TEST_CHECK(!s.good());
    TEST_CHECK(!s.fail());
    TEST_CHECK(!bool(s));
    TEST_CHECK((s.error_code() == std::error_code{0, std::system_category()}));
}

TEST_CASE(open_close_test)
{    
    socket s{sock_domain::inet, sock_type::stream, 0};
    
    TEST_CHECK(s.is_open());
    TEST_CHECK(s.raw_socket() != 0);
    TEST_CHECK(s.good() && bool(s) && !s.fail());
    TEST_CHECK(s.error_code() == std::error_code{});
    
    s.close();
    TEST_CHECK(!s.fail() && !s.good() && !s.is_open());
    TEST_CHECK(s.error_code() == std::error_code{});
    TEST_CHECK(s.raw_socket() == -1);
    
    s.close();
    TEST_CHECK(!s.fail() && !s.good() && !s.is_open());
    TEST_CHECK(s.error_code() == std::error_code{});
    TEST_CHECK(s.raw_socket() == -1);
}

TEST_CASE(bind_listen_test)
{
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(7050);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    socket s{sock_domain::inet, sock_type::stream, 0};
    TEST_REQUIRE(s.good());

    s.bind(server);
    TEST_CHECK(s.good());
    
    s.listen(5);
    TEST_CHECK(s.good());
    
    s.close();
    TEST_CHECK(!s.fail() && !s.is_open());
}

TEST_SUITE_END()
