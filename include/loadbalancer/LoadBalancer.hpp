#pragma once

#include <memory>
#include <string>
#include <vector>

#include <boost/asio.hpp>

#include "strategy/StrategyFactory.hpp"
#include "connection/ConnectionFactory.hpp"

namespace ZetaFlow {
namespace LoadBalancer {

class LoadBalancer {
public:
    LoadBalancer(short port, const std::vector<std::string>& servers, Strategy::StrategyType strategy_type, Connection::ConnectionType connection_type, short backend_port = 3101);
    void start();

private:
    void accept();
    void handleRequest(std::shared_ptr<boost::asio::ip::tcp::socket> client_socket);

    boost::asio::io_context io_ctx;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unique_ptr<Strategy::IStrategy> strategy;
    std::vector<std::string> backend_servers;
    Connection::ConnectionType connection_type;
    short backend_port;
};

}
}
