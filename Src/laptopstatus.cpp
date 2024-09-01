#include "../Lib/laptopStatus.hpp"
#include <string>
#include <thread>
#include <future>
#include <map>
#include <iostream>

namespace pcControl {
    namespace laptopStatus {

        // Helper function definitions
        void getBatteryStatusHelper(std::promise<std::map<std::string, std::string>> promise) {
            std::map<std::string, std::string> batteryStatus;
            std::string batteryStatusPath = "/sys/class/power_supply/BAT0/status";
            std::string batteryCapacityPath = "/sys/class/power_supply/BAT0/capacity";
            try {
                pcControl::fileHandler::FileHandler fileHandler(batteryStatusPath);
                std::string status = fileHandler.readFromFile();
                fileHandler.setFilePath(batteryCapacityPath);
                std::string capacity = fileHandler.readFromFile();
                batteryStatus["status"] = status;
                batteryStatus["capacity"] = capacity;
            }
            catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
            promise.set_value(batteryStatus);
        }

        void getTemperatureHelper(std::promise<std::string> promise) {
            std::string temperaturePath = "/sys/class/thermal/thermal_zone0/temp";
            try {
                pcControl::fileHandler::FileHandler fileHandler(temperaturePath);
                std::string temperature = fileHandler.readFromFile();
                if (temperature.empty()) {
                    throw std::runtime_error("Error getting temperature");
                }
                temperature = std::to_string(std::stoi(temperature) / 1000);
                promise.set_value(temperature);
            }
            catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
                promise.set_value("Error getting temperature");
            }
        }

        void getRamUsageHelper(std::promise<std::string> promise) {
            std::string ramUsagePath = "/proc/meminfo";
            pcControl::fileHandler::FileHandler fileHandler(ramUsagePath);
            std::string ramUsage = fileHandler.readFromFile();
            promise.set_value(ramUsage);
        }

        void getDiskUsageHelper(std::promise<std::string> promise) {
            std::string diskUsagePath = "/proc/diskstats";
            pcControl::fileHandler::FileHandler fileHandler(diskUsagePath);
            std::string diskUsage = fileHandler.readFromFile();
            promise.set_value(diskUsage);
        }

        void getCPUUsageHelper(std::promise<std::string> promise) {
            std::string cpuUsagePath = "/proc/stat";
            pcControl::fileHandler::FileHandler fileHandler(cpuUsagePath);
            std::string cpuUsage = fileHandler.readFromFile();
            promise.set_value(cpuUsage);
        }

        std::string LaptopStatus::getStatus() {
            // Create promises and futures for each status component
            std::promise<std::map<std::string, std::string>> batteryStatusPromise;
            std::future<std::map<std::string, std::string>> batteryStatusFuture = batteryStatusPromise.get_future();

            std::promise<std::string> temperaturePromise;
            std::future<std::string> temperatureFuture = temperaturePromise.get_future();

            std::promise<std::string> ramUsagePromise;
            std::future<std::string> ramUsageFuture = ramUsagePromise.get_future();

            std::promise<std::string> diskUsagePromise;
            std::future<std::string> diskUsageFuture = diskUsagePromise.get_future();

            std::promise<std::string> cpuUsagePromise;
            std::future<std::string> cpuUsageFuture = cpuUsagePromise.get_future();

            // Start threads to compute each status component
            std::thread batteryStatusThread(getBatteryStatusHelper, std::move(batteryStatusPromise));
            std::thread temperatureThread(getTemperatureHelper, std::move(temperaturePromise));
            std::thread ramUsageThread(getRamUsageHelper, std::move(ramUsagePromise));
            std::thread diskUsageThread(getDiskUsageHelper, std::move(diskUsagePromise));
            std::thread cpuUsageThread(getCPUUsageHelper, std::move(cpuUsagePromise));

            // Wait for all threads to finish
            batteryStatusThread.join();
            temperatureThread.join();
            ramUsageThread.join();
            diskUsageThread.join();
            cpuUsageThread.join();

            // Get results from futures
            std::map<std::string, std::string> batteryStatus = batteryStatusFuture.get();
            std::string temperature = temperatureFuture.get();
            std::string ramUsage = ramUsageFuture.get();
            std::string diskUsage = diskUsageFuture.get();
            std::string cpuUsage = cpuUsageFuture.get();

            // Construct the status string
            std::string status;
            status += "Battery Status: " + batteryStatus["status"] + " Battery Capacity: " + batteryStatus["capacity"] + "\n";
            status += "Temperature: " + temperature + "\n";
          //  status += "Ram Usage: " + ramUsage + "\n";
          //  status += "Disk Usage: " + diskUsage + "\n";
          //  status += "CPU Usage: " + cpuUsage + "\n";
            return status;
        }
    }
}
