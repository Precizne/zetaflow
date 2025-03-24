#include <iostream>

#include "strategies/RandomSelectionStrategy.hpp"

RandomSelectionStrategy::RandomSelectionStrategy(const std::vector<std::string>& server_list) : servers(server_list), gen(rd()) {}

std::string RandomSelectionStrategy::getNextServer() {
    std::lock_guard<std::mutex> lock(mtx);
    if(servers.empty())
        return "";

    std::uniform_int_distribution<> distrib(0, servers.size() - 1);
    std::string selected = servers[distrib(gen)];

    std::cout << "[RandomSelection] Selected backend server: " << selected << std::endl;
    return selected;
}

void RandomSelectionStrategy::updateHealth(const std::string& server, bool is_healthy) {
    std::cout << "[RandomSelection] Health update for server " << server << ": " << (is_healthy ? "healthy" : "unhealthy") << std::endl;
}
