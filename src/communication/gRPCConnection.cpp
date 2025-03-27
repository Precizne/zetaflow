#include "communication/gRPCConnection.hpp"

namespace ZetaFlow {
namespace Communication {

gRPCConnection::gRPCConnection(const std::string &server_address) {
    stub_ = service::Service::NewStub(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
}

void gRPCConnection::send(const std::string &data) {
    service::ServerRequest request;
    request.set_query(data);
    
    service::ServerResponse response;
    grpc::ClientContext context;
    
    grpc::Status status = stub_->GetServerInfo(&context, request, &response);

    if(!status.ok())
        std::cerr << "[gRPCConnection] RPC failed: " << status.error_message() << std::endl;
    else
        std::cout << "[gRPCConnection] Received: " << response.info() << std::endl;
}

std::string gRPCConnection::receive() {
    return "";
}

}
}
