#include "../Lib/screenShare.hpp"
#include <X11/Xlib.h>
#include <opencv4/opencv2/core/mat.hpp>
/*
* Undefine Status macro defined in Xlib.h to fix build conflicts
*/
#undef Status
#include <cstring>
#include <exception>
#include <opencv2/opencv.hpp>


namespace pcControl{
    namespace screenShare {
        screenCapture::screenCapture(){
            try{
            /*
            * Open the display
            */
            display = XOpenDisplay(nullptr);
             /*
            * Get the default screen for the current display
            */

            screen=DefaultScreen(display);
            /*
            * Get the root window for the current display
            */
            root = RootWindow(display,screen);
            /*
            * Get the attributes of the root window
            */

            XGetWindowAttributes(display, root, &attr);
            if(!display){
                throw "Unable to open X display";
            }
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;

            }
        
        }
        screenCapture::~screenCapture(){
            if(img){
                XDestroyImage(img);
            }
            if(display){
                XCloseDisplay(display);
            }
        }
        unsigned char* screenCapture::captureScreen(int width, int height){
            width=attr.width;
            height=attr.height;
            try{
                /*
            * Get the image of the root window
                */
            img = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);
            if(!img){
                throw "Unable to capture screen";
            }
            }catch(std::exception &e){
                std::cerr<<e.what()<<std::endl;
            }
            /*
            * Copy the image data to a buffer
            */


            unsigned char* frame = new unsigned char[width*height*4];
            std::memcpy(frame, img->data, width*height*4);
            return frame;
        }

        /*
        * Encode the frame to JPEG
        * pixels: The frame to encode
        * width: The width of the frame
        * height: The height of the frame
        * quality: The quality of the JPEG - default is 50 to reduce size and ensure smooth transmission

        */
        std::vector<unsigned char> frameEncoder::encodeToJPEG(unsigned char* pixels, int width, int height, int quality){
           cv::Mat frame(height, width, CV_8UC4, pixels);
              std::vector<unsigned char> buffer;
                std::vector<int> params;
                params.push_back(cv::IMWRITE_JPEG_QUALITY);
                params.push_back(quality);
                cv::imencode(".jpg", frame, buffer, params);
                return buffer;
        }
        screenShareServer::screenShareServer(int port):server(port, default_domain, default_type, default_protocol){
            
        }
        /*
        * Start the screen sharing server
        * Capture the screen, encode the frame to JPEG and send it to the client
        * This function runs indefinitely
        */
        void screenShareServer::start(){
            server.listenSocket();
            server.acceptConnection();
            while(true){
                unsigned char* frame = screen.captureScreen();
                std::vector<unsigned char> jpeg = encoder.encodeToJPEG(frame, screen_width, screen_height);
                server.sendData(std::string(jpeg.begin(), jpeg.end()));
                delete[] frame;
            }
        }
        void screenShareServer::stop(){
            server.closeSocket();
        }
    }

    
}