#include "LoadBalancerFactory.hpp"
#include "strategies/RoundRobinStrategy.hpp"
#include "strategies/LeastConnectionsStrategy.hpp"
#include "strategies/ConsistentHashingStrategy.hpp"
#include "strategies/RandomSelectionStrategy.hpp"

std::unique_ptr<LoadBalancingStrategy> LoadBalancerFactory::createStrategy(const std::string& type, const std::vector<std::string>& servers) {
    if(type == "round_robin")
        return std::make_unique<RoundRobinStrategy>(servers);
    else if(type == "least_connections")
        return std::make_unique<LeastConnectionsStrategy>(servers);
    else if(type == "consistent_hashing")
        return std::make_unique<ConsistentHashingStrategy>(servers);
    else if(type == "random_selection")
        return std::make_unique<RandomSelectionStrategy>(servers);
    throw std::invalid_argument("Unsupported strategy type");
}
