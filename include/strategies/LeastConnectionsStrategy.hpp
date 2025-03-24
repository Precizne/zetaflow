#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>

#include "LoadBalancingStrategy.hpp"

class LeastConnectionsStrategy : public LoadBalancingStrategy {
public:
    LeastConnectionsStrategy(const std::vector<std::string>& servers);
    std::string getNextServer() override;
    void updateHealth(const std::string& server, bool is_healthy) override;

private:
    std::unordered_map<std::string, int> server_connections;
    std::mutex mtx;
};
