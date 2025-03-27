#pragma once

#include <memory>
#include <string>

#include "connection/IConnection.hpp"

namespace ZetaFlow {
namespace Connection {

enum class ConnectionType {
    HTTP,
    GRPC
};

class ConnectionFactory {
public:
    static std::unique_ptr<IConnection> createConnection(ConnectionType type, const std::string& address, short port);
};

}
}
