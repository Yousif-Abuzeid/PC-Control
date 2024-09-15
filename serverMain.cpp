#include "Lib/socket.hpp"
#include "Lib/webBrowserHandler.hpp"
#include <nlohmann/json.hpp>
#include <thread>
#include "Lib/App.hpp"

int main() {
    try {
        // Create server socket on port 8080
    //     pcControl::sockets::ServerSocket server(8080);
    //     std::string userName = std::getenv("USER");
    //     // Listen for incoming connections
    //     std::cout<<userName<<std::endl;
    //     server.listenSocket(5);

    //     // Accept a connection
    //     server.acceptConnection();

    //     server.sendData(userName);
      
    //    std::string message;

    //    while(message != "exit") {
    //         server.clearBuffer();
    //         message = server.receiveData();
    //         while(message.empty()){
    //             server.closeClientSocket();
    //             std::cout<<"Connection Lost"<<std::endl;
    //             std::this_thread::sleep_for(std::chrono::seconds(25));
    //             server.acceptConnection();
    //             server.sendData(userName);
    //             message = server.receiveData();
    //         }
    //        std::cout << "Received: " << message << std::endl;
    //        if(message.find("open") != std::string::npos) {
    //            std::string url = message.substr(5);
    //            pcControl::webBrowserHandler::WebBrowserHandler::openWebBrowser(url);
    //            std::cout << "Opening web browser to "+url << std::endl;
    //        } else if(message.find("close") != std::string::npos) {
    //            pcControl::webBrowserHandler::WebBrowserHandler::closeWebBrowser();
    //             std::cout << "Closing web browser" << std::endl;
    //        }
           
    //    }
    // //     server.sendData(response);
    //  } catch (const std::exception& e) {
    //     std::cerr << "Server error: " << e.what() << std::endl;
    // }
    mainLoop();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}
