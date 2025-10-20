import grpc
import sys

import hello_pb2
import hello_pb2_grpc


def parse_lang(arg: str) -> int:
    m = {
        "en": hello_pb2.HelloRequest.EN,
        "fr": hello_pb2.HelloRequest.FR,
        "ar": hello_pb2.HelloRequest.AR,
    }
    return m.get(arg.lower(), hello_pb2.HelloRequest.EN)


def run(first: str = "John", last: str = "Doe", lang: int = hello_pb2.HelloRequest.EN, target: str = "localhost:50051") -> None:
    with grpc.insecure_channel(target) as channel:
        stub = hello_pb2_grpc.HelloServiceStub(channel)
        req = hello_pb2.HelloRequest(firstName=first, lastName=last, lang=lang)
        resp = stub.hello(req)
        print(resp.greeting)


if __name__ == "__main__":
    # Usage patterns:
    # - client.py zaid en -> first=zaid, last="", lang=en
    # - client.py zaid chibani fr -> first=zaid, last=chibani, lang=fr
    # - client.py Alice Bob Carol ar -> first=Alice, last="Bob Carol", lang=ar
    if len(sys.argv) <= 1:
        run("John", "Doe", hello_pb2.HelloRequest.EN)
        raise SystemExit(0)

    args = sys.argv[1:]
    lang = hello_pb2.HelloRequest.EN
    if args and args[-1].lower() in {"en", "fr", "ar"}:
        lang = parse_lang(args[-1])
        args = args[:-1]

    if not args:
        first = "John"
        last = "Doe"
    elif len(args) == 1:
        first = args[0]
        last = ""
    else:
        first = args[0]
        last = " ".join(args[1:])
    run(first, last, lang)
