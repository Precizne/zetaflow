#include <string>
#include <vector>

#include "HttpLoadBalancer.hpp"

int main() {
    std::vector<std::string> servers = { "127.0.0.1", "192.168.1.2", "192.168.1.3" };

    HttpLoadBalancer lb(8080, servers, "round_robin");
    lb.start();

    return 0;
}
