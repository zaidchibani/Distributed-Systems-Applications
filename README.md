# Distributed Systems Applications - gRPC HelloWorld

A cross-language gRPC application demonstrating communication between Python, C++, and Java services with multi-language support (English, French, Arabic).

## 📋 Overview

This project implements a gRPC-based "HelloWorld" service with:
- **Multi-language support**: English (EN), French (FR), and Arabic (AR)
- **Two RPC types**: Unary RPC and Server Streaming RPC
- **Cross-language compatibility**: Python, C++, and Java implementations that can communicate with each other
- **Remote connectivity**: Clients can connect to remote servers across networks

## 🏗️ Architecture

```
┌─────────────────┐         gRPC          ┌─────────────────┐
│  Python Client  │ ◄──────────────────► │  Python Server  │
└─────────────────┘                       └─────────────────┘
        │                                          ▲
        │                                          │
        │           Cross-language                 │
        │           Communication                  │
        │                                          │
        ▼                                          │
┌─────────────────┐         gRPC          ┌─────────────────┐
│   C++ Client    │ ◄──────────────────► │   C++ Server    │
└─────────────────┘                       └─────────────────┘
        │                                          ▲
        │                                          │
        │                                          │
        ▼                                          │
┌─────────────────┐         gRPC          ┌─────────────────┐
│   Java Client   │ ◄──────────────────► │   Java Server   │
└─────────────────┘                       └─────────────────┘
```

## 📁 Project Structure

```
Distributed-Systems-Applications/
├── hello.proto              # Protocol Buffer definition (shared)
├── python/
│   ├── server.py           # Python gRPC server
│   ├── client.py           # Python gRPC client
│   ├── hello_pb2.py        # Generated Python protobuf code
│   ├── hello_pb2_grpc.py   # Generated Python gRPC code
│   └── requirements.txt    # Python dependencies
├── C++/
│   ├── hello_server.cpp    # C++ gRPC server
│   ├── hello_client.cpp    # C++ gRPC client
│   ├── hello.pb.h          # Generated C++ protobuf header
│   ├── hello.pb.cc         # Generated C++ protobuf implementation
│   ├── hello.grpc.pb.h     # Generated C++ gRPC header
│   ├── hello.grpc.pb.cc    # Generated C++ gRPC implementation
│   ├── Makefile            # Build script for C++
│   ├── hello_server        # Compiled server executable
│   └── hello_client        # Compiled client executable
├── java/
│   ├── pom.xml             # Maven build configuration
│   ├── build.sh            # Build script
│   ├── run-server.sh       # Server run script
│   ├── run-client.sh       # Client run script
│   ├── src/
│   │   └── main/
│   │       └── java/
│   │           └── org/
│   │               └── baeldung/
│   │                   └── grpc/
│   │                       ├── HelloServer.java   # Java gRPC server
│   │                       └── HelloClient.java   # Java gRPC client
│   └── target/             # Build output (generated)
│       └── grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar
└── README.md               # This file
```

## 🔧 Prerequisites

### For Python:
- Python 3.8 or higher
- pip (Python package manager)

### For C++:
- g++ compiler with C++11 support or higher
- gRPC C++ libraries
- Protocol Buffers compiler (protoc)

### For Java:
- Java 11 or higher
- Maven 3.6 or higher

## 📦 Installation

### Python Setup

1. Install Python dependencies:
```bash
cd python
pip install -r requirements.txt
```

2. Generate Python gRPC stubs (if needed):
```bash
cd ..
python3 -m grpc_tools.protoc -I. --python_out=./python --grpc_python_out=./python hello.proto
```

### C++ Setup

1. Install gRPC and Protocol Buffers:
```bash
# On Ubuntu/Debian
sudo apt-get install -y build-essential autoconf libtool pkg-config
sudo apt-get install -y libgrpc++-dev protobuf-compiler-grpc
```

2. Generate C++ gRPC stubs and compile:
```bash
cd C++
make
```

### Java Setup

1. Install Java and Maven:
```bash
# On Ubuntu/Debian
sudo apt-get install -y openjdk-11-jdk maven
```

2. Build the Java project:
```bash
cd java
./build.sh
# or manually:
mvn clean compile package
```

## 🚀 Usage

### Running Servers

#### Python Server
```bash
cd python
python3 server.py
# or use the executable:
./server.py
```

The server will start on `0.0.0.0:50051` and display:
```
gRPC server started on 0.0.0.0:50051
```

#### C++ Server
```bash
cd C++
./hello_server
```

The server will start on `0.0.0.0:50051` and display:
```
Server listening on 0.0.0.0:50051
```

#### Java Server

1. Build the Java project first:
```bash
cd java
mvn clean compile package
# or use the build script:
./build.sh
```

2. Start the server:
```bash
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloServer
# or use the run script:
./run-server.sh
```

The server will start on `0.0.0.0:50051` and display:
```
INFO: Server started, listening on 50051
```

### Running Clients

#### Python Client

**Local connection:**
```bash
cd python
python3 client.py <first_name> <last_name> <language>
# or use the executable:
./client.py <first_name> <last_name> <language>
```

**Remote connection:**
```bash
./client.py <first_name> <last_name> <language> --target <server_ip>:50051
```

**Examples:**
```bash
# English greeting
./client.py zaid chibani en
# Output: Hello, zaid chibani!

# French greeting
./client.py zaid chibani fr
# Output: bonjour, zaid chibani

# Arabic greeting
./client.py zaid chibani ar
# Output: مرحبا، zaid chibani

# Connect to remote server
./client.py zaid chibani fr --target 192.168.1.100:50051
```

#### C++ Client

**Local connection:**
```bash
cd C++
./hello_client <first_name> <last_name> <language>
```

**Remote connection:**
```bash
./hello_client <first_name> <last_name> <language> <server_ip>:50051
```

**Examples:**
```bash
# English greeting
./hello_client zaid chibani en
# Output: Hello, zaid chibani!

# French greeting
./hello_client zaid chibani fr
# Output: bonjour, zaid chibani

# Arabic greeting
./hello_client zaid chibani ar
# Output: مرحبا، zaid chibani

# Connect to remote server
./hello_client zaid chibani fr 192.168.1.100:50051
```

#### Java Client

**Build and run:**
```bash
cd java
mvn clean compile package  # or use ./build.sh
```

**Local connection:**
```bash
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient <first_name> <last_name> <language>
```

**Remote connection:**
```bash
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient <first_name> <last_name> <language> --target <server_ip>:50051
```

**Examples:**
```bash
# English greeting
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient zaid chibani en
# Output: INFO: Greeting: Hello zaid chibani

# French greeting
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient zaid chibani fr
# Output: INFO: Greeting: Bonjour zaid chibani

# Arabic greeting
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient zaid chibani ar
# Output: INFO: Greeting: مرحبا zaid chibani

# Connect to remote server
java -cp target/grpc-hello-world-1.0-SNAPSHOT-jar-with-dependencies.jar org.baeldung.grpc.HelloClient zaid chibani fr --target 192.168.1.100:50051
```

### Language Codes

- `en` - English
- `fr` - French (Français)
- `ar` - Arabic (العربية)

If no language is specified, English is used by default.

## 🔄 Cross-Language Communication

This project demonstrates true cross-language gRPC communication:

### Python Client → C++ Server
```bash
# Terminal 1 (Start C++ server)
cd C++
./hello_server

# Terminal 2 (Run Python client)
cd python
./client.py zaid chibani fr
```

### C++ Client → Python Server
```bash
# Terminal 1 (Start Python server)
cd python
./server.py

# Terminal 2 (Run C++ client)
cd C++
./hello_client zaid chibani fr
```

### Java Client → Python Server
```bash
# Terminal 1 (Start Python server)
cd python
./server.py

# Terminal 2 (Run Java client)
cd java
./run-client.sh zaid chibani fr
```

### Python Client → Java Server
```bash
# Terminal 1 (Start Java server)
cd java
./run-server.sh

# Terminal 2 (Run Python client)
cd python
./client.py zaid chibani fr
```

### Any Client → Any Server
All combinations work seamlessly:
- Python Client ↔ Python/C++/Java Server
- C++ Client ↔ Python/C++/Java Server
- Java Client ↔ Python/C++/Java Server

## 🌐 Remote Server Connection

To allow remote clients to connect to your server:

1. **Start the server** (Python or C++) on the host machine
2. **Check the server is listening:**
   ```bash
   ss -ltnp | grep 50051
   # or
   netstat -ltnp | grep 50051
   ```
   You should see the server listening on `0.0.0.0:50051` or `:::50051`

3. **Configure firewall** (if enabled):
   ```bash
   sudo ufw allow 50051/tcp
   sudo ufw status
   # or disable firewall temporarily for testing:
   sudo ufw disable
   ```

4. **Get your IP address:**
   ```bash
   # Local network IP
   ip a
   # or public IP
   curl ifconfig.me
   ```

5. **Connect from remote client:**
   ```bash
   # Python client
   ./client.py zaid chibani fr --target <server_ip>:50051
   
   # C++ client
   ./hello_client zaid chibani fr <server_ip>:50051
   ```

## 🔍 Protocol Buffer Definition

The service is defined in `hello.proto`:

```protobuf
service HelloService {
    // Unary RPC: single request, single response
    rpc hello(HelloRequest) returns (HelloResponse);

    // Server streaming RPC: single request, multiple responses
    rpc helloStream(HelloRequest) returns (stream HelloResponse);
}
```

### Message Types:
- **HelloRequest**: Contains first name, last name, and language preference
- **HelloResponse**: Contains the greeting message

## 🛠️ Troubleshooting

### Connection Refused
- Ensure the server is running: `ss -ltnp | grep 50051`
- Check firewall settings: `sudo ufw status`
- Verify the correct IP and port are being used

### Module Not Found (Python)
```bash
cd python
pip install -r requirements.txt
```

### Compilation Errors (C++)
```bash
cd C++
make clean
make
```

### Port Already in Use
```bash
# Find and kill the process using port 50051
sudo lsof -ti:50051 | xargs kill -9
# or
sudo ss -lptn 'sport = :50051'
```

## 📝 Development

### Regenerating Protocol Buffer Code

**Python:**
```bash
python3 -m grpc_tools.protoc -I. --python_out=./python --grpc_python_out=./python hello.proto
```

**C++:**
```bash
cd C++
make clean
make
```

### Making Scripts Executable

```bash
# Python
chmod +x python/server.py
chmod +x python/client.py

# C++ (after compilation)
chmod +x C++/hello_server
chmod +x C++/hello_client
```

## 📚 Features

- ✅ Unary RPC (single request/response)
- ✅ Server streaming RPC (single request, multiple responses)
- ✅ Multi-language support (EN, FR, AR)
- ✅ Cross-language compatibility (Python ↔ C++)
- ✅ Local and remote server connectivity
- ✅ Command-line interface with flexible argument parsing
- ✅ Executable Python scripts with shebang
- ✅ Compiled C++ executables

## 🤝 Contributing

Feel free to submit issues, fork the repository, and create pull requests for any improvements.

## 📄 License

This project is open source and available for educational purposes.

## 👤 Author

**Zaid Chibani**
- GitHub: [@zaidchibani](https://github.com/zaidchibani)

**wejden Abdelmoumen**

**Mohamed Anas Rejeb**
- Repository: [Distributed-Systems-Applications](https://github.com/zaidchibani/Distributed-Systems-Applications)

---

**Note**: This is a demonstration project for learning gRPC and cross-language service communication in distributed systems.
