#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <fstream>
#include <string>
#include <vector>

namespace pcControl {
    namespace fileHandler {
        class FileHandler {
            private:
                std::string filePath;
                std::fstream file;
            public:
                FileHandler(std::string& filePath);
                ~FileHandler();
                void writeToFile(const std::string& filePath,const std::string& data);
                std::string readFromFile();

                void sendFile(std::string data);
                std::vector<std::string> listFiles(const std::string& dirPath);
        };
    }
}

#endif // !FILEHANDLER_HPP
#define FILEHANDLER_HPP



