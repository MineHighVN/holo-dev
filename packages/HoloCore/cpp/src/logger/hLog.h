#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>
#include <string>

namespace logger {
    template<typename T>
    void logImpl(std::ostringstream& oss, T&& value) {
        oss << std::forward<T>(value);
    }

    template<typename T, typename... Args>
    void logImpl(std::ostringstream& oss, T&& value, Args&&... args) {
        oss << std::forward<T>(value);
        logImpl(oss, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(Args&&... args) {
        std::ostringstream oss;
        oss << "[INFO] ";
        logImpl(oss, std::forward<Args>(args)...);
        std::cout << oss.str() << std::endl;
    }

    template<typename... Args>
    void verbose(Args&&... args) {
        std::ostringstream oss;
        oss << "[VERBOSE] ";
        logImpl(oss, std::forward<Args>(args)...);
        std::cout << oss.str() << std::endl;
    }

    template<typename... Args>
    void debug(Args&&... args) {
        std::ostringstream oss;
        oss << "[DEBUG] ";
        logImpl(oss, std::forward<Args>(args)...);
        std::cout << oss.str() << std::endl;
    }

    template<typename... Args>
    void error(Args&&... args) {
        std::ostringstream oss;
        oss << "[ERROR] ";
        logImpl(oss, std::forward<Args>(args)...);
        std::cerr << oss.str() << std::endl;
    }

    template<typename... Args>
    void warn(Args&&... args) {
        std::ostringstream oss;
        oss << "[WARN] ";
        logImpl(oss, std::forward<Args>(args)...);
        std::cout << oss.str() << std::endl;
    }
}

#endif // LOGGER_H