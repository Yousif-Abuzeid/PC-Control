#include "Lib/socket.hpp"
#include <nlohmann/json.hpp>

int main() {
    try {
        // Create server socket on port 8080
        pcControl::sockets::ServerSocket server(8080);

        // Listen for incoming connections
        server.listenSocket(5);

        // Accept a connection
        server.acceptConnection();

         std::string response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "Connection: close\r\n"
            "\r\n"
            "Hello, world!";
        
       // Send response to client
    
        server.sendData(response);
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}
