#!/bin/bash
# Run script for Java gRPC HelloWorld Client

JAR_FILE="target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar"

if [ ! -f "$JAR_FILE" ]; then
    echo "Error: JAR file not found. Please build the project first:"
    echo "  ./build.sh"
    exit 1
fi

if [ $# -eq 0 ]; then
    echo "Usage: ./run-client.sh <first_name> [last_name] [language] [--target <host:port>]"
    echo ""
    echo "Examples:"
    echo "  ./run-client.sh zaid chibani fr"
    echo "  ./run-client.sh zaid chibani fr --target 192.168.1.100:50051"
    echo "  ./run-client.sh alice en"
    exit 1
fi

java -cp "$JAR_FILE" org.baeldung.grpc.HelloClient "$@"
