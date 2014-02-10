#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/web/fwd.hpp>
#include <elib/web/socket.hpp>

#include <string>
#include <system_error>
#include <vector>

#include <iostream>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// needed to disambiguate web::socket from ::socket
namespace test
{
    
using namespace elib::web;
using elib::web::socket;

BOOST_AUTO_TEST_SUITE(prox_socket_test_suite)

BOOST_AUTO_TEST_CASE(prox_socket_error_test)
{
    socket_error e1{"se1", std::error_code{0, std::system_category()}};
    BOOST_CHECK(e1.what() == std::string{"se1"});
    BOOST_CHECK((e1.error_code() == std::error_code{0, std::system_category()}));
    
    const std::error_code ec{EBADF, std::system_category()};
    const std::string s{"This is What!"};
    socket_error e2{s, ec};
    BOOST_CHECK(e2.what() == s);
    BOOST_CHECK(e2.error_code() == ec);
}

BOOST_AUTO_TEST_CASE(prox_socket_default_test)
{
    socket s;
    BOOST_CHECK(s.raw_socket() == -1);
    BOOST_CHECK(!s.is_open());
    BOOST_CHECK(!s.good());
    BOOST_CHECK(!s.fail());
    BOOST_CHECK(!((bool)s));
    BOOST_CHECK((s.error_code() == std::error_code{0, std::system_category()}));
}

BOOST_AUTO_TEST_CASE(prox_socket_open_close_test)
{    
    socket s{sock_domain::inet, sock_type::stream, 0};
    
    BOOST_CHECK(s.is_open());
    BOOST_CHECK(s.raw_socket() != 0);
    BOOST_CHECK(s.good() && ((bool)s) && !s.fail());
    BOOST_CHECK(s.error_code() == std::error_code{});
    
    s.close();
    BOOST_CHECK(!s.fail() && !s.good() && !s.is_open());
    BOOST_CHECK(s.error_code() == std::error_code{});
    BOOST_CHECK(s.raw_socket() == -1);
    
    s.close();
    BOOST_CHECK(!s.fail() && !s.good() && !s.is_open());
    BOOST_CHECK(s.error_code() == std::error_code{});
    BOOST_CHECK(s.raw_socket() == -1);
}

BOOST_AUTO_TEST_CASE(prox_socket_bind_listen_test)
{
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(7050);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    socket s{sock_domain::inet, sock_type::stream, 0};
    BOOST_REQUIRE(s.good());

    s.bind(server);
    BOOST_CHECK(s.good());
    
    s.listen(5);
    BOOST_CHECK(s.good());
    
    s.close();
    BOOST_CHECK(!s.fail() && !s.is_open());
}

BOOST_AUTO_TEST_SUITE_END()

}                                                           // namespace test