#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "../HoloEngine/Node.h"
#include <node_api.h>

class ErrNodeNotFound : public std::exception {
private:
    std::string message;

public:
    ErrNodeNotFound(uint64_t id) : message("node with id " + std::to_string(id) + " not found") {};

    const char* what() const noexcept override {
        return message.c_str();
    }
};

namespace Translator {
    holo_node getNode(napi_env env, napi_value value);
}
