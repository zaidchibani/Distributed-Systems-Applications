#!/bin/bash
# Build script for Java gRPC HelloWorld

echo "Building Java gRPC HelloWorld..."
mvn clean compile package

if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful!"
    echo ""
    echo "To run the server:"
    echo "  ./run-server.sh"
    echo "  or: java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloServer"
    echo ""
    echo "To run the client:"
    echo "  ./run-client.sh <first_name> [last_name] [language] [--target <host:port>]"
    echo "  or: java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient <args>"
else
    echo ""
    echo "Build failed!"
    exit 1
fi
