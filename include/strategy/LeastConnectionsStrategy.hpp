#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>

#include "strategy/IStrategy.hpp"

namespace ZetaFlow {
namespace Strategy {

class LeastConnectionsStrategy : public IStrategy {
public:
    LeastConnectionsStrategy(const std::vector<std::string>& servers);
    std::string getNextServer() override;
    void updateHealth(const std::string& server, bool is_healthy) override;

private:
    std::unordered_map<std::string, int> server_connections;
    std::mutex mtx;
};

}
}
