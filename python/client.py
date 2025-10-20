import grpc
import sys

import hello_pb2
import hello_pb2_grpc


def run(first: str = "John", last: str = "Doe", target: str = "localhost:50051") -> None:
    with grpc.insecure_channel(target) as channel:
        stub = hello_pb2_grpc.HelloServiceStub(channel)
        resp = stub.hello(hello_pb2.HelloRequest(firstName=first, lastName=last))
        print(resp.greeting)


if __name__ == "__main__":
    first = sys.argv[1] if len(sys.argv) > 1 else "John"
    last = sys.argv[2] if len(sys.argv) > 2 else "Doe"
    run(first, last)
