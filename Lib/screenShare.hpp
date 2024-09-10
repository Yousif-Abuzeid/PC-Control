#ifndef SCREENSHARE_HPP
#define SCREENSHARE_HPP

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "socket.hpp"


namespace pcControl {
    namespace screenShare {
        /*Default screen size*/
      const  int screen_width = 1920;
      const  int screen_height = 1080;
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

    }
    /*Class to Encode Frame*/
    class frameEncoder{
        frameEncoder();
        ~frameEncoder();
        std::string encodeFrame(unsigned char* frame, int width=screenShare::screen_width, int height=screenShare::screen_height);
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




#endif // !SCREENSHARE_HPP
