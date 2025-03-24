#include <iostream>

#include "strategies/RoundRobinStrategy.hpp"

RoundRobinStrategy::RoundRobinStrategy(const std::vector<std::string>& server_list) : servers(server_list), index(0) {}

std::string RoundRobinStrategy::getNextServer() {
    std::lock_guard<std::mutex> lock(mtx);
    if(servers.empty())
        return "";

    std::string selected = servers[index];
    index = (index + 1) % servers.size();

    std::cout << "[RoundRobin] Selected backend server: " << selected << std::endl;
    return selected;
}

void RoundRobinStrategy::updateHealth(const std::string& server, bool is_healthy) {
    std::cout << "[RoundRobin] Health update for server " << server << ": " << (is_healthy ? "healthy" : "unhealthy") << std::endl;
}
