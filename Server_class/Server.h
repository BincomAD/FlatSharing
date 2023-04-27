//
// Created by SashaD on 04.04.23.
//

#ifndef FS_TEST_SERVER_H
#define FS_TEST_SERVER_H


#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <boost/beast/http.hpp>

namespace http = boost::beast::http;

class Server {
public:
    explicit Server(unsigned short port);
    void run();

private:
    void do_session(boost::asio::ip::tcp::socket socket);

private:
    boost::asio::io_context ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
};


#endif //FS_TEST_SERVER_H
