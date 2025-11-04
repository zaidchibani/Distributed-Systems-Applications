#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "hello.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using org::baeldung::grpc::HelloRequest;
using org::baeldung::grpc::HelloResponse;
using org::baeldung::grpc::HelloService;

// Implementation of the HelloService
class HelloServiceImpl final : public HelloService::Service {
    Status hello(ServerContext* context, const HelloRequest* request,
                HelloResponse* response) override {
        
        std::string greeting;
        std::string fullName = request->firstname();
        if (!request->lastname().empty()) {
            fullName += " " + request->lastname();
        }
        
        // Generate greeting based on language
        switch (request->lang()) {
            case HelloRequest::FR:
                greeting = "Bonjour, " + fullName + "!";
                break;
            case HelloRequest::AR:
                greeting = "مرحبا، " + fullName + "!";
                break;
            case HelloRequest::EN:
            default:
                greeting = "Hello, " + fullName + "!";
                break;
        }
        
        response->set_greeting(greeting);
        
        std::cout << "Server received: " << request->firstname() << " " << request->lastname() 
                  << " (lang: " << request->lang() << ")" << std::endl;
        std::cout << "Server responding: " << greeting << std::endl;
        
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    HelloServiceImpl service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
