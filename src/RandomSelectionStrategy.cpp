#include <iostream>

#include "strategies/RandomSelectionStrategy.hpp"

RandomSelectionStrategy::RandomSelectionStrategy(const std::vector<std::string>& server_list) : servers(server_list), gen(rd()) {}

std::string RandomSelectionStrategy::getNextServer() {
    std::lock_guard<std::mutex> lock(mtx);

    if(servers.empty()) {
        std::cerr << "[RandomSelection] No servers available!" << std::endl;
        return "";
    }

    std::uniform_int_distribution<> distrib(0, servers.size() - 1);
    std::string selected = servers[distrib(gen)];

    std::cout << "[RandomSelection] Selected backend server: " << selected << std::endl;
    return selected;
}

void RandomSelectionStrategy::updateHealth(const std::string& server, bool is_healthy) {
    std::lock_guard<std::mutex> lock(mtx);

    if(!is_healthy) {
        auto it = std::remove(servers.begin(), servers.end(), server);
        if(it != servers.end()) {
            servers.erase(it, servers.end());

            std::cout << "[RandomSelection] Removed unhealthy server: " << server << std::endl;
        }
        else
            std::cout << "[RandomSelection] Server " << server << " not found for removal." << std::endl;
    }
    else
        std::cout << "[RandomSelection] Health update for server " << server << ": healthy" << std::endl;
}
