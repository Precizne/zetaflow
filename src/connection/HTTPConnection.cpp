#include <iostream>

#include "connection/HTTPConnection.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace ZetaFlow {
namespace Connection {

HTTPConnection::HTTPConnection(const std::string& host, short port) : host_(host), port_(port), socket_(io_ctx_) {
    std::cout << "[HttpConnection] Attempting to connect to " << host_ << ":" << port_ << std::endl;

    tcp::resolver resolver(io_ctx_);
    auto endpoints = resolver.resolve(host_, std::to_string(port_));
    boost::asio::connect(socket_, endpoints);

    std::cout << "[HttpConnection] Connected to " << host_ << ":" << port_ << std::endl;
}

void HTTPConnection::send(const std::string &data) {
    std::cout << "[HttpConnection] Sending data: " << data << std::endl;

    boost::asio::write(socket_, boost::asio::buffer(data));

    std::cout << "[HttpConnection] Data sent successfully." << std::endl;
}

std::string HTTPConnection::receive() {
    std::vector<char> buffer(1024);
    size_t len = socket_.read_some(boost::asio::buffer(buffer));
    std::string response(buffer.data(), len);

    std::cout << "[HttpConnection] Received data (" << len << " bytes): " << response << std::endl;

    return response;
}

}
}
