#include "communication/HttpConnection.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace ZetaFlow {
namespace Communication {

HttpConnection::HttpConnection(const std::string &host, int port) : host_(host), port_(port), socket_(io_ctx_) {
    tcp::resolver resolver(io_ctx_);
    auto endpoints = resolver.resolve(host, std::to_string(port));
    boost::asio::connect(socket_, endpoints);
}

void HttpConnection::send(const std::string &data) {
    boost::asio::write(socket_, boost::asio::buffer(data));
}

std::string HttpConnection::receive() {
    std::vector<char> buffer(1024);
    size_t length = socket_.read_some(boost::asio::buffer(buffer));
    return std::string(buffer.data(), length);
}

}
}
