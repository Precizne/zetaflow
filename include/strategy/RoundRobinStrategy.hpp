#pragma once

#include <vector>
#include <string>
#include <mutex>

#include "strategy/LoadBalancingStrategy.hpp"

namespace ZetaFlow {
namespace Strategy {

class RoundRobinStrategy : public LoadBalancingStrategy {
public:
    RoundRobinStrategy(const std::vector<std::string>& server_list);
    std::string getNextServer() override;
    void updateHealth(const std::string& server, bool is_healthy) override;

private:
    std::vector<std::string> servers;
    size_t index;
    std::mutex mtx;
};

}
}
