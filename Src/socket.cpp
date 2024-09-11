#include "../Lib/socket.hpp"
#include <exception>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>


namespace pcControl {


    namespace sockets{ 

        bool mySocket::CheckConnection(){
            int result = recv(getSocket(), buffer, default_buffer_size, MSG_PEEK|MSG_DONTWAIT);
            if(result == 0) {
                return false;
            } else {
                return true;
            }
        }

        ServerSocket::ServerSocket(int port){
            /*
                Try to open Socket if not opened correctly Throw Error
            */
            try{
            serverSockFd = socket(default_domain,default_type,default_protocol);
                if(serverSockFd<0){
                    throw std::runtime_error("Error creating socket");
                }
            }
            catch(std::exception &e){
                std::cerr << e.what() << std::endl;
            }

            /*
                Try to bind socket
            */
            serverAddr.sin_family =  default_domain;
            serverAddr.sin_port = htons(port);
            serverAddr.sin_addr.s_addr= INADDR_ANY;

            try{
                if (bind(serverSockFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
                    throw std::runtime_error("Error binding socket with port: "+std::to_string(port)); 
                }
        
        }catch(std::exception &e){
            std::cerr<<e.what()<<std::endl;
        }

        }

        int ServerSocket::getSocket() const{
            return serverSockFd;
        }

        // Listen Method

        void ServerSocket::listenSocket(int backlog){
            try{
                if(listen(serverSockFd, backlog)<0){
                    throw std::runtime_error("Error Listening on socket");

                }
                std::cout<<"Listening ... "<<std::endl;
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
        }

        void ServerSocket::acceptConnection(){
            socklen_t addrLen = sizeof(clientAddr);
            try{
            clientSockFd=accept(serverSockFd, (struct sockaddr*)&clientAddr,&addrLen);
            if(clientSockFd<0){
                throw std::runtime_error("Error Accepting Client Connection");
            }
            std::cout<<"Connected Successfully"<<std::endl;
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }   

        }

        void ServerSocket::sendData(std::string data){ 
            try{
                
                if(send(clientSockFd, data.c_str(), data.size(), 0)<0){
                    throw std::runtime_error("Error Sending Data");
                }
                std::cout<<"Data Sent Successfully"<<std::endl;
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
        
        }
        std::string ServerSocket::receiveData(){
            try{
                int valread = read(clientSockFd, buffer, default_buffer_size);
                if(valread<0){
                    throw std::runtime_error("Error Receiving Data");
                }
                std::cout<<"Data Received Successfully"<<std::endl;
                return std::string(buffer);
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
            return "";
        }
        void ServerSocket::closeSocket(){
            close(serverSockFd);
        }
        void ServerSocket::closeClientSocket(){
            close(clientSockFd);
        }

        ServerSocket::~ServerSocket(){
            closeClientSocket();
            closeSocket();
        }

        ClientSocket::ClientSocket(const std::string& ip, int port):ip(ip){
            serverAddr.sin_family = default_domain;
            serverAddr.sin_port = htons(port);
            serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
            try{
                clientSockFd = socket(default_domain,default_type,default_protocol);
                if(clientSockFd<0){
                    throw std::runtime_error("Error creating socket");
                }
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }

            try{
                if(connect(clientSockFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr))<0){
                    throw std::runtime_error("Error connecting to server");
                }
                std::cout<<"Connected to server"<<std::endl;
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
        }

        int ClientSocket::getSocket() const{
            return clientSockFd;
        }

        void ClientSocket::sendData(std::string data){
            try{
                
                if(send(clientSockFd, data.c_str(), data.size(), 0)<0){
                    throw std::runtime_error("Error Sending Data");
                }
                std::cout<<"Data Sent Successfully"<<std::endl;
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
        }

        std::string ClientSocket::receiveData(){
            try{
                int valread = read(clientSockFd, buffer, default_buffer_size);
                if(valread<0){
                    throw std::runtime_error("Error Receiving Data");
                }
                std::cout<<"Data Received Successfully"<<std::endl;
                return std::string(buffer);
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
            return "";
        }

        ClientSocket::~ClientSocket(){
            close(clientSockFd);
        }



    
    }
}