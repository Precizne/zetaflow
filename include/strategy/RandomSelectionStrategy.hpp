#pragma once

#include <mutex>
#include <random>
#include <string>
#include <vector>

#include "strategy/IStrategy.hpp"

namespace ZetaFlow {
namespace Strategy {

class RandomSelectionStrategy : public IStrategy {
public:
    RandomSelectionStrategy(const std::vector<std::string>& server_list);
    std::string getNextServer() override;
    void updateHealth(const std::string& server, bool is_healthy) override;

private:
    std::vector<std::string> servers;
    std::mutex mtx;
    std::random_device rd;
    std::mt19937 gen;
};

}
}
