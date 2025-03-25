#include <iostream>

#include "strategies/RoundRobinStrategy.hpp"

RoundRobinStrategy::RoundRobinStrategy(const std::vector<std::string>& server_list) : servers(server_list), index(0) {}

std::string RoundRobinStrategy::getNextServer() {
    std::lock_guard<std::mutex> lock(mtx);

    if(servers.empty()) {
        std::cerr << "[RoundRobin] No servers available!" << std::endl;
        return "";
    }

    std::string selected = servers[index];
    index = (index + 1) % servers.size();

    std::cout << "[RoundRobin] Selected backend server: " << selected << std::endl;
    return selected;
}

void RoundRobinStrategy::updateHealth(const std::string& server, bool is_healthy) {
    std::lock_guard<std::mutex> lock(mtx);

    if(!is_healthy) {
        auto it = std::remove(servers.begin(), servers.end(), server);

        if(it != servers.end()) {
            servers.erase(it, servers.end());

            if(index >= servers.size())
                index = 0;

            std::cout << "[RoundRobin] Removed unhealthy server: " << server << std::endl;
        }
        else
            std::cout << "[RoundRobin] Server " << server << " not found for removal." << std::endl;
    }
    else
        std::cout << "[RoundRobin] Health update for server " << server << ": healthy" << std::endl;
}
