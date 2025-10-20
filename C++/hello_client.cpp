#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "hello.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using org::baeldung::grpc::HelloRequest;
using org::baeldung::grpc::HelloResponse;
using org::baeldung::grpc::HelloService;

class HelloClient {
public:
    HelloClient(std::shared_ptr<Channel> channel)
        : stub_(HelloService::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string SayHello(const std::string& firstName, const std::string& lastName) {
        // Data we are sending to the server.
        HelloRequest request;
        request.set_firstname(firstName);
        request.set_lastname(lastName);

        // Container for the data we expect from the server.
        HelloResponse response;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        Status status = stub_->hello(&context, request, &response);

        // Act upon its status.
        if (status.ok()) {
            return response.greeting();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<HelloService::Stub> stub_;
};

int main(int argc, char** argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    std::string server_address("localhost:50051");
    HelloClient client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
    
    std::string firstName = "John";
    std::string lastName = "Doe";
    
    if (argc >= 3) {
        firstName = argv[1];
        lastName = argv[2];
    }
    
    std::string response = client.SayHello(firstName, lastName);
    std::cout << "Client received: " << response << std::endl;

    return 0;
}
