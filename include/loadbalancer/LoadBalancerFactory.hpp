#pragma once

#include <memory>
#include <string>
#include <vector>

#include "strategy/LoadBalancingStrategy.hpp"

namespace ZetaFlow {
namespace LoadBalancer {

class LoadBalancerFactory {
public:
    static std::unique_ptr<Strategy::LoadBalancingStrategy> createStrategy(const std::string& type, const std::vector<std::string>& servers);
};

}
}
