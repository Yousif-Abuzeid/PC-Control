#include "commands.hpp"
#include "socket.hpp"
#include "screenShare.hpp"
#include "webBrowserHandler.hpp"
#include "laptopStatus.hpp"




void webHandler(std::string command);
void screenShareHandler(std::string command);
void startServer(pcControl::sockets::ServerSocket &socket);
std::string handleCommand(std::string command, pcControl::sockets::mySocket &socket);
void mainLoop();

