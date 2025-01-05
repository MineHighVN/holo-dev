#include "Translator.h"

#include "getParameters.h"

namespace Translator {
    holo_node getNode(napi_env env, napi_value value) {
        uint64_t nodeId = utils::getUint64(env, value);

        std::shared_ptr<Node> node = Node::getNode(nodeId);
        
        if (node != nullptr) {
            return node;
        } else {
            napi_throw_error(env, NULL, "node not found");
            throw ErrNodeNotFound(nodeId);
            return nullptr;
        }
    }
}