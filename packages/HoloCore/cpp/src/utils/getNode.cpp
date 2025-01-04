#include "getNode.h"

#include "getParameters.h"

namespace utils {
    std::shared_ptr<Node> getNode(napi_env env, napi_value value) {
        uint64_t nodeId = getUint64(env, value);

        auto it = NodeMap.find(nodeId);
        if (it != NodeMap.end()) {
            return it->second;
        } else {
            std::cerr << "Node not found for the given key: " << nodeId << std::endl;
            return nullptr;
        }
    }
}
