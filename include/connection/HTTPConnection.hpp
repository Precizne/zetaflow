#pragma once

#include <string>

#include <boost/asio.hpp>

#include "connection/IConnection.hpp"

namespace ZetaFlow {
namespace Connection {

class HTTPConnection : public IConnection {
public:
    HTTPConnection(const std::string& host, short port);
    void send(const std::string& data) override;
    std::string receive() override;

private:
    std::string host_;
    int port_;
    boost::asio::io_context io_ctx_;
    boost::asio::ip::tcp::socket socket_;
};

}
}
