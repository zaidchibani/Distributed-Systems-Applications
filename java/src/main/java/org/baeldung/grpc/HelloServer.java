package org.baeldung.grpc;

import io.grpc.Server;
import io.grpc.ServerBuilder;
import io.grpc.stub.StreamObserver;
import java.io.IOException;
import java.util.logging.Logger;

public class HelloServer {
    private static final Logger logger = Logger.getLogger(HelloServer.class.getName());
    private Server server;

    private void start() throws IOException {
        int port = Integer.parseInt(System.getProperty("grpc.port", "50051"));
        server = ServerBuilder.forPort(port)
                .addService(new HelloServiceImpl())
                .build()
                .start();
        logger.info("Server started, listening on " + port);
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.err.println("*** shutting down gRPC server since JVM is shutting down");
            try {
                HelloServer.this.stop();
            } catch (InterruptedException e) {
                e.printStackTrace(System.err);
            }
            System.err.println("*** server shut down");
        }));
    }

    private void stop() throws InterruptedException {
        if (server != null) {
            server.shutdown().awaitTermination();
        }
    }

    private void blockUntilShutdown() throws InterruptedException {
        if (server != null) {
            server.awaitTermination();
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        final HelloServer server = new HelloServer();
        server.start();
        server.blockUntilShutdown();
    }

    static class HelloServiceImpl extends HelloServiceGrpc.HelloServiceImplBase {

        @Override
        public void hello(HelloRequest req, StreamObserver<HelloResponse> responseObserver) {
            String greeting = getGreeting(req.getFirstName(), req.getLastName(), req.getLang());
            HelloResponse reply = HelloResponse.newBuilder()
                    .setGreeting(greeting)
                    .build();
            responseObserver.onNext(reply);
            responseObserver.onCompleted();
        }

        @Override
        public void helloStream(HelloRequest req, StreamObserver<HelloResponse> responseObserver) {
            for (int i = 0; i < 3; i++) {
                String greeting = getGreeting(req.getFirstName(), req.getLastName(), req.getLang()) + " (" + (i + 1) + ")";
                HelloResponse reply = HelloResponse.newBuilder()
                        .setGreeting(greeting)
                        .build();
                responseObserver.onNext(reply);
            }
            responseObserver.onCompleted();
        }

        private String getGreeting(String firstName, String lastName, HelloRequest.Language lang) {
            switch (lang) {
                case FR:
                    return "Bonjour " + firstName + " " + lastName;
                case AR:
                    return "مرحبا " + firstName + " " + lastName;
                case EN:
                default:
                    return "Hello " + firstName + " " + lastName;
            }
        }
    }
}
