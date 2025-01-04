#include <memory>

#include "NodeManager.h"
#include "Text.h"
#include "Body.h"

namespace NodeManager {
    unsigned int CreateNode(std::string nodeName) {
        std::shared_ptr<Node> node;
        if (nodeName == "p") {
            node = std::make_shared<Text>();
        } else if (nodeName == "body") {
            body = std::make_shared<Body>();
            node = body;
        }

        if (node != nullptr) {
            NodeMap[node->getNodeID()] = node;
            return node->getNodeID();
        } else {
            return 0;
        }
    }
}