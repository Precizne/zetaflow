#pragma once

#include <string>

namespace ZetaFlow {
namespace Communication {

class IConnection {
public:
    virtual ~IConnection() = default;
    virtual void send(const std::string &data) = 0;
    virtual std::string receive() = 0;
};

}
}
