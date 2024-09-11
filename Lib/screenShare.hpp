#ifndef SCREENSHARE_HPP
#define SCREENSHARE_HPP

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <sys/socket.h>
#include "socket.hpp"


namespace pcControl {
    namespace screenShare {
        /*Default screen size*/
    const  int screen_width = 1920;
    const  int screen_height = 1080;

      /*
        Default Server Settings
        For UDP Server
      */
    const int default_port = 8090;
    const int default_domain = AF_INET;
    const int default_type = SOCK_DGRAM;
    const int default_protocol = 0;
        /*Class to Capture Screen*/
        class screenCapture{
            private:
            Display* display;
            Window root;
            XImage* img;
            XWindowAttributes attr;
            int screen;
            public:
            screenCapture();
            ~screenCapture();

            unsigned char* captureScreen(int width=screen_width, int height=screen_height);
        };
    
    /*Class to Encode Frame*/
    class frameEncoder{
        public:
    std::vector<unsigned char> encodeToJPEG(unsigned char* pixels, int width, int height, int quality = 50);
    
    };

    class screenShareServer{
        private:
        sockets::ServerSocket server;
        screenShare::screenCapture screen;
        frameEncoder encoder;
        public:
        screenShareServer(int port);
        void start();
    };

}

}


#endif // !SCREENSHARE_HPP