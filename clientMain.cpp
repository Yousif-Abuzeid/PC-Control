#include "Lib/socket.hpp"

int main() {
    try {
        // Connect to the server on localhost, port 8080
        pcControl::sockets::ClientSocket client("127.0.0.1", 8080);

        // Receive a message from the server
        std::string receivedMessage = client.receiveData();
        std::cout << "Received from server: " << receivedMessage << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }

    return 0;
}
