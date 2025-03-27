#pragma once

#include <string>

#include <boost/asio.hpp>

#include "IConnection.hpp"

namespace ZetaFlow {
namespace Communication {

class HttpConnection : public IConnection {
public:
    HttpConnection(const std::string &host, int port);
    void send(const std::string &data) override;
    std::string receive() override;

private:
    std::string host_;
    int port_;
    boost::asio::io_context io_ctx_;
    boost::asio::ip::tcp::socket socket_;
};

}
}
