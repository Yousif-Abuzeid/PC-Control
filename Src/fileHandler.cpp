#include "../Lib/fileHandler.hpp"
#include <vector>
#include <iostream>
namespace pcControl {
    namespace fileHandler{
        FileHandler::FileHandler(const std::string& filePath ):filePath(filePath){
            try{
            file.open(filePath,std::ios::in | std::ios::app);
            if(!file.is_open()){
                throw std::runtime_error("Error opening file");
            }
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
            
        }
        FileHandler::~FileHandler(){
            if(file.is_open()){
            file.close();
            }
            
        }
        void FileHandler::setFilePath(const std::string& filePath){
            this->filePath=filePath;
        }
        void FileHandler::writeToFile(const std::string& filePath,const std::string& data){
            try{
                file.open(filePath,std
                ::ios::in | std::ios::out | std::ios::app);
                if(!file.is_open()){
                    throw std::runtime_error("Error opening file");
                }
                file<<data;
                file.close();
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }

        }
        std::string FileHandler::readFromFile(){
            std::string data;
            try{
                file.open(filePath,std::ios::in);
                if(!file.is_open()){
                    throw std::runtime_error("Error opening file");
                }
                std::string line;
                while(std::getline(file,line)){
                    data+=line;
                }
                file.close();
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
            return data;
        }
        
        
        std::vector<std::string>FileHandler::listFiles(const std::string& dirPath){
            if(!std::filesystem::exists(dirPath)){
                throw std::runtime_error("Directory does not exist");
            }else{
                std::vector<std::string> files;
                for(const auto & entry : std::filesystem::directory_iterator(dirPath)){
                    files.push_back(entry.path());
            }
            return files;
        }
    } 
    
    
    }
}