#include "../Lib/App.hpp"
#include <cctype>
#include <cmath>
#include <memory>
#include <string>
#include <thread>

/*
 Function to handle web commands
*/
void webHandler(std::string url){
    pcControl::webBrowserHandler::WebBrowserHandler::openWebBrowser(url);
}
/*
 Function to handle screen share commands
*/
std::shared_ptr<pcControl::screenShare::screenShareServer> screenShareServer;
void screenShareHandler(){
    screenShareServer = std::make_shared<pcControl::screenShare::screenShareServer>(8090);
    std::cout<<"Starting Screen Share Server"<<std::endl;
    std::cout<<"Server Running on Port 8090"<<std::endl;
    /*
        Start the server in a new thread

    */
    
    std::thread serverThread(&pcControl::screenShare::screenShareServer::start,screenShareServer);
    /*
        Detach the thread
        to run in the background
    */
    serverThread.detach();
}
/*
    Function to Start the server
    params: socket - The server socket to start
*/



void startServer(pcControl::sockets::ServerSocket &socket){
    socket.listenSocket();
    socket.acceptConnection();
}
/*
    Main Loop of the application
*/
void mainLoop(){
    int failCounts = 0;
    int timeToWait = 1;
    pcControl::sockets::ServerSocket socket(8080);
    startServer(socket);
    while(true){
        
        if(socket.CheckConnection()){
            std::string command = socket.receiveData();
            std::string response = handleCommand(command);
            if(std::tolower(response.find("web")) != std::string::npos){
                socket.clearBuffer();
            }
            socket.sendData(response);
            //reset failCounts
            failCounts = 0;
        }else{
            //wait for 2^failCounts seconds
            timeToWait=static_cast<int>(pow(2,failCounts));
            std::cout<<"No Connection"<<std::endl;
            std::cout<<"Try to reconnect in" <<std::to_string(timeToWait) +" seconds"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(timeToWait));
            startServer(socket);
            //increment failCounts
            failCounts++;
            if(failCounts>5){
                std::cout<<"Connection Lost"<<std::endl;
                break;
            }
        }

    }


}
/*
    Function to handle the command
    params: command - The command to handle
    returns: string - The response to the command
*/
std::string helpMenu(){
    return "Commands:\n1. open <url> - Open a website\n2.\
    screenShare - Start Screen Share\n3.\
    screenShareStop - Stop Screen Share\n4.\
    help - Display Help Menu";
}
std::string handleCommand(std::string command){
    if(command.find(OPEN_WEBSITE) != std::string::npos){
        webHandler(command.substr(OPEN_WEBSITE.length()));
        return "Web Command Executed "+ command.substr(OPEN_WEBSITE.length()) ;
    }
    if(command.find(SCREEN_SHARE) != std::string::npos){
        screenShareHandler();
        return "Screen Share Command Executed";
    }
    if(command.find(SCREEN_SHARE_STOP)!=std::string::npos){
        
        //reset the pointer so the thread can die
        screenShareServer.reset();
        return "Screen Share Stopped";
    }
    if(command.find(HELP)!=std::string::npos){
        return helpMenu();
    }
    return "Command Not Found";
}