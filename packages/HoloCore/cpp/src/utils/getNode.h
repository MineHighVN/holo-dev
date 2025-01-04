#pragma once

#include <node_api.h>
#include <memory>

#include "../HoloEngine/Node.h"

namespace utils {
    std::shared_ptr<Node> getNode(napi_env env, napi_value value);
}
