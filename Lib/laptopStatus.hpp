#ifndef LAPTOPSTATUS_HPP
#define LAPTOPSTATUS_HPP

#include <string>
#include <type_traits>
#include "fileHandler.hpp"

namespace pcControl {
    namespace laptopStatus {
        class LaptopStatus {
            private:
                static void getBatteryStatus();
                static void getTemperature();
                static void getRamUsage();
                static void getDiskUsage();
                static void getCPUUsage();

                
            public:
                
                static std::string getStatus();
        };
    }
}

#endif // !LAPTOPSTATUS_HPP
