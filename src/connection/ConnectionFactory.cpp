#include "connection/ConnectionFactory.hpp"
#include "connection/HTTPConnection.hpp"
#include "connection/GRPCConnection.hpp"

namespace ZetaFlow {
namespace Connection {

std::unique_ptr<IConnection> ConnectionFactory::createConnection(ConnectionType type, const std::string& address, short port) {
    switch(type) {
        case ConnectionType::HTTP:
            return std::make_unique<HTTPConnection>(address, port);
        case ConnectionType::GRPC:
            return std::make_unique<GRPCConnection>(address, port);
        default:
            throw std::invalid_argument("[ConnectionFactory] Unsupported connection type");
    }
}

}
}
