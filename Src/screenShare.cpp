#include "../Lib/screenShare.hpp"
#include <X11/Xlib.h>
#include <cstring>
#include <exception>


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
            unsigned char* frame = new unsigned char[width*height*4];
            std::memcpy(frame, img->data, width*height*4);
            return frame;
        }
    }
}