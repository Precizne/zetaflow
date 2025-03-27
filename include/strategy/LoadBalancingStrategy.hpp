#pragma once

#include <string>

namespace ZetaFlow {
namespace Strategy {

class LoadBalancingStrategy {
public:
    virtual std::string getNextServer() = 0;
    virtual void updateHealth(const std::string& server, bool is_healthy) = 0;
    virtual ~LoadBalancingStrategy() = default;
};

}
}
