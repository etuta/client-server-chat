# C Chat Server and Client

A simple multithreaded TCP chat server and client implemented in C.  
This project illustrates fundamental concepts essential for IT professionals and system administrators managing networked environments.

---

## Overview

This project provides:

- A TCP server that can handle up to 100 concurrent clients.
- A client that connects to the server, sends messages, and displays incoming broadcasts.
- Use of `pthread` threads to manage multiple client sessions.

It demonstrates core networking principles that are critical for IT and system administration roles.

---

## Why It Matters for IT and System Administration

System administrators and IT engineers often need to:

- Understand how TCP connections are established and maintained.
- Debug and monitor communication between clients and servers.
- Build tools for internal communication or alerting over a network.

This project shows how to:

- Create and bind sockets (`socket()`, `bind()`, `listen()`).
- Accept and handle incoming client connections (`accept()`).
- Connect clients to servers (`connect()`).
- Broadcast messages to multiple clients.
- Manage concurrency with threads.

By studying and extending this project, you can develop practical skills to:

- Troubleshoot network connectivity.
- Build simple internal tools for status updates and notifications.
- Test firewall rules, routing, and port configurations.
- Understand the foundations of secure and reliable communication services.

---

## Building

Ensure you have a C compiler installed (e.g., `gcc`).

Use the provided `Makefile` to compile both components:

```
make
```

This generates:

- `chat-server`: the server executable.
- `chat-client`: the client executable.

Clean up build artifacts:

```
make clean
```

---

## Running the Server

Start the server with a specified port:

```
./chat-server <port>
```

Example:

```
./chat-server 5000
```

---

## Running the Client

Start the client, providing the server’s hostname/IP and port:

```
./chat-client <hostname> <port>
```

Example:

```
./chat-client 127.0.0.1 5000
```

---

## Usage in IT Environments

This project can be applied to:

- Testing network connectivity between servers and clients.
- Simulating chat or alerting services on internal networks.
- Practicing deployment and monitoring of network services.
- Experimenting with multithreaded concurrency and resource management.
- Building a foundation for more advanced secure messaging solutions.

---

## Educational Value

Working with this code provides hands-on experience in:

- Socket APIs (`getaddrinfo()`, `send()`, `recv()`).
- Multithreaded server architecture.
- Message broadcasting and buffering.
- Real-world considerations like resource cleanup and error handling.

These are valuable skills for IT administrators who maintain and secure infrastructure.

---

## Security Considerations

**Note:** This project does not include authentication or encryption. If you deploy it beyond an isolated environment, consider adding:

- TLS encryption for secure transport.
- Authentication mechanisms to prevent unauthorized access.

---

## Authors

- Eliza-Teodora Tuta
- Tenzin Dolma Gyalpo
