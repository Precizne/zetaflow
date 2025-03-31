#include "strategy/StrategyFactory.hpp"
#include "strategy/RoundRobinStrategy.hpp"
#include "strategy/LeastConnectionsStrategy.hpp"
#include "strategy/ConsistentHashingStrategy.hpp"
#include "strategy/RandomSelectionStrategy.hpp"

namespace ZetaFlow {
namespace Strategy {

std::unique_ptr<IStrategy> StrategyFactory::createStrategy(StrategyType type, const std::vector<std::string>& servers) {
    switch(type) {
        case StrategyType::ROUND_ROBIN:
            return std::make_unique<RoundRobinStrategy>(servers);
        case StrategyType::LEAST_CONNECTIONS:
            return std::make_unique<LeastConnectionsStrategy>(servers);
        case StrategyType::CONSISTENT_HASHING:
            return std::make_unique<ConsistentHashingStrategy>(servers);
        case StrategyType::RANDOM_SELECTION:
            return std::make_unique<RandomSelectionStrategy>(servers);
        default:
            throw std::invalid_argument("[StrategyFactory] Unsupported strategy type");
    }
}

}
}
