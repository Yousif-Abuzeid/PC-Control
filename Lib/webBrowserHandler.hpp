#ifndef WEBBROWSERHANDLER_HPP
#define WEBBROWSERHANDLER_HPP

#include <string>
#include <vector>
#include <iostream>


namespace pcControl {
    namespace webBrowserHandler {
        class WebBrowserHandler {
            public:
                
                static void openWebBrowser(std::string url);
                static void closeWebBrowser();
        };
    
    }
}

#endif // !WEBBROWSERHANDLER_HPP