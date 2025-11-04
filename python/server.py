import grpc
from concurrent import futures
from typing import Iterator

import hello_pb2
import hello_pb2_grpc


class HelloServiceServicer(hello_pb2_grpc.HelloServiceServicer):
    def hello(self, request: hello_pb2.HelloRequest, context: grpc.ServicerContext) -> hello_pb2.HelloResponse:
        # Build the greeting, handling optional last name gracefully
        full_name = f"{request.firstName} {request.lastName}".strip()
        # Select language
        if request.lang == hello_pb2.HelloRequest.EN:
            greeting = f"hello {full_name}".strip()
        elif request.lang == hello_pb2.HelloRequest.FR:
            greeting = f"bonjour, {full_name}".strip()
        elif request.lang == hello_pb2.HelloRequest.AR:
            greeting = f"مرحبا، {full_name}".strip()
        else:
            greeting = f"hello {full_name}".strip()
        return hello_pb2.HelloResponse(greeting=greeting)

    def helloStream(self, request: hello_pb2.HelloRequest, context: grpc.ServicerContext) -> Iterator[hello_pb2.HelloResponse]:
        full_name = f"{request.firstName} {request.lastName}".strip()
        # Provide 3 variants in the selected language
        variants = []
        if request.lang == hello_pb2.HelloRequest.EN:
            variants = [
                f"hello {full_name}",
                f"hi {full_name}",
                f"greetings {full_name}",
            ]
        elif request.lang == hello_pb2.HelloRequest.FR:
            variants = [
                f"bonjour, {full_name}",
                f"salut, {full_name}",
                f"bienvenue, {full_name}",
            ]
        elif request.lang == hello_pb2.HelloRequest.AR:
            variants = [
                f"مرحبا، {full_name}",
                f"أهلاً، {full_name}",
                f"تحياتي، {full_name}",
            ]
        else:
            variants = [f"Hello, {full_name}!"]
        for g in variants:
            yield hello_pb2.HelloResponse(greeting=g)


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
