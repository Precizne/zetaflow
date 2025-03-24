#include <iostream>

#include "HttpLoadBalancer.hpp"
#include "LoadBalancerFactory.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

HttpLoadBalancer::HttpLoadBalancer(short port, const std::vector<std::string>& servers, const std::string& strategy_type) : acceptor(io_ctx, tcp::endpoint(tcp::v4(), port)), backend_servers(servers) {
    strategy = LoadBalancerFactory::createStrategy(strategy_type, servers);

    std::cout << "[HttpLoadBalancer] Initialized with strategy: " << strategy_type << std::endl;
}

void HttpLoadBalancer::start() {
    std::cout << "[HttpLoadBalancer] Starting load balancer on port " << acceptor.local_endpoint().port() << "..." << std::endl;

    accept();
    io_ctx.run();
}

void HttpLoadBalancer::accept() {
    auto socket = std::make_shared<tcp::socket>(io_ctx);

    acceptor.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if(!ec) {
            std::cout << "[HttpLoadBalancer] Accepted new connection from " << socket->remote_endpoint() << std::endl;
            handleRequest(socket);
        }
        else
            std::cerr << "[HttpLoadBalancer] Accept error: " << ec.message() << std::endl;
        accept();
    });
}

void HttpLoadBalancer::handleRequest(std::shared_ptr<tcp::socket> client_socket) {
    auto server_ip = strategy->getNextServer();

    if(server_ip.empty()) {
        std::cerr << "[HttpLoadBalancer] No available backend server!" << std::endl;
        return;
    }
    std::cout << "[HttpLoadBalancer] Forwarding client " << client_socket->remote_endpoint() << " to backend server " << server_ip << std::endl;

    auto server_socket = std::make_shared<tcp::socket>(io_ctx); 
    tcp::resolver resolver(io_ctx);
    auto endpoints = resolver.resolve(server_ip, "80");

    async_connect(*server_socket, endpoints, [this, client_socket, server_socket, server_ip](boost::system::error_code ec, tcp::endpoint) {
        if(!ec) {
            std::cout << "[HttpLoadBalancer] Connected to backend server " << server_ip << std::endl;
            relayTraffic(client_socket, server_socket);
        }
        else {
            std::cerr << "[HttpLoadBalancer] Failed to connect to backend server " << server_ip << " Error: " << ec.message() << std::endl;
            strategy->updateHealth(server_ip, false);
        }
    });
}

void HttpLoadBalancer::relayTraffic(std::shared_ptr<tcp::socket> client_socket, std::shared_ptr<tcp::socket> server_socket) {
    std::cout << "[relayTraffic] Starting relay between client " << client_socket->remote_endpoint() << " and backend " << server_socket->remote_endpoint() << std::endl;

    auto client_buffer = std::make_shared<std::vector<char>>(8192);
    auto server_buffer = std::make_shared<std::vector<char>>(8192);
    auto forward = std::make_shared<std::function<void(std::shared_ptr<tcp::socket>, std::shared_ptr<tcp::socket>, std::shared_ptr<std::vector<char>>)>>();

    *forward = [forward](std::shared_ptr<tcp::socket> src, std::shared_ptr<tcp::socket> dst, std::shared_ptr<std::vector<char>> buffer) {
        src->async_read_some(boost::asio::buffer(*buffer), [src, dst, buffer, forward](boost::system::error_code ec, std::size_t length) {
            if(!ec) {
                async_write(*dst, boost::asio::buffer(*buffer, length), [src, dst, buffer, forward](boost::system::error_code ec2, std::size_t) {
                    if(!ec2)
                        (*forward)(src, dst, buffer);
                    else {
                        std::cerr << "[relayTraffic] Write error: " << ec2.message() << std::endl;
                        src->close();
                        dst->close();
                    }
                });
            }
            else {
                std::cerr << "[relayTraffic] Read error: " << ec.message() << std::endl;
                src->close();
                dst->close();
            }
        });
    };

    (*forward)(client_socket, server_socket, client_buffer);
    (*forward)(server_socket, client_socket, server_buffer);
}
