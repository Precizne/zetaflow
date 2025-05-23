#include "connection/GRPCConnection.hpp"

namespace ZetaFlow {
namespace Connection {

GRPCConnection::GRPCConnection(const std::string& host, short port) {
    server_address = std::format("{}:{}", host, port);
    stub_ = ZetaFlowService::NewStub(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

    std::cout << "[GRPCConnection] Created stub for server at " << server_address << std::endl;
}

std::string GRPCConnection::sendRequest(const std::string& client_id) {
    Request request;
    request.set_client_id(client_id);

    Response response;

    grpc::ClientContext context;
    grpc::Status status = stub_->GetServer(&context, request, &response);

    if(!status.ok()) {
        std::cerr << "[GRPCConnection] RPC failed: " << status.error_message() << std::endl;
        return "";
    }

    return response.server_address();
}

void GRPCConnection::send(const std::string& client_id) {
    auto response = sendRequest(client_id);

    if(response.empty())
        std::cerr << "[GRPCConnection] No response received (RPC failure)." << std::endl;
    else
        std::cout << "[GRPCConnection] Received server address: " << response << std::endl;
}

std::string GRPCConnection::receive() {
    return "";
}

bool GRPCConnection::isConnected() {
    Request request;
    request.set_client_id("");

    Response response;

    grpc::ClientContext context;
    grpc::Status status = stub_->GetServer(&context, request, &response);

    if(!status.ok()) {
        std::cerr << "[GRPCConnection] Health check failed: " << status.error_message() << std::endl;
    }

    return status.ok();
}

}
}
