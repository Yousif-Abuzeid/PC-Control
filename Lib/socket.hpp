#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

namespace pcControl {
    namespace  sockets{
const int default_domain = AF_INET;
const int default_type = SOCK_STREAM;
const int default_protocol = 0;

const int default_port = 8080;
const int default_s_addr = INADDR_ANY;
const int default_backlog = 5;

const int default_buffer_size = 1024;
class mySocket {

protected:

    char buffer[default_buffer_size]={0};

public:
    

    // Socket(const Socket&) = delete;            // Delete copy constructor
    // Socket& operator=(const Socket&) = delete; // Delete copy assignment
    // Socket(Socket&&) noexcept;                 // Move constructor
    // Socket& operator=(Socket&&) noexcept;      // Move assignment

    ~mySocket() =default;
    virtual char* getBuffer() { return buffer; }
    virtual void clearBuffer() { memset(buffer, 0, default_buffer_size); }
    virtual int getSocket() const =0;
    //void connectSocket(const std::string& ip, int port) //client
    //int acceptConnection();
    virtual void sendData(std::string data)=0;
    virtual std::string receiveData()=0;
    bool CheckConnection();

};

class ServerSocket : public mySocket {
    private:
    int serverSockFd; // Server socket file descriptor
    int clientSockFd; // Client socket file descriptor
    sockaddr_in serverAddr; // Server address
    sockaddr_in clientAddr; // Client address

    // helper functions
    void bindSocket();
    
    public:

    // Constructor
    ServerSocket(int port=default_port);
    // Destructor
    ~ServerSocket();
    
    ServerSocket(const ServerSocket&) = delete;            // Delete copy constructor
    ServerSocket& operator=(const ServerSocket&) = delete; // Delete copy assignment
    ServerSocket(ServerSocket&&) noexcept;                 // Move constructor
    ServerSocket& operator=(ServerSocket&&) noexcept;      // Move assignment

    // Get server socket file descriptor
    int getSocket() const override;

    // Listen for incoming connections
    void listenSocket(int backlog=default_backlog);

    //Accept connection from client
    void acceptConnection();

    // Send data to client
    void sendData(std::string data) override;
    
    // Receive data from client
    std::string receiveData() override;

    

};

class ClientSocket : public mySocket {
    private:
    int clientSockFd; // Client socket file descriptor
    sockaddr_in serverAddr; // Server address
    std::string ip;
    public:

    // Constructor
    ClientSocket(const std::string& ip, int port);
    // Destructor
    ~ClientSocket();

    ClientSocket(const ClientSocket&) = delete;            // Delete copy constructor
    ClientSocket& operator=(const ClientSocket&) = delete; // Delete copy assignment
    ClientSocket(ClientSocket&&) noexcept;                 // Move constructor
    ClientSocket& operator=(ClientSocket&&) noexcept;      // Move assignment

    // Get client socket file descriptor
    int getSocket() const override;
    // Change server address
    void setServerAddr(const std::string& ip, int port);
    // Connect to server
    void connectSocket();
    // Send data to server
    void sendData(std::string data) override;

    // Receive data from server
    std::string receiveData() override;

};

}
}
#endif // !SOCKET_HPP