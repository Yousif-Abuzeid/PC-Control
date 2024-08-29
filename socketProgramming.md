# Sockets

## What is a socket?

A socket is one endpoint of a two-way communication link between two programs running on the network. A socket is bound to a port number so that the TCP layer can identify the application that data is destined to.

## What is the socket identified by?

A socket is identified by an IP address concatenated with a port number.

## How does a socket work?

A socket is created by a process and is used to send and receive data. The process binds a socket to a port number on the machine it is running on. The process then listens for incoming connections on the socket. When a connection is made, the process can send and receive data on the socket.

## What are the types of sockets?

There are two types of sockets: stream sockets and datagram sockets. Stream sockets use TCP to provide a reliable connection between two programs. Datagram sockets use UDP to provide a connectionless communication between two programs.

## What is a stream socket?

A stream socket is a type of socket that uses TCP to provide a reliable connection between two programs. A stream socket is used when the data being sent must be received in the same order it was sent.

## What is a datagram socket?

A datagram socket is a type of socket that uses UDP to provide a connectionless communication between two programs. A datagram socket is used when the data being sent does not need to be received in the same order it was sent.

## What is a socket address?

A socket address is the combination of an IP address and a port number. A socket address is used to identify a socket on the network.

## What is a socket option?

A socket option is a parameter that can be set on a socket to control its behavior. Socket options can be used to set the timeout for a socket, enable or disable the reuse of a socket address, and other parameters.

## What is a socket descriptor?

A socket descriptor is a unique identifier that is assigned to a socket when it is created. The socket descriptor is used to refer to the socket in the program.

## What is a socket buffer?

A socket buffer is a region of memory that is used to store data that is being sent or received on a socket. The socket buffer is used to hold the data until it can be processed by the program.

## What is a socket connection?

A socket connection is a connection between two programs that allows them to send and receive data. A socket connection is established when a process binds a socket to a port number and listens for incoming connections.

## What is a socket server?

A socket server is a program that listens for incoming connections on a socket. When a connection is made, the server can send and receive data on the socket.

## What is a socket client?

A socket client is a program that connects to a socket server. The client can send and receive data on the socket.

## What is a socket programming?

Socket programming is a way of connecting two nodes on a network to communicate with each other. One socket(node) listens on a particular port at an IP, while other socket reaches out to the other to form a connection. The server forms the listener socket while the client reaches out to the server.

# Socket Programming in C++

## How to create a socket in C++?

To create a socket in C++, you need to include the `sys/socket.h` header file and use the `socket()` function to create a socket. The `socket()` function takes three arguments: the address family (AF_INET for IPv4), the socket type (SOCK_STREAM for stream sockets), and the protocol (0 for the default protocol).

```cpp
#include <sys/socket.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }
    return 0;
}
```

## How to bind a socket to a port in C++?


To bind a socket to a port in C++, you need to use the `bind()` function. The `bind()` function takes three arguments: the socket file descriptor, a pointer to a `sockaddr` structure that contains the IP address and port number to bind to, and the size of the `sockaddr` structure.

```cpp

#include <sys/socket.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    return 0;
}
```

## How to listen for incoming connections on a socket in C++?

To listen for incoming connections on a socket in C++, you need to use the `listen()` function. The `listen()` function takes two arguments: the socket file descriptor and the maximum number of connections that can be queued.

```cpp

#include <sys/socket.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    if (listen(sockfd, 5) < 0) {
        perror("Error listening on socket");
        return 1;
    }

    return 0;
}
```


## How to accept an incoming connection on a socket in C++?

To accept an incoming connection on a socket in C++, you need to use the `accept()` function. The `accept()` function takes three arguments: the socket file descriptor, a pointer to a `sockaddr` structure that will contain the address of the client, and a pointer to an integer that will contain the size of the `sockaddr` structure.

```cpp

#include <sys/socket.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    if (listen(sockfd, 5) < 0) {
        perror("Error listening on socket");
        return 1;
    }

    struct sockaddr_in client_addr;
    int client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr));
    if (client_sockfd < 0) {
        perror("Error accepting connection");
        return 1;
    }

    return 0;
}
```

## How to connect to a socket server in C++?

To connect to a socket server in C++, you need to use the `connect()` function. The `connect()` function takes three arguments: the socket file descriptor, a pointer to a `sockaddr` structure that contains the IP address and port number of the server, and the size of the `sockaddr` structure.

```cpp

#include <sys/socket.h>


int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr()

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error connecting to server");
        return 1;
    }

    return 0;
}
```

## How to send data over a socket in C++?

To send data over a socket in C++, you need to use the `send()` function. The `send()` function takes four arguments: the socket file descriptor, a pointer to the data to send, the size of the data, and flags (usually set to 0).

```cpp

#include <sys/socket.h>



int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr()

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error connecting to server");
        return 1;
    }

    char data[] = "Hello, world!";
    if (send(sockfd, data, sizeof(data), 0) < 0) {
        perror("Error sending data");
        return 1;
    }

    return 0;
}
```

## How to receive data over a socket in C++?

To receive data over a socket in C++, you need to use the `recv()` function. The `recv()` function takes four arguments: the socket file descriptor, a pointer to a buffer to store the received data, the size of the buffer, and flags (usually set to 0).

```cpp

#include <sys/socket.h>



int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr()

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error connecting to server");
        return 1;
    }

    char data[1024];
    if (recv(sockfd, data, sizeof(data), 0) < 0) {
        perror("Error receiving data");
        return 1;
    }

    return 0;
}
```

## How to close a socket in C++?

To close a socket in C++, you need to use the `close()` function. The `close()` function takes one argument: the socket file descriptor.

```cpp

#include <sys/socket.h>



int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr()

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error connecting to server");
        return 1;
    }

    close(sockfd);

    return 0;
}
```


## How to handle multiple connections in C++?

To handle multiple connections in C++, you can use the `select()` function. The `select()` function takes three arguments: the maximum file descriptor value plus one, a pointer to a set of file descriptors to read from, and a pointer to a set of file descriptors to write to.

```cpp

#include <sys/socket.h>
#include <sys/select.h>




int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr()

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error connecting to server");
        return 1;
    }

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    if (select(sockfd + 1, &readfds, NULL, NULL, NULL) < 0) {
        perror("Error selecting file descriptors");
        return 1;
    }

    if (FD_ISSET(sockfd, &readfds)) {
        char data[1024];
        if (recv(sockfd, data, sizeof(data), 0) < 0) {
            perror("Error receiving data");
            return 1;
        }
    }

    return 0;
}
```

