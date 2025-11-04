package org.baeldung.grpc;

import io.grpc.Channel;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import io.grpc.StatusRuntimeException;
import java.util.Iterator;
import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;

public class HelloClient {
    private static final Logger logger = Logger.getLogger(HelloClient.class.getName());
    private final ManagedChannel channel;
    private final HelloServiceGrpc.HelloServiceBlockingStub blockingStub;

    public HelloClient(String host, int port) {
        this(ManagedChannelBuilder.forAddress(host, port)
                .usePlaintext()
                .build());
    }

    HelloClient(ManagedChannel channel) {
        this.channel = channel;
        blockingStub = HelloServiceGrpc.newBlockingStub(channel);
    }

    public void shutdown() throws InterruptedException {
        channel.shutdown().awaitTermination(5, TimeUnit.SECONDS);
    }

    public void greet(String firstName, String lastName, String language) {
        logger.info("Will try to greet " + firstName + " " + lastName + " in " + language);
        HelloRequest request = HelloRequest.newBuilder()
                .setFirstName(firstName)
                .setLastName(lastName)
                .setLang(parseLanguage(language))
                .build();
        HelloResponse response;
        try {
            response = blockingStub.hello(request);
        } catch (StatusRuntimeException e) {
            logger.log(Level.WARNING, "RPC failed: {0}", e.getStatus());
            return;
        }
        logger.info("Greeting: " + response.getGreeting());
    }

    public void greetStream(String firstName, String lastName, String language) {
        logger.info("Will try to greet stream " + firstName + " " + lastName + " in " + language);
        HelloRequest request = HelloRequest.newBuilder()
                .setFirstName(firstName)
                .setLastName(lastName)
                .setLang(parseLanguage(language))
                .build();
        try {
            Iterator<HelloResponse> responses = blockingStub.helloStream(request);
            while (responses.hasNext()) {
                HelloResponse response = responses.next();
                logger.info("Greeting stream: " + response.getGreeting());
            }
        } catch (StatusRuntimeException e) {
            logger.log(Level.WARNING, "RPC failed: {0}", e.getStatus());
        }
    }

    private HelloRequest.Language parseLanguage(String lang) {
        switch (lang.toLowerCase()) {
            case "fr":
            case "french":
                return HelloRequest.Language.FR;
            case "ar":
            case "arabic":
                return HelloRequest.Language.AR;
            case "en":
            case "english":
            default:
                return HelloRequest.Language.EN;
        }
    }

    public static void main(String[] args) throws Exception {
        if (args.length == 0) {
            printUsage();
            return;
        }

        String firstName = null;
        String lastName = null;
        String language = "en";
        String host = "localhost";
        int port = 50051;

        for (int i = 0; i < args.length; i++) {
            if ("--target".equals(args[i])) {
                if (i + 1 < args.length) {
                    String target = args[i + 1];
                    String[] parts = target.split(":");
                    host = parts[0];
                    if (parts.length > 1) {
                        port = Integer.parseInt(parts[1]);
                    }
                    i++;
                }
            } else if (firstName == null) {
                firstName = args[i];
            } else if (lastName == null) {
                lastName = args[i];
            } else if (language == null || "en".equals(language)) {
                language = args[i];
            }
        }

        if (firstName == null || lastName == null) {
            printUsage();
            return;
        }

        HelloClient client = new HelloClient(host, port);
        try {
            client.greet(firstName, lastName, language);
            client.greetStream(firstName, lastName, language);
        } finally {
            client.shutdown();
        }
    }

    private static void printUsage() {
        System.out.println("Usage: java HelloClient <first_name> <last_name> [language] [--target host:port]");
        System.out.println("  first_name: Your first name");
        System.out.println("  last_name: Your last name");
        System.out.println("  language: Greeting language (en, fr, ar) - default: en");
        System.out.println("  --target host:port: Remote server address - default: localhost:50051");
        System.out.println("\nExamples:");
        System.out.println("  java HelloClient zaid chibani");
        System.out.println("  java HelloClient zaid chibani fr");
        System.out.println("  java HelloClient zaid chibani ar --target 192.168.1.100:50051");
    }
}
