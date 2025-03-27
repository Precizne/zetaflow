#include "connection/GRPCConnection.hpp"

namespace ZetaFlow {
namespace Connection {

GRPCConnection::GRPCConnection(const std::string& server_address) {
    stub_ = service::Service::NewStub(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
    std::cout << "[gRPCConnection] Created stub for server at " << server_address << std::endl;
}

std::string GRPCConnection::sendRequest(const std::string& query) {
    service::ServerRequest request;
    request.set_query(query);

    service::ServerResponse response;
    grpc::ClientContext context;
    grpc::Status status = stub_->GetServerInfo(&context, request, &response);

    if(!status.ok()) {
        std::cerr << "[gRPCConnection] RPC failed: " << status.error_message() << std::endl;
        return "";
    }

    return response.info();
}

void GRPCConnection::send(const std::string& data) {
    auto response = sendRequest(data);

    if(!response.empty()) {
        std::cout << "[gRPCConnection] Received: " << response << std::endl;
    }
}

std::string GRPCConnection::receive() {
    return "";
}

}
}
