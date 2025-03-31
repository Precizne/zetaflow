#include <iostream>

#include "connection/HTTPConnection.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace ZetaFlow {
namespace Connection {

HTTPConnection::HTTPConnection(const std::string& host, short port) : host_(host), port_(port), socket_(io_ctx_) {
    std::cout << "[HTTPConnection] Attempting to connect to " << host_ << ":" << port_ << std::endl;

    tcp::resolver resolver(io_ctx_);
    auto endpoints = resolver.resolve(host_, std::to_string(port_));
    boost::system::error_code ec;
    boost::asio::connect(socket_, endpoints, ec);

    if(ec) {
        std::cerr << "[HTTPConnection] Failed to connect to " << host_ << ":" << port_ << " - " << ec.message() << std::endl;

        socket_.close();
    }
    else
        std::cout << "[HTTPConnection] Connected to " << host_ << ":" << port_ << std::endl;
}

void HTTPConnection::send(const std::string& data) {
    std::cout << "[HTTPConnection] Sending data: " << data << std::endl;

    if(!isConnected()) {
        std::cerr << "[HTTPConnection] Cannot send data; socket is not connected." << std::endl;

        return;
    }

    boost::asio::write(socket_, boost::asio::buffer(data));

    std::cout << "[HTTPConnection] Data sent successfully." << std::endl;
}

std::string HTTPConnection::receive() {
    std::cout << "[HTTPConnection] Receiving data: " << std::endl;
    
    if(!isConnected()) {
        std::cerr << "[HTTPConnection] Cannot send data; socket is not connected." << std::endl;

        return "";
    }

    std::vector<char> buffer(1024);
    size_t len = socket_.read_some(boost::asio::buffer(buffer));
    std::string response(buffer.data(), len);

    std::cout << "[HTTPConnection] Received data (" << len << " bytes): " << response << std::endl;

    return response;
}

bool HTTPConnection::isConnected() {
    return socket_.is_open();
}

}
}
