# Java gRPC HelloWorld Implementation

A cross-language gRPC client and server with multi-language support (English, French, Arabic).

## 📋 Overview

- **Framework**: gRPC 1.58.0
- **Protocol Buffers**: 3.24.0
- **Build System**: Maven 3.6+
- **Java Version**: 11+
- **Package**: `org.baeldung.grpc`
- **Port**: 50051 (TCP)

## 🔧 Prerequisites

- **Java 11+**: OpenJDK or Oracle JDK
- **Maven 3.6+**: Build and dependency management
- **protoc 23.x+**: Already included in dependencies

### Installation

**Ubuntu/Debian:**
```bash
sudo apt-get install -y openjdk-11-jdk maven
```

**macOS:**
```bash
brew install java@11 maven
```

## 📦 Building

### Quick Build

```bash
cd java
./build.sh
```

### Full Build with Dependencies

```bash
mvn clean compile package -DskipTests
```

**Build Output:**
```
target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar  # Ready to run
```

## 🚀 Running the Server

### Start Server

```bash
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloServer
```

**Expected Output:**
```
Oct 21, 2025 10:42:25 AM org.baeldung.grpc.HelloServer start
INFO: Server started, listening on 50051
```

### Verify Server

```bash
# Check if port 50051 is listening
ss -ltnp | grep 50051
netstat -ltnp | grep 50051
```

## 👥 Running Clients

### Basic Usage

```bash
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient <first_name> <last_name> [language] [--target host:port]
```

### Usage Examples

**English greeting (localhost, default):**
```bash
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient john doe
```

**French greeting:**
```bash
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient marie dupont fr
```

**Arabic greeting:**
```bash
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient ali hassan ar
```

**Connect to remote server:**
```bash
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient zaid chibani fr --target 192.168.1.100:50051
```

## 🌐 Language Support

| Code | Language   | Example Output       |
|------|------------|----------------------|
| `en` | English    | Hello zaid chibani   |
| `fr` | French     | Bonjour zaid chibani |
| `ar` | Arabic     | مرحبا zaid chibani   |

## 📁 Project Structure

```
java/
├── pom.xml                        # Maven project configuration
├── build.sh                       # Build script
├── run-server.sh                  # Server launcher script
├── run-client.sh                  # Client launcher script
├── README.md                      # This file
├── src/
│   └── main/
│       └── java/
│           └── org/
│               └── baeldung/
│                   └── grpc/
│                       ├── HelloServer.java           # Server implementation
│                       ├── HelloClient.java           # Client implementation
│                       ├── Hello.java                 # Generated protobuf
│                       ├── HelloRequest.java          # Generated message
│                       ├── HelloResponse.java         # Generated message
│                       └── HelloServiceGrpc.java      # Generated stubs
└── target/                        # Build output (generated)
    └── grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar
```

## 🔄 Cross-Language Testing

### Java Server with Python Client

**Terminal 1:**
```bash
cd java
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloServer
```

**Terminal 2:**
```bash
cd python
python3 client.py zaid chibani fr
```

### Java Client with Python Server

**Terminal 1:**
```bash
cd python
python3 server.py
```

**Terminal 2:**
```bash
cd java
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient zaid chibani fr
```

## 🛠️ Troubleshooting

### Build Errors

**"Cannot find symbol" errors:**
```bash
mvn clean compile package -DskipTests
```

**Port already in use:**
```bash
pkill -f HelloServer
# or
lsof -ti:50051 | xargs kill -9
```

### Runtime Issues

**Server fails to start:**
- Verify port 50051 is not in use
- Check Java version: `java -version` (should be 11+)
- Ensure build completed successfully

**Client connection refused:**
- Verify server is running: `netstat -ltnp | grep 50051`
- Check firewall: `sudo ufw status`
- Verify correct server IP and port

## 📝 Implementation Details

### HelloServer.java
- Listens on `0.0.0.0:50051` (all network interfaces)
- Supports both unary and streaming RPC
- Implements multi-language greeting logic
- Graceful shutdown on termination

### HelloClient.java
- Connects to local or remote servers
- Flexible argument parsing
- Language code normalization
- Supports both unary and streaming calls

### Generated Files
- `Hello.java` - Protocol Buffer container
- `HelloRequest.java` - Request message (auto-generated)
- `HelloResponse.java` - Response message (auto-generated)
- `HelloServiceGrpc.java` - Service stubs (auto-generated)

## 🔍 Performance Tips

1. **Persistent connections**: Client reuses channel for multiple calls
2. **Async operations**: Client blocks only for response (synchronous for simplicity)
3. **Streaming**: Server can stream multiple responses per request
4. **Error handling**: Graceful error handling with logging

## 📚 Dependencies

- `grpc-netty-shaded:1.58.0` - Netty transport
- `grpc-protobuf:1.58.0` - Protocol Buffer support
- `grpc-stub:1.58.0` - gRPC stubs
- `protobuf-java:3.24.0` - Protocol Buffer runtime

## 🤝 Contributing

Feel free to extend with additional features:
- Client-side streaming
- Bidirectional streaming
- Custom interceptors
- Additional language translations

## 📄 License

Open source - educational purposes

---

**Quick Start:**
```bash
# Terminal 1: Build and run server
cd java && ./build.sh
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloServer

# Terminal 2: Run client
cd java
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient zaid chibani fr
```
