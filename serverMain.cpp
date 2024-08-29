#include "Lib/socket.hpp"

int main() {
    try {
        // Create server socket on port 8080
        pcControl::sockets::ServerSocket server(8080);

        // Listen for incoming connections
        server.listenSocket(5);

        // Accept a connection
        server.acceptConnection();

        // Send a message to the client
        std::string message = "Hello from the server!";
        server.sendData(message);
        
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}
