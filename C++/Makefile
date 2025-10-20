CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++14
LDFLAGS += `pkg-config --libs protobuf grpc++`\
           -pthread\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl

PROTOC = /usr/bin/protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= /usr/bin/$(GRPC_CPP_PLUGIN)

# Proto file resides one level up from this C++ directory
PROTOS_PATH = ..

vpath %.proto $(PROTOS_PATH)

all: hello_server hello_client

hello_server: hello.pb.o hello.grpc.pb.o hello_server.o
	$(CXX) $^ $(LDFLAGS) -o $@

hello_client: hello.pb.o hello.grpc.pb.o hello_client.o
	$(CXX) $^ $(LDFLAGS) -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

clean:
	rm -f *.o *.pb.cc *.pb.h hello_server hello_client

.PHONY: all clean
