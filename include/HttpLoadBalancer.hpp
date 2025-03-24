#pragma once

#include <memory>
#include <string>
#include <vector>

#include <boost/asio.hpp>

#include "strategies/LoadBalancingStrategy.hpp"

class HttpLoadBalancer {
public:
    HttpLoadBalancer(short port, const std::vector<std::string>& servers, const std::string& strategy_type);
    void start();

private:
    void accept();
    void handleRequest(std::shared_ptr<boost::asio::ip::tcp::socket> client_socket);
    void relayTraffic(std::shared_ptr<boost::asio::ip::tcp::socket> client_socket, std::shared_ptr<boost::asio::ip::tcp::socket> server_socket);

    boost::asio::io_context io_ctx;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unique_ptr<LoadBalancingStrategy> strategy;
    std::vector<std::string> backend_servers;
};
