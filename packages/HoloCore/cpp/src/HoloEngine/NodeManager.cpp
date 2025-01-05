#include <memory>

#include "NodeManager.h"
#include "Text.h"
#include "Body.h"
#include "Div.h"

namespace NodeManager {
    unsigned int CreateNode(std::string nodeName) {
        std::shared_ptr<Node> node;
        if (nodeName == "p") {
            node = std::make_shared<Text>();
        } else if (nodeName == "body") {
            body = std::make_shared<Body>();
            node = body;
        } else if (nodeName == "div") {
            node = std::make_shared<Div>();
        }

        if (node != nullptr) {
            NodeMap[node->getNodeID()] = node;
            node->setSelfSharedPtr(node);
            return node->getNodeID();
        } else {
            return 0;
        }
    }
}