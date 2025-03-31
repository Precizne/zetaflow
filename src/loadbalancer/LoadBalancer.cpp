#include <iostream>

#include "loadbalancer/LoadBalancer.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace ZetaFlow {
namespace LoadBalancer {

LoadBalancer::LoadBalancer(short port, const std::vector<std::string>& servers, Strategy::StrategyType strategy_type, Connection::ConnectionType connection_type, short backend_port) : acceptor(io_ctx, tcp::endpoint(tcp::v4(), port)), backend_servers(servers), connection_type(connection_type), backend_port(backend_port) {
    strategy = Strategy::StrategyFactory::createStrategy(strategy_type, servers);

    std::cout << "[LoadBalancer] Initialized strategy" << std::endl;
}

void LoadBalancer::start() {
    std::cout << "[LoadBalancer] Starting load balancer on port " << acceptor.local_endpoint().port() << "..." << std::endl;

    accept();
    io_ctx.run();
}

void LoadBalancer::accept() {
    auto socket = std::make_shared<tcp::socket>(io_ctx);

    acceptor.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if(!ec) {
            std::cout << "[LoadBalancer] Accepted new connection from " << socket->remote_endpoint() << std::endl;

            handleRequest(socket);
        }
        else
            std::cerr << "[LoadBalancer] Accept error: " << ec.message() << std::endl;
        accept();
    });
}

void LoadBalancer::handleRequest(std::shared_ptr<tcp::socket> client_socket) {
    std::string backend_server = strategy->getNextServer();

    if(backend_server.empty()) {
        std::cerr << "[LoadBalancer] No available backend server!" << std::endl;

        return;
    }

    std::cout << "[LoadBalancer] Forwarding client " << client_socket->remote_endpoint() << " to backend server " << backend_server << std::endl;

    auto connection = Connection::ConnectionFactory::createConnection(connection_type, backend_server, backend_port);
    if(!connection->isConnected()) {
        strategy->updateHealth(backend_server, false);
        return;
    }

    auto client_buffer = std::make_shared<std::vector<char>>(1024);

    client_socket->async_read_some(boost::asio::buffer(*client_buffer), [client_socket, client_buffer, connection = std::move(connection)](boost::system::error_code ec, std::size_t length) mutable {
            if(ec) {
                std::cerr << "[LoadBalancer] Error reading from client: " << ec.message() << std::endl;

                return;
            }

            std::string client_request(client_buffer->data(), length);

            std::cout << "[LoadBalancer] Received request from client: " << client_request << std::endl;
            
            std::thread([client_socket, client_request, connection = std::move(connection)]() mutable {
                connection->send(client_request);
                std::string backend_response = connection->receive();

                std::cout << "[LoadBalancer] Received response from backend: " << backend_response << std::endl;

                boost::asio::async_write(*client_socket, boost::asio::buffer(backend_response), [client_socket, backend_response](boost::system::error_code write_ec, std::size_t length) {
                    if(write_ec)
                        std::cerr << "[LoadBalancer] Error writing to client: " << write_ec.message() << std::endl;
                    else
                        std::cout << "[LoadBalancer] Successfully wrote " << length << " bytes to client." << std::endl;

                    client_socket->close();
                });
            }).detach();
        });
}

}
}
