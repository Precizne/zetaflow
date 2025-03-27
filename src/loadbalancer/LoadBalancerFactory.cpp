#include "loadbalancer/LoadBalancerFactory.hpp"
#include "strategy/RoundRobinStrategy.hpp"
#include "strategy/LeastConnectionsStrategy.hpp"
#include "strategy/ConsistentHashingStrategy.hpp"
#include "strategy/RandomSelectionStrategy.hpp"

namespace ZetaFlow {
namespace LoadBalancer {

std::unique_ptr<Strategy::LoadBalancingStrategy> LoadBalancerFactory::createStrategy(const std::string& type, const std::vector<std::string>& servers) {
    if(type == "round_robin")
        return std::make_unique<Strategy::RoundRobinStrategy>(servers);
    else if(type == "least_connections")
        return std::make_unique<Strategy::LeastConnectionsStrategy>(servers);
    else if(type == "consistent_hashing")
        return std::make_unique<Strategy::ConsistentHashingStrategy>(servers);
    else if(type == "random_selection")
        return std::make_unique<Strategy::RandomSelectionStrategy>(servers);
    throw std::invalid_argument("Unsupported strategy type");
}

}
}
