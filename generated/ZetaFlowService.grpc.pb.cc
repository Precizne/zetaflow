// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: ZetaFlowService.proto

#include "ZetaFlowService.pb.h"
#include "ZetaFlowService.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace ZetaFlow {

static const char* ZetaFlowService_method_names[] = {
  "/ZetaFlow.ZetaFlowService/GetServer",
  "/ZetaFlow.ZetaFlowService/UpdateHealth",
};

std::unique_ptr< ZetaFlowService::Stub> ZetaFlowService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ZetaFlowService::Stub> stub(new ZetaFlowService::Stub(channel, options));
  return stub;
}

ZetaFlowService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_GetServer_(ZetaFlowService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_UpdateHealth_(ZetaFlowService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ZetaFlowService::Stub::GetServer(::grpc::ClientContext* context, const ::ZetaFlow::Request& request, ::ZetaFlow::Response* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ZetaFlow::Request, ::ZetaFlow::Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetServer_, context, request, response);
}

void ZetaFlowService::Stub::async::GetServer(::grpc::ClientContext* context, const ::ZetaFlow::Request* request, ::ZetaFlow::Response* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ZetaFlow::Request, ::ZetaFlow::Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetServer_, context, request, response, std::move(f));
}

void ZetaFlowService::Stub::async::GetServer(::grpc::ClientContext* context, const ::ZetaFlow::Request* request, ::ZetaFlow::Response* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetServer_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ZetaFlow::Response>* ZetaFlowService::Stub::PrepareAsyncGetServerRaw(::grpc::ClientContext* context, const ::ZetaFlow::Request& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ZetaFlow::Response, ::ZetaFlow::Request, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetServer_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ZetaFlow::Response>* ZetaFlowService::Stub::AsyncGetServerRaw(::grpc::ClientContext* context, const ::ZetaFlow::Request& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetServerRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ZetaFlowService::Stub::UpdateHealth(::grpc::ClientContext* context, const ::ZetaFlow::HealthUpdate& request, ::ZetaFlow::Ack* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ZetaFlow::HealthUpdate, ::ZetaFlow::Ack, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_UpdateHealth_, context, request, response);
}

void ZetaFlowService::Stub::async::UpdateHealth(::grpc::ClientContext* context, const ::ZetaFlow::HealthUpdate* request, ::ZetaFlow::Ack* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ZetaFlow::HealthUpdate, ::ZetaFlow::Ack, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UpdateHealth_, context, request, response, std::move(f));
}

void ZetaFlowService::Stub::async::UpdateHealth(::grpc::ClientContext* context, const ::ZetaFlow::HealthUpdate* request, ::ZetaFlow::Ack* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UpdateHealth_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ZetaFlow::Ack>* ZetaFlowService::Stub::PrepareAsyncUpdateHealthRaw(::grpc::ClientContext* context, const ::ZetaFlow::HealthUpdate& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ZetaFlow::Ack, ::ZetaFlow::HealthUpdate, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_UpdateHealth_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ZetaFlow::Ack>* ZetaFlowService::Stub::AsyncUpdateHealthRaw(::grpc::ClientContext* context, const ::ZetaFlow::HealthUpdate& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncUpdateHealthRaw(context, request, cq);
  result->StartCall();
  return result;
}

ZetaFlowService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ZetaFlowService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ZetaFlowService::Service, ::ZetaFlow::Request, ::ZetaFlow::Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ZetaFlowService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ZetaFlow::Request* req,
             ::ZetaFlow::Response* resp) {
               return service->GetServer(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ZetaFlowService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ZetaFlowService::Service, ::ZetaFlow::HealthUpdate, ::ZetaFlow::Ack, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ZetaFlowService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ZetaFlow::HealthUpdate* req,
             ::ZetaFlow::Ack* resp) {
               return service->UpdateHealth(ctx, req, resp);
             }, this)));
}

ZetaFlowService::Service::~Service() {
}

::grpc::Status ZetaFlowService::Service::GetServer(::grpc::ServerContext* context, const ::ZetaFlow::Request* request, ::ZetaFlow::Response* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ZetaFlowService::Service::UpdateHealth(::grpc::ServerContext* context, const ::ZetaFlow::HealthUpdate* request, ::ZetaFlow::Ack* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace ZetaFlow

