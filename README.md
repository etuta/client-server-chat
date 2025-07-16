# C Chat Server and Client

This project provides a simple TCP-based chat server and client implemented in C. It demonstrates fundamental socket programming concepts, multithreading, and basic message broadcasting to multiple clients.

---

## Overview

The chat server accepts multiple concurrent TCP client connections, relaying messages from any connected client to all others. The client connects to the server, reads input from the user, and sends messages over the network while concurrently displaying received messages.

This project is intended for:

- Learning **network socket programming** in C.
- Understanding **multithreaded server architectures**.
- Demonstrating concepts relevant to **IT infrastructure**, such as:
  - TCP connection management
  - Client session handling
  - Simple message broadcasting
  - Basic concurrency with pthreads

---

## Features

- TCP server that:
  - Listens on a configurable port.
  - Supports up to 100 concurrent clients.
  - Broadcasts incoming messages to all connected clients.

- TCP client that:
  - Connects to a specified server and port.
  - Sends user input to the server.
  - Receives and displays messages from the server.
  - Shows timestamps on received messages.

- Multithreaded design using **pthreads** for concurrent client handling.

---

## Use Cases

- Training and demonstration in **network programming** courses.
- Proof of concept for **internal chat utilities** over secure networks.
- Basis for further development into secure or feature-rich messaging systems.

---

## Building

Ensure you have a C compiler and POSIX environment (e.g., Linux or macOS).

Build both server and client using the provided `Makefile`:

```
make
```

This generates two executables:

- `chat-server`
- `chat-client`

To clean up:

```
make clean
```

---

## Running the Server

Start the server and specify the TCP port to listen on:

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

## Example Workflow

1. Start the server:

   ```
   ./chat-server 5000
   ```

2. In separate terminals or machines, start multiple clients:

   ```
   ./chat-client 127.0.0.1 5000
   ```

3. Type messages in any client terminal.
   - The server will broadcast each message to all connected clients.

---

## Technical Details

- **Networking**
  - IPv4 TCP sockets.
  - `getaddrinfo()` for address resolution.
  - `bind()`, `listen()`, `accept()` on the server side.
  - `connect()` on the client side.

- **Concurrency**
  - Each client connection handled in a dedicated thread.
  - Simple shared array tracks active connections.
  - No advanced synchronization (intended for demonstration).

- **Limitations**
  - No authentication or encryption.
  - Limited to 100 concurrent clients.
  - No persistence or message history.

---

## Potential Improvements

This project can be extended in many ways:

- Add SSL/TLS for secure communication.
- Implement authentication and user management.
- Improve thread safety and error handling.
- Build a richer client interface.

---

## Authors

- Tenzin Dolma Gyalpo
- Eliza-Teodora Tuta
