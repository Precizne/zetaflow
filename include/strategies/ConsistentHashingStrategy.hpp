#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "LoadBalancingStrategy.hpp"

class ConsistentHashingStrategy : public LoadBalancingStrategy {
public:
    ConsistentHashingStrategy(const std::vector<std::string>& servers);
    std::string getNextServer() override;
    void updateHealth(const std::string& server, bool is_healthy) override;

private:
    std::map<size_t, std::string> hash_ring;
    std::hash<std::string> hasher;
    std::mutex mtx;
};
