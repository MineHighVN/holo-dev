#include <stdexcept>


class ErrNoPhysicalDevice : public std::exception {
private:
    std::string message;

public:
    explicit ErrNoPhysicalDevice() : message("no support physical device") {}
};

class ErrNoDeviceCompatible : public std::exception {
private:
    std::string message;

public:
    explicit ErrNoDeviceCompatible() : message("no support physical device") {}
};

class ErrInvalidAPI : public std::exception {
private:
    std::string message;

public:
    explicit ErrInvalidAPI() : message("invalid function forapi using") {}
};
