#pragma once

#include <memory>
#include <string>
#include <vector>

#include "strategies/LoadBalancingStrategy.hpp"

class LoadBalancerFactory {
public:
    static std::unique_ptr<LoadBalancingStrategy> createStrategy(const std::string& type, const std::vector<std::string>& servers);
};
