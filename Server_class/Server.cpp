//
// Created by nikita on 14.04.23.
//
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include "Server.h"
#include "../urls/index/IndexPage.h"
#include "../urls/flatList/FlatListPage.h"
#include "../urls/CurrentFlatPage/CurrentFlatPage.h"
#include "../urls/LockStatusPage/LockStatusPage.h"
#include "../urls/RegistrationPage/RegistrationPage.h"
#include "../urls/LogIn/LoginPage.h"
#include "../urls/UserPage/UserPage.h"
#include "../urls/RentAFlat/RentAFlatPage.h"

#define PAGE_WAS_NOT_FOUND "Page was not found"

void Server::do_session(boost::asio::ip::tcp::socket socket) {
    try
    {
        // getting data from client
        boost::beast::flat_buffer buffer;
        std::shared_ptr request = std::make_shared<http::request<http::string_body>>();
        http::read(socket, buffer, (*request));
        std::string responseStr;

        auto target {request->target().to_string()};
        std::string url = target.substr(0, target.find_first_of("?"));
        std::shared_ptr<http::response<http::string_body>> response = std::make_shared<http::response<http::string_body>>();


        if (url == "/") {
            IndexPage page(request);
            (*response) = page.getResponse();
        } else if (url == "/flats"){
            FlatListPage page(request);
            (*response) = page.getResponse();
        } else if(url == "/flat"){
            CurrentFlatPage page(request);
            (*response) = page.getResponse();
        } else if(url == "/lock_status"){
            LockStatusPage page(request);
            (*response) = page.getResponse();
        } else if(url == "/registration"){
            RegistrationPage page(request);
            (*response) = page.getResponse();
        } else if(url == "/login"){
            LoginPage page(request);
            (*response) = page.getResponse();
        } else if(url == "/userpage"){
            UserPage page(request);
            (*response) = page.getResponse();
        } else if(url == "/rentaflat"){
            RentAFlatPage page(request);
            (*response) = page.getResponse();
        } else{
            (*response).result(http::status::not_found);
            (*response).set(http::field::content_type, "text/html");
            (*response).body() = PAGE_WAS_NOT_FOUND;
        }

        //send response to client
        response->set(http::field::access_control_allow_origin, "*");
        response->set(http::field::server, BOOST_BEAST_VERSION_STRING);
        response->keep_alive(request->keep_alive());
        response->prepare_payload();
        http::write(socket, (*response));
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Server::run() {
    // endless cycle for connections accepting
    while (true)
    {
        boost::asio::ip::tcp::socket socket{ioc_};
        acceptor_.accept(socket);
        std::thread{&Server::do_session, this, std::move(socket)}.detach();
    }
}

Server::Server(unsigned short port) : acceptor_(ioc_, {boost::asio::ip::tcp::v4(), port})
{
    std::cout << "Server listening on port " << port << std::endl;
}
