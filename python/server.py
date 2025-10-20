import grpc
from concurrent import futures
from typing import Iterator

import hello_pb2
import hello_pb2_grpc


class HelloServiceServicer(hello_pb2_grpc.HelloServiceServicer):
    def hello(self, request: hello_pb2.HelloRequest, context: grpc.ServicerContext) -> hello_pb2.HelloResponse:
        greeting = f"Hello, {request.firstName} {request.lastName}!"
        return hello_pb2.HelloResponse(greeting=greeting)


def serve(host: str = "0.0.0.0", port: int = 50051) -> None:
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    hello_pb2_grpc.add_HelloServiceServicer_to_server(HelloServiceServicer(), server)
    server.add_insecure_port(f"{host}:{port}")
    server.start()
    print(f"gRPC server started on {host}:{port}")
    try:
        server.wait_for_termination()
    except KeyboardInterrupt:
        print("Shutting down server...")
        server.stop(grace=None)


if __name__ == "__main__":
    serve()
