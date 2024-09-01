#include "../Lib/webBrowserHandler.hpp"
#include <string>



namespace pcControl {
    namespace webBrowserHandler{
        void WebBrowserHandler::openWebBrowser(std::string url){
            try{
            std::string cmd="firefox "+url;
           int response= std::system(cmd.c_str());
           if(response==-1){
               throw std::runtime_error("Error opening web browser");
                }
            }
            catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
        }
        
        void WebBrowserHandler::closeWebBrowser(){
            try{
            std::string cmd="pkill firefox";
            int response=std::system(cmd.c_str());
            if(response==-1){
                throw std::runtime_error("Error closing web browser");
            }
            }
            catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
        }
    
    }
}