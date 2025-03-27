#pragma once

#include <memory>
#include <string>
#include <vector>

#include "strategy/IStrategy.hpp"

namespace ZetaFlow {
namespace Strategy {

enum class StrategyType {
    ROUND_ROBIN,
    LEAST_CONNECTIONS,
    CONSISTENT_HASHING,
    RANDOM_SELECTION
};

class StrategyFactory {
public:
    static std::unique_ptr<IStrategy> createStrategy(StrategyType type, const std::vector<std::string>& servers);
};

}
}
