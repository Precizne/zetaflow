#pragma once

#include <string>

#include <grpcpp/grpcpp.h>

#include "connection/IConnection.hpp"
#include "service.grpc.pb.h"

namespace ZetaFlow {
namespace Connection {

class GRPCConnection : public IConnection {
public:
    GRPCConnection(const std::string& host, short port);
    void send(const std::string& data) override;
    std::string receive() override;

private:
    std::unique_ptr<service::Service::Stub> stub_;
    std::string sendRequest(const std::string& query);
};

}
}
