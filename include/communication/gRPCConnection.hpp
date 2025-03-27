#pragma once

#include <string>

#include <grpcpp/grpcpp.h>

#include "IConnection.hpp"
#include "service.grpc.pb.h"

namespace ZetaFlow {
namespace Communication {

class gRPCConnection : public IConnection {
public:
    gRPCConnection(const std::string &server_address);
    void send(const std::string &data) override;
    std::string receive() override;

private:
    std::unique_ptr<service::Service::Stub> stub_;
};

}
}
