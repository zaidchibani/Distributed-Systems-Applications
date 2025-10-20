#include <iostream>
#include <memory>
#include <vector>
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
    std::string SayHello(const std::string& firstName, const std::string& lastName, HelloRequest::Language lang) {
        // Data we are sending to the server.
        HelloRequest request;
        request.set_firstname(firstName);
        request.set_lastname(lastName);
        request.set_lang(lang);

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

    void SayHelloStream(const std::string& firstName, const std::string& lastName, HelloRequest::Language lang) {
        HelloRequest request;
        request.set_firstname(firstName);
        request.set_lastname(lastName);
        request.set_lang(lang);

        ClientContext context;
        std::unique_ptr< grpc::ClientReader<HelloResponse> > reader(stub_->helloStream(&context, request));
        HelloResponse r;
        while (reader->Read(&r)) {
            std::cout << " - " << r.greeting() << std::endl;
        }
        Status status = reader->Finish();
        if (!status.ok()) {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
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
    HelloRequest::Language lang = HelloRequest::EN;

    // Parse args where the last token can be a language code (en|fr|ar), and the rest are name tokens
    if (argc > 1) {
        std::vector<std::string> tokens;
        for (int i = 1; i < argc; ++i) tokens.emplace_back(argv[i]);

        auto is_lang = [](const std::string& s){
            return s == "en" || s == "EN" || s == "fr" || s == "FR" || s == "ar" || s == "AR";
        };
        if (!tokens.empty() && is_lang(tokens.back())) {
            std::string l = tokens.back();
            tokens.pop_back();
            if (l == "fr" || l == "FR") lang = HelloRequest::FR;
            else if (l == "ar" || l == "AR") lang = HelloRequest::AR;
            else lang = HelloRequest::EN;
        }

        if (!tokens.empty()) {
            firstName = tokens.front();
            if (tokens.size() > 1) {
                std::string rest;
                for (size_t i = 1; i < tokens.size(); ++i) {
                    if (i > 1) rest += " ";
                    rest += tokens[i];
                }
                lastName = rest;
            } else {
                lastName.clear();
            }
        }
    }
    
    std::string response = client.SayHello(firstName, lastName, lang);
    std::cout << response << std::endl;

    return 0;
}
