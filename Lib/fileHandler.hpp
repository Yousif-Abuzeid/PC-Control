#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "socket.hpp"
namespace pcControl {
    namespace fileHandler {
        class FileHandler {
            private:
                std::string filePath;
                std::fstream file;
            public:
                FileHandler(const std::string& filePath);
                ~FileHandler();
                void setFilePath(const std::string& filePath);
                void writeToFile(const std::string& filePath,const std::string& data);
                std::string readFromFile();

                void sendFile(const std::string& filePath,const int port);

                std::vector<std::string> listFiles(const std::string& dirPath);
        };
    }
}

#endif // !FILEHANDLER_HPP
#define FILEHANDLER_HPP



