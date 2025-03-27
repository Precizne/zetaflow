#pragma once

#include <string>

namespace ZetaFlow {
namespace Connection {

class IConnection {
public:
    virtual void send(const std::string& data) = 0;
    virtual std::string receive() = 0;
    virtual ~IConnection() = default;
};

}
}
