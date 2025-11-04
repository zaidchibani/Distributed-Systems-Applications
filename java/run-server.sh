#!/bin/bash
# Run script for Java gRPC HelloWorld Server

JAR_FILE="target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar"

if [ ! -f "$JAR_FILE" ]; then
    echo "Error: JAR file not found. Please build the project first:"
    echo "  ./build.sh"
    exit 1
fi

echo "Starting Java gRPC Server on port 50051..."
java -cp "$JAR_FILE" org.baeldung.grpc.HelloServer "$@"
